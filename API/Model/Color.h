#pragma once
#ifndef NUKEE_COLOR_H
#define NUKEE_COLOR_H

class Color
{
public:
	float r, g, b, a;

	Color() {}
	Color(float r, float g, float b, float a) 
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}


	Color operator+(Color other)
	{
		Color tmp = Color(other.r + r, other.g + g, other.b + b,  other.a + a);
		return tmp;
	}

	Color operator+=(Color other)
	{
		a += other.a; b += other.b; g += other.g; r += other.r;
		return *this;
	}

	Color operator-(Color other)
	{
		Color tmp = Color(r - other.r, g - other.g, b - other.b, a - other.a);
		return tmp;
	}

	Color operator-=(Color other)
	{
		a -= other.a; b -= other.b; g -= other.g; r -= other.r;
		return *this;
	}

	Color operator*(Color other)
	{
		Color tmp = Color(r * other.r, g * other.g, b * other.b, a * other.a);
		return tmp;
	}

	Color operator*=(Color other)
	{
		a *= other.a; b *= other.b; g *= other.g; r *= other.r;
		return *this;
	}

	Color operator/(Color other)
	{
		Color tmp = Color(r / other.r, g / other.g, b / other.b, a / other.a);
		return tmp;
	}

	Color operator/=(Color other)
	{
		a /= other.a; b /= other.b; g /= other.g; r /= other.r;
		return *this;
	}

	Color operator*(double other)
	{
		Color tmp = Color(r - other, g - other, b - other, a - other);
		return tmp;
	}

	Color operator*=(double other)
	{
		a *= other; b *= other; g *= other; r *= other;
		return *this;
	}

	Color operator/(double other)
	{
		Color tmp = Color(r / other,  g / other, b / other, a / other);
		return tmp;
	}

	Color operator/=(double other)
	{
		a /= other; b /= other; g /= other; r /= other;
		return *this;
	}

    class Vector4 toVector4();
};
#endif // !NUKEE_COLOR_H
