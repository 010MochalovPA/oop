#include "LineSegment.h"
#include "Common.h"
#include "stdafx.h"

Point LineSegment::GetStartPoint() const
{
	return m_startPoint;
}

Point LineSegment::GetEndPoint() const
{
	return m_endPoint;
}

double LineSegment::GetPerimeter() const
{
	return sqrt(pow(m_startPoint.GetX() - m_endPoint.GetX(), 2) + pow(m_startPoint.GetY() - m_endPoint.GetY(), 2));
}

double LineSegment::GetArea() const
{
	return 0.0;
}

uint32_t LineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string LineSegment::ToString() const
{
	return m_title
		+ ": "
		+ m_startPoint.ToString() + " "
		+ m_endPoint.ToString() + " "
		+ "area " + std::format("{:.2f}", GetArea()) + " "
		+ "perimeter " + std::format("{:.2f}", GetPerimeter()) + " "
		+ "length " + std::format("{:.2f}", GetPerimeter()) + " "
		+ "outline " + ColorToHex(m_outlineColor);
}

void LineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}
