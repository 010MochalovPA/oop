#include "Point.h"

std::string Point::ToString() const
{
	return "(" + std::format("{:.2f}", m_x) + ", " + std::format("{:.2f}", m_y) + ")";
}

double Point::GetX() const
{
	return m_x;
}

double Point::GetY() const
{
	return m_y;
}