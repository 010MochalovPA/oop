#pragma once

#include "ISolidShape.h"
#include "Point.h"
#include "LineSegment.h"
#include "Common.h"
#include <math.h>
#include "stdafx.h"

class Triangle : public ISolidShape
{
public:
	Triangle(Point vertex1, Point vertex2, Point vertex3, uint32_t outlineColor = 0, uint32_t fillColor = 0)
		: m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
		, m_title("Triangle")
	{
	}

	double GetPerimeter() const override;
	double GetArea() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	std::string ToString() const override;
	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

	void Draw(ICanvas& canvas) const override;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
	std::string m_title;
};