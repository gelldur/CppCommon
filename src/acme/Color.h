//
// Created by Dawid Drozd aka Gelldur on 14.05.17.
//
#pragma once

#include <ccTypes.h>

namespace Color
{
/**
 * @param color format is AARRGGBB
 * @return RR
 */
inline unsigned char getRed(int colorARGB)
{
	return static_cast<unsigned char>((colorARGB & 0xFF0000) >> 16);
}

/**
 * @param color format is AARRGGBB
 * @return GG
 */
inline unsigned char getGreen(int colorARGB)
{
	return static_cast<unsigned char>((colorARGB & 0x00FF00) >> 8);
}

/**
 * @param color format is AARRGGBB
 * @return BB
 */
inline unsigned char getBlue(int colorARGB)
{
	return static_cast<unsigned char>(colorARGB & 0x0000FF);
}

/**
 * @param color format is AARRGGBB
 * @return AA
 */
inline unsigned char getAlpha(int colorARGB)
{
	return static_cast<unsigned char>((colorARGB & 0xFF000000) >> 24);
}

inline int setAlpha(const int colorARGB, unsigned char alpha)
{
	return (colorARGB & 0x00FFFFFF) | (alpha << 24);
}

cocos2d::ccColor3B convertTo3B(const int colorARGB);
cocos2d::ccColor4F convertTo4F(const int colorARGB);
cocos2d::ccColor4B convertTo4B(const int colorARGB);

class convert
{
public:
	convert(int colorARGB)
			: _colorARGB(colorARGB)
	{
	}

	template<typename T>
	inline operator T()
	{
		return T{_colorARGB};
	}

	convert& opacity(const float value)
	{
		_colorARGB = setAlpha(_colorARGB, static_cast<unsigned char>(255 * value));
		return *this;
	}

private:
	int _colorARGB;
};

template<>
inline convert::operator cocos2d::ccColor3B()
{
	return convertTo3B(_colorARGB);
}

template<>
inline convert::operator cocos2d::ccColor4F()
{
	return convertTo4F(_colorARGB);
}

template<>
inline convert::operator cocos2d::ccColor4B()
{
	return convertTo4B(_colorARGB);
}

}
