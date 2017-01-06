//
// Created by Dawid Drozd aka Gelldur on 06/01/17.
//

#include <gtest/gtest.h>

#include <cocos2d.h>
#include <memory/RefHolder.h>

using namespace Dexode;

class TestRef : public cocos2d::Ref
{

};

TEST(RefHolderTest, simpleOne)
{
	auto testRef = new TestRef();
	EXPECT_EQ(1, testRef->getReferenceCount());
	{
		RefHolder<TestRef> holder{testRef};
		EXPECT_EQ(2, testRef->getReferenceCount());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	testRef->release();//delete
}

TEST(RefHolderTest, empty)
{
	auto testRef = new TestRef();
	{
		RefHolder<TestRef> holder{};
		EXPECT_EQ(1, testRef->getReferenceCount());
	}
	{
		RefHolder<TestRef> holder{nullptr};
		EXPECT_EQ(1, testRef->getReferenceCount());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	testRef->release();//delete
}

TEST(RefHolderTest, doubleRetain)
{
	auto testRef = new TestRef();
	{
		RefHolder<TestRef> holder{testRef};
		EXPECT_EQ(2, testRef->getReferenceCount());

		RefHolder<TestRef> holderCopy{testRef};
		EXPECT_EQ(3, testRef->getReferenceCount());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	testRef->release();//delete
}

TEST(RefHolderTest, copyCtor)
{
	auto testRef = new TestRef();
	{
		RefHolder<TestRef> holder{testRef};
		EXPECT_EQ(2, testRef->getReferenceCount());
		{
			RefHolder<TestRef> holderCopy{holder};
			EXPECT_EQ(3, testRef->getReferenceCount());
		}
		EXPECT_EQ(2, testRef->getReferenceCount());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	testRef->release();//delete
}

TEST(RefHolderTest, copyCtorAssign)
{
	auto testRef = new TestRef();
	{
		RefHolder<TestRef> holder{testRef};
		EXPECT_EQ(2, testRef->getReferenceCount());
		testRef->release();
		EXPECT_EQ(1, testRef->getReferenceCount());
		{
			RefHolder<TestRef> holderCopy{holder};
			EXPECT_EQ(2, testRef->getReferenceCount());
			holderCopy = holder;
			EXPECT_EQ(2, testRef->getReferenceCount());
		}
		EXPECT_EQ(1, testRef->getReferenceCount());
	}
}

TEST(RefHolderTest, selfAssign)
{
	auto testRef = new TestRef();
	{
		RefHolder<TestRef> holder{testRef};
		EXPECT_EQ(2, testRef->getReferenceCount());
		holder = holder;
		EXPECT_EQ(2, testRef->getReferenceCount());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	testRef->release();//delete
}

TEST(RefHolderTest, copyCtorNullptr)
{
	RefHolder<TestRef> holder{nullptr};
	{
		RefHolder<TestRef> holderCopy{holder};
		EXPECT_NO_FATAL_FAILURE(holderCopy.release());//should not crash
	}
	holder.release();
}

TEST(RefHolderTest, moveCtor)
{
	auto testRef = new TestRef();
	{
		RefHolder<TestRef> holder{testRef};
		EXPECT_EQ(2, testRef->getReferenceCount());
		{
			RefHolder<TestRef> holderCopy{std::move(holder)};
			EXPECT_EQ(2, testRef->getReferenceCount());
		}
		EXPECT_EQ(1, testRef->getReferenceCount());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	testRef->release();//delete
}

TEST(RefHolderTest, moveCtorNullptr)
{
	RefHolder<TestRef> holder{nullptr};
	{
		RefHolder<TestRef> holderCopy{std::move(holder)};
		EXPECT_NO_FATAL_FAILURE(holderCopy.release());//should not crash
	}
	holder.release();
}

TEST(RefHolderTest, assignCopy)
{
	auto testRef = new TestRef();
	{
		RefHolder<TestRef> holder{testRef};
		EXPECT_EQ(2, testRef->getReferenceCount());
		{
			RefHolder<TestRef> holderCopy;
			EXPECT_EQ(2, testRef->getReferenceCount());
			holderCopy = holder;
			EXPECT_EQ(3, testRef->getReferenceCount());
		}
		EXPECT_EQ(2, testRef->getReferenceCount());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	testRef->release();//delete
}

TEST(RefHolderTest, assignCopyNullptr)
{
	RefHolder<TestRef> holder{nullptr};
	{
		RefHolder<TestRef> holderCopy;
		EXPECT_NO_FATAL_FAILURE(holderCopy = holder);
		EXPECT_NO_FATAL_FAILURE(holderCopy.release());
	}
}

TEST(RefHolderTest, assignMove)
{
	auto testRef = new TestRef();
	{
		RefHolder<TestRef> holder{testRef};
		EXPECT_EQ(2, testRef->getReferenceCount());
		{
			RefHolder<TestRef> holderCopy;
			EXPECT_EQ(2, testRef->getReferenceCount());
			holderCopy = std::move(holder);
			EXPECT_EQ(2, testRef->getReferenceCount());
		}
		EXPECT_EQ(1, testRef->getReferenceCount());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	testRef->release();//delete
}

TEST(RefHolderTest, assignMoveSamePointer)
{
	auto testRef = new TestRef();
	{
		RefHolder<TestRef> holder{testRef};
		EXPECT_EQ(2, testRef->getReferenceCount());
		{
			RefHolder<TestRef> holderCopy{testRef};
			EXPECT_EQ(3, testRef->getReferenceCount());
			holderCopy = std::move(holder);
			EXPECT_EQ(2, testRef->getReferenceCount());
		}
		EXPECT_EQ(1, testRef->getReferenceCount());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	testRef->release();//delete
}

TEST(RefHolderTest, assignMoveNullptr)
{
	RefHolder<TestRef> holder{nullptr};
	{
		RefHolder<TestRef> holderCopy;
		EXPECT_NO_FATAL_FAILURE(holderCopy = std::move(holder));
		EXPECT_NO_FATAL_FAILURE(holderCopy.release());
	}
}

TEST(RefHolderTest, reset)
{
	auto testRef = new TestRef();
	{
		RefHolder<TestRef> holder{testRef};
		EXPECT_EQ(2, testRef->getReferenceCount());
		EXPECT_NO_FATAL_FAILURE(holder.reset());
		EXPECT_EQ(2, testRef->getReferenceCount());
		EXPECT_NO_FATAL_FAILURE(holder.release());
		EXPECT_EQ(2, testRef->getReferenceCount());
		testRef->release();
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	{
		RefHolder<TestRef> holder{nullptr};
		EXPECT_NO_FATAL_FAILURE(holder.reset());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	testRef->release();//delete
}

TEST(RefHolderTest, release)
{
	auto testRef = new TestRef();
	{
		RefHolder<TestRef> holder{testRef};
		EXPECT_EQ(2, testRef->getReferenceCount());
		holder.release();
		EXPECT_EQ(1, testRef->getReferenceCount());
		EXPECT_NO_FATAL_FAILURE(holder.release());
		EXPECT_EQ(1, testRef->getReferenceCount());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	{
		RefHolder<TestRef> holder{nullptr};
		EXPECT_NO_FATAL_FAILURE(holder.release());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	testRef->release();//delete
}

TEST(RefHolderTest, checks)
{
	auto testRef = new TestRef();
	{
		RefHolder<TestRef> holder{testRef};
		EXPECT_EQ(2, testRef->getReferenceCount());
		EXPECT_TRUE(holder);
		EXPECT_FALSE(holder.isNull());
		EXPECT_FALSE(holder != testRef);
		EXPECT_TRUE(holder != nullptr);
		EXPECT_TRUE(holder == testRef);
		EXPECT_FALSE(holder == nullptr);
		EXPECT_EQ(testRef, holder.get());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	{
		RefHolder<TestRef> holder{nullptr};
		EXPECT_FALSE(holder);
		EXPECT_TRUE(holder.isNull());
		EXPECT_TRUE(holder != testRef);
		EXPECT_FALSE(holder != nullptr);
		EXPECT_FALSE(holder == testRef);
		EXPECT_TRUE(holder == nullptr);
		EXPECT_NE(testRef, holder.get());
	}
	EXPECT_EQ(1, testRef->getReferenceCount());
	testRef->release();//delete
}

TEST(RefHolderTest, assignCopy2)
{
	auto testRefA = new TestRef();
	auto testRefB = new TestRef();
	testRefA->retain();
	testRefB->retain();
	EXPECT_EQ(2, testRefA->getReferenceCount());
	EXPECT_EQ(2, testRefB->getReferenceCount());

	{
		RefHolder<TestRef> holder{testRefA};
		EXPECT_EQ(3, testRefA->getReferenceCount());
		{
			RefHolder<TestRef> holderCopy{testRefB};
			EXPECT_EQ(3, testRefB->getReferenceCount());
			holderCopy = holder;
			EXPECT_EQ(2, testRefB->getReferenceCount());
			EXPECT_EQ(4, testRefA->getReferenceCount());
		}
		EXPECT_EQ(3, testRefA->getReferenceCount());
	}

	EXPECT_EQ(2, testRefA->getReferenceCount());
	EXPECT_EQ(2, testRefB->getReferenceCount());
	testRefA->release();
	testRefB->release();
	EXPECT_EQ(1, testRefA->getReferenceCount());
	EXPECT_EQ(1, testRefB->getReferenceCount());
	testRefA->release();//delete
	testRefB->release();//delete
}

TEST(RefHolderTest, assignCopy2Nullptr)
{
	auto testRefA = new TestRef();
	auto testRefB = new TestRef();
	testRefA->retain();
	testRefB->retain();
	EXPECT_EQ(2, testRefA->getReferenceCount());
	EXPECT_EQ(2, testRefB->getReferenceCount());

	{
		RefHolder<TestRef> holder{nullptr};
		{
			RefHolder<TestRef> holderCopy{testRefB};
			EXPECT_EQ(3, testRefB->getReferenceCount());
			holderCopy = holder;
			EXPECT_EQ(2, testRefB->getReferenceCount());
			EXPECT_EQ(2, testRefA->getReferenceCount());
		}
		EXPECT_EQ(2, testRefA->getReferenceCount());
	}

	EXPECT_EQ(2, testRefA->getReferenceCount());
	EXPECT_EQ(2, testRefB->getReferenceCount());
	testRefA->release();
	testRefB->release();
	EXPECT_EQ(1, testRefA->getReferenceCount());
	EXPECT_EQ(1, testRefB->getReferenceCount());
	testRefA->release();//delete
	testRefB->release();//delete
}

TEST(RefHolderTest, assignMove2)
{
	auto testRefA = new TestRef();
	auto testRefB = new TestRef();
	testRefA->retain();
	testRefB->retain();
	EXPECT_EQ(2, testRefA->getReferenceCount());
	EXPECT_EQ(2, testRefB->getReferenceCount());

	{
		RefHolder<TestRef> holder{testRefA};
		EXPECT_EQ(3, testRefA->getReferenceCount());
		{
			RefHolder<TestRef> holderCopy{testRefB};
			EXPECT_EQ(3, testRefB->getReferenceCount());
			holderCopy = std::move(holder);
			EXPECT_EQ(2, testRefB->getReferenceCount());
			EXPECT_EQ(3, testRefA->getReferenceCount());
		}
		EXPECT_EQ(2, testRefA->getReferenceCount());
	}

	EXPECT_EQ(2, testRefA->getReferenceCount());
	EXPECT_EQ(2, testRefB->getReferenceCount());
	testRefA->release();
	testRefB->release();
	EXPECT_EQ(1, testRefA->getReferenceCount());
	EXPECT_EQ(1, testRefB->getReferenceCount());
	testRefA->release();//delete
	testRefB->release();//delete
}

TEST(RefHolderTest, assignMove2Nullptr)
{
	auto testRefA = new TestRef();
	auto testRefB = new TestRef();
	testRefA->retain();
	testRefB->retain();
	EXPECT_EQ(2, testRefA->getReferenceCount());
	EXPECT_EQ(2, testRefB->getReferenceCount());

	{
		RefHolder<TestRef> holder{nullptr};
		{
			RefHolder<TestRef> holderCopy{testRefB};
			EXPECT_EQ(3, testRefB->getReferenceCount());
			holderCopy = std::move(holder);
			EXPECT_EQ(2, testRefB->getReferenceCount());
			EXPECT_EQ(2, testRefA->getReferenceCount());
		}
		EXPECT_EQ(2, testRefA->getReferenceCount());
	}

	EXPECT_EQ(2, testRefA->getReferenceCount());
	EXPECT_EQ(2, testRefB->getReferenceCount());
	testRefA->release();
	testRefB->release();
	EXPECT_EQ(1, testRefA->getReferenceCount());
	EXPECT_EQ(1, testRefB->getReferenceCount());
	testRefA->release();//delete
	testRefB->release();//delete
}

class DeletingClass : public cocos2d::Node
{
public:
	DeletingClass(bool& deleteTracker)
			: isDeleted(deleteTracker)
	{

	}

	virtual ~DeletingClass()
	{
		isDeleted = true;
	}

	bool& isDeleted;
};

TEST(RefHolderTest, dependedReleaseAssignCopy)
{
	bool isADeleted = false;
	bool isBDeleted = false;
	auto testRefA = new DeletingClass(isADeleted);
	auto testRefB = new DeletingClass(isBDeleted);
	testRefA->init();
	testRefB->init();
	EXPECT_EQ(1, testRefA->getReferenceCount());
	EXPECT_EQ(1, testRefB->getReferenceCount());
	EXPECT_FALSE(isADeleted);
	EXPECT_FALSE(isBDeleted);

	testRefA->addChild(testRefB);
	EXPECT_EQ(2, testRefB->getReferenceCount());
	testRefB->release();
	EXPECT_EQ(1, testRefB->getReferenceCount());
	{
		RefHolder<cocos2d::Ref> holder{testRefA};
		EXPECT_EQ(2, testRefA->getReferenceCount());
		testRefA->release();
		EXPECT_EQ(1, testRefA->getReferenceCount());
		EXPECT_EQ(1, testRefB->getReferenceCount());//B is hold by A
		{
			EXPECT_FALSE(isADeleted);
			EXPECT_FALSE(isBDeleted);
			//holder can't release firstly refA because
			//it will delete refB and we will have invalid pointer in refB
			holder = testRefB;
			//refA will be deleted
			EXPECT_TRUE(isADeleted);
			EXPECT_FALSE(isBDeleted);

			EXPECT_EQ(1, testRefB->getReferenceCount());
		}
	}
	//refB will be deleted
	EXPECT_TRUE(isADeleted);
	EXPECT_TRUE(isBDeleted);
}

TEST(RefHolderTest, dependedReleaseAssignMove)
{
	bool isADeleted = false;
	bool isBDeleted = false;
	auto testRefA = new DeletingClass(isADeleted);
	auto testRefB = new DeletingClass(isBDeleted);
	testRefA->init();
	testRefB->init();
	EXPECT_EQ(1, testRefA->getReferenceCount());
	EXPECT_EQ(1, testRefB->getReferenceCount());
	EXPECT_FALSE(isADeleted);
	EXPECT_FALSE(isBDeleted);

	testRefA->addChild(testRefB);
	EXPECT_EQ(2, testRefB->getReferenceCount());
	testRefB->release();
	EXPECT_EQ(1, testRefB->getReferenceCount());
	{
		RefHolder<cocos2d::Ref> holder{testRefA};
		EXPECT_EQ(2, testRefA->getReferenceCount());
		testRefA->release();
		EXPECT_EQ(1, testRefA->getReferenceCount());
		EXPECT_EQ(1, testRefB->getReferenceCount());//B is hold by A
		{
			EXPECT_FALSE(isADeleted);
			EXPECT_FALSE(isBDeleted);
			//holder can't release firstly refA because
			//it will delete refB and we will have invalid pointer in refB
			holder = RefHolder<cocos2d::Ref>{testRefB};//move will be called
			//refA will be deleted
			EXPECT_TRUE(isADeleted);
			EXPECT_FALSE(isBDeleted);

			EXPECT_EQ(1, testRefB->getReferenceCount());
		}
	}
	//refB will be deleted
	EXPECT_TRUE(isADeleted);
	EXPECT_TRUE(isBDeleted);
}


TEST(RefHolderTest, dependedReleaseAssignMove_cocos)
{
	bool isADeleted = false;
	bool isBDeleted = false;
	auto testRefA = new DeletingClass(isADeleted);
	auto testRefB = new DeletingClass(isBDeleted);
	testRefA->init();
	testRefB->init();
	EXPECT_EQ(1, testRefA->getReferenceCount());
	EXPECT_EQ(1, testRefB->getReferenceCount());
	EXPECT_FALSE(isADeleted);
	EXPECT_FALSE(isBDeleted);

	testRefA->addChild(testRefB);
	EXPECT_EQ(2, testRefB->getReferenceCount());
	testRefB->release();
	EXPECT_EQ(1, testRefB->getReferenceCount());
	{
		cocos2d::RefPtr<cocos2d::Ref> holder{testRefA};
		EXPECT_EQ(2, testRefA->getReferenceCount());
		testRefA->release();
		EXPECT_EQ(1, testRefA->getReferenceCount());
		EXPECT_EQ(1, testRefB->getReferenceCount());//B is hold by A
		{
			EXPECT_FALSE(isADeleted);
			EXPECT_FALSE(isBDeleted);
			//holder can't release firstly refA because
			//it will delete refB and we will have invalid pointer in refB
			holder = cocos2d::RefPtr<cocos2d::Ref>{testRefA};//move will be called
			//refA will be deleted
			EXPECT_FALSE(isADeleted);
			EXPECT_FALSE(isBDeleted);

			EXPECT_EQ(1, testRefA->getReferenceCount());
			EXPECT_EQ(1, testRefB->getReferenceCount());
		}
	}
	//refB will be deleted
	EXPECT_TRUE(isADeleted);
	EXPECT_TRUE(isBDeleted);
}
