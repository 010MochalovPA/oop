#include "ShapeCreator.h"

void ShapeCreator::CreateLine(const Point start, const Point end, const uint32_t color = 0)
{
	m_shapes.push_back(new LineSegment(start, end, color));
}

void ShapeCreator::CreateRectangle(const Point leftTop, const Point rightBottom, const uint32_t outlineColor, const uint32_t fillColor)
{
	m_shapes.push_back(new Rectangle(leftTop, rightBottom, outlineColor, fillColor));
}

void ShapeCreator::CreateTriangle(const Point p1, const Point p2, const Point p3, const uint32_t outlineColor, const uint32_t fillColor)
{
	m_shapes.push_back(new Triangle(p1, p2, p3, outlineColor, fillColor));
}

void ShapeCreator::CreateCircle(const Point origin, const double radius, const uint32_t outlineColor, const uint32_t fillColor)
{
	m_shapes.push_back(new Circle(origin, radius, outlineColor, fillColor));
}

std::vector<IShape*> ShapeCreator::GetShapes() const
{
	return m_shapes;
}
