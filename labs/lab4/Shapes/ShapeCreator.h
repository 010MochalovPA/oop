#pragma once

#include "stdafx.h"
#include "stdafx.h"
#include "IShape.h"
#include "Point.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"

class ShapeCreator
{
public:
	class ShapeCreator()
	{
	}

	void CreateLine(const Point start, const Point end, uint32_t color);
	void CreateRectangle(const Point leftTop, const Point rightBottom, const uint32_t outlineColor, const uint32_t fillColor);
	void CreateTriangle(const Point p1, const Point p2, const Point p3, const uint32_t outlineColor, const uint32_t fillColor);
	void CreateCircle(const Point origin, const double radius, const uint32_t outlineColor, const uint32_t fillColor);
	std::vector<IShape*> GetShapes() const;

private:
	std::vector<IShape*> m_shapes;
};