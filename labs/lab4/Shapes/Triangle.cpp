#include "Triangle.h"

double Triangle::GetPerimeter() const
{
	LineSegment line1(m_vertex1, m_vertex2);
	LineSegment line2(m_vertex2, m_vertex3);
	LineSegment line3(m_vertex3, m_vertex1);

	return line1.GetPerimeter() + line2.GetPerimeter() + line3.GetPerimeter();
}

double Triangle::GetArea() const
{
	double a = LineSegment(m_vertex1, m_vertex2).GetPerimeter();
	double b = LineSegment(m_vertex2, m_vertex3).GetPerimeter();
	double c = LineSegment(m_vertex3, m_vertex1).GetPerimeter();

	double s = (a + b + c) / 2;

	return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

uint32_t Triangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Triangle::GetFillColor() const
{
	return m_fillColor;
}

std::string Triangle::ToString() const
{
	return m_title + ": "
		+ m_vertex1.ToString() + " "
		+ m_vertex2.ToString() + " "
		+ m_vertex3.ToString() + " "
		+ "area " + std::format("{:.2f}", GetArea()) + " "
		+ "perimeter " + std::format("{:.2f}", GetPerimeter()) + " "
		+ "outline " + ColorToHex(m_outlineColor) + " "
		+ "fill " + ColorToHex(m_fillColor);
}

Point Triangle::GetVertex1() const
{
	return m_vertex1;
}

Point Triangle::GetVertex2() const
{
	return m_vertex2;
}

Point Triangle::GetVertex3() const
{
	return m_vertex3;
}

void Triangle::Draw(ICanvas& canvas) const
{
	std::vector<Point> vertexes = {
		m_vertex1,
		m_vertex2,
		m_vertex3
	};

	canvas.FillPolygon(vertexes, m_fillColor);
	canvas.DrawLine(m_vertex1, m_vertex2, m_outlineColor);
	canvas.DrawLine(m_vertex2, m_vertex3, m_outlineColor);
	canvas.DrawLine(m_vertex3, m_vertex1, m_outlineColor);
}
