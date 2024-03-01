#pragma once

#include "ISolidShape.h"
#include "Point.h"
#include "Common.h"
#include "stdafx.h"

class Circle : public ISolidShape
{
public:
	Circle(Point origin, double radius, uint32_t outlineColor = 0, uint32_t fillColor = 0)
		: m_title("Circle")
		, m_origin(origin)
		, m_radius(abs(radius))
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
	{
	}

	double GetPerimeter() const override;
	double GetArea() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;
	Point GetOrigin() const;
	double GetRadius() const;

private:
	Point m_origin;
	double m_radius;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
	std::string m_title; // не надо хранить, информацию не нужно хранить в поле.
};