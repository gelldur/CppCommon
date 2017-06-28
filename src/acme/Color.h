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
inline unsigned char getRed(int color)
{
	return static_cast<unsigned char>((color & 0xFF0000) >> 16);
}

/**
 * @param color format is AARRGGBB
 * @return GG
 */
inline unsigned char getGreen(int color)
{
	return static_cast<unsigned char>((color & 0x00FF00) >> 8);
}

/**
 * @param color format is AARRGGBB
 * @return BB
 */
inline unsigned char getBlue(int color)
{
	return static_cast<unsigned char>(color & 0x0000FF);
}

/**
 * @param color format is AARRGGBB
 * @return AA
 */
inline unsigned char getAlpha(int color)
{
	return static_cast<unsigned char>((color & 0xFF000000) >> 24);
}

inline int setAlpha(const int color, unsigned char alpha)
{
	return (color & 0x00FFFFFF) | (alpha << 24);
}

cocos2d::ccColor3B convertTo3B(const int color);
cocos2d::ccColor4F convertTo4F(const int color);
cocos2d::ccColor4B convertTo4B(const int color);

class convert
{
public:
	convert(int color)
			: _color(color)
	{
	}

	template<typename T>
	inline operator T()
	{
		return T{_color};
	}

	convert& opacity(const float value)
	{
		_color = setAlpha(_color, static_cast<unsigned char>(255 * value));
		return *this;
	}

private:
	int _color;
};

template<>
inline convert::operator cocos2d::ccColor3B()
{
	return convertTo3B(_color);
}

template<>
inline convert::operator cocos2d::ccColor4F()
{
	return convertTo4F(_color);
}

template<>
inline convert::operator cocos2d::ccColor4B()
{
	return convertTo4B(_color);
}

}
