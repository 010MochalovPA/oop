#include "Rectangle.h"
#include "Common.h"

double Rectangle::GetPerimeter() const
{
	return (GetWidth() + GetHeight()) * 2;
}

double Rectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

uint32_t Rectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Rectangle::GetFillColor() const
{
	return m_fillColor;
}

std::string Rectangle::ToString() const
{ // устранить дублирование кода между методами toString
	return m_title + ": "// удалить m_title
		+ m_leftTop.ToString() + " "
		+ m_rightBottom.ToString() + " "
		+ "area " + std::format("{:.2f}", GetArea()) + " "
		+ "perimeter " + std::format("{:.2f}", GetPerimeter()) + " "
		+ "outline " + ColorToHex(m_outlineColor) + " "
		+ "fill " + ColorToHex(m_fillColor);
}

Point Rectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point Rectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double Rectangle::GetWidth() const
{
	double x1 = m_rightBottom.GetX();
	double x2 = m_leftTop.GetX();
	return abs(x1 - x2);
}

double Rectangle::GetHeight() const
{
	double y1 = m_rightBottom.GetY();
	double y2 = m_leftTop.GetY();
	return abs(y1 - y2);
}

void Rectangle::Draw(ICanvas& canvas) const
{
	Point rightTop = Point(m_rightBottom.GetX(), m_leftTop.GetY());
	Point leftBottom = Point(m_leftTop.GetX(), m_rightBottom.GetY());
	
	std::vector<Point> vertexes = {
		m_leftTop,
		rightTop,
		m_rightBottom,
		leftBottom
	};
	
	canvas.FillPolygon(vertexes, m_fillColor);
	canvas.DrawLine(m_leftTop, rightTop, m_outlineColor);
	canvas.DrawLine(rightTop, m_rightBottom, m_outlineColor);
	canvas.DrawLine(m_rightBottom, leftBottom, m_outlineColor);
	canvas.DrawLine(leftBottom, m_leftTop, m_outlineColor);
}
