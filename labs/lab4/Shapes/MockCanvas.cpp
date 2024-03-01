#include "MockCanvas.h"
#include <iomanip>

void MockCanvas::Draw() const
{
	return;
}

std::string MockCanvas::GetShapes() const
{
	return m_shapes;
}

void MockCanvas::DrawLine(Point from, Point to, uint32_t lineColor)
{
	std::ostringstream stream;

	stream << "l"
		<< std::setw(4) << std::setfill('0') << from.GetX()
		<< std::setw(4) << std::setfill('0') << from.GetY()
		<< std::setw(4) << std::setfill('0') << to.GetX()
		<< std::setw(4) << std::setfill('0') << to.GetY()
		<< std::setw(6) << std::setfill('0') << std::hex << lineColor;

	m_shapes += stream.str();
}

void MockCanvas::FillPolygon(std::vector<Point> points, uint32_t fillColor)
{
	std::ostringstream stream;
	stream << "p";

	for (auto& point : points)
	{
		stream << std::setw(4) << std::setfill('0') << point.GetX()
			<< std::setw(4) << std::setfill('0') << point.GetY();
	}

	stream << std::setw(6) << std::setfill('0') << std::hex << fillColor;
	m_shapes += stream.str();
}

void MockCanvas::FillCircle(Point origin, double radius, uint32_t fillColor)
{
	std::ostringstream stream;
	stream << "fc" 
		<< std::setw(4) << std::setfill('0') << origin.GetX()
		<< std::setw(4) << std::setfill('0') << origin.GetY()
		<< std::setw(4) << std::setfill('0') << radius
		<< std::setw(6) << std::setfill('0') << std::hex << fillColor;

	m_shapes += stream.str();
}

void MockCanvas::DrawCircle(Point origin, double radius, uint32_t lineColor)
{
	std::ostringstream stream;
	stream << "dc" 
		<< std::setw(4) << std::setfill('0') << origin.GetX()
		<< std::setw(4) << std::setfill('0') << origin.GetY()
		<< std::setw(4) << std::setfill('0') << radius
		<< std::setw(6) << std::setfill('0') << std::hex << lineColor;

	m_shapes += stream.str();
}