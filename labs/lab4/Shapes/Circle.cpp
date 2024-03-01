#include "Circle.h"


double Circle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

double Circle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

uint32_t Circle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Circle::GetFillColor() const
{
	return m_fillColor;
}

std::string Circle::ToString() const
{
	return m_title + ": "
		+ m_origin.ToString() + " "
		+ "area " + std::format("{:.2f}", GetArea()) + " "
		+ "perimeter " + std::format("{:.2f}", GetPerimeter()) + " "
		+ "radius " + std::format("{:.2f}", m_radius) + " "
		+ "outline " + ColorToHex(m_outlineColor) + " "
		+ "fill " + ColorToHex(m_fillColor);
}

void Circle::Draw(ICanvas& canvas) const
{
	canvas.FillCircle(m_origin, m_radius, m_fillColor);
	canvas.DrawCircle(m_origin, m_radius, m_outlineColor);
}

Point Circle::GetOrigin() const
{
	return m_origin;
}

double Circle::GetRadius() const
{
	return m_radius;
}