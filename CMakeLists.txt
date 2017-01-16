CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

SET(FILES
		src/memory/RefHolder.cpp src/memory/RefHolder.h
		)

SET(FILES_GTESTS
		test/gtest/RefHolderTest.cpp
		)

ADD_EXECUTABLE(cocos2d-x-common-Test ${FILES_GTESTS})

TARGET_INCLUDE_DIRECTORIES(cocos2d-x-common-Test PRIVATE
		src
		${gtest_INCLUDE}
		${COCOS2D_ROOT}/cocos
		${COCOS2D_ROOT}/cocos/audio/include/
		${COCOS2D_ROOT}/cocos/platform
		/usr/include/GLFW
		/usr/local/include/GLFW
		)

TARGET_LINK_LIBRARIES(cocos2d-x-common-Test gtest gtest_main)
TARGET_LINK_LIBRARIES(cocos2d-x-common-Test cocos2d)
