#pragma once

#include "IShape.h"
#include "Point.h"

class LineSegment : public IShape
{
public:
	LineSegment(Point startPoint, Point endPoint, uint32_t color = 0)
		: m_startPoint(startPoint)
		, m_endPoint(endPoint)
		, m_outlineColor(color)
		, m_title("Line")
	{
	}

	double GetPerimeter() const override;
	double GetArea() const override;
	Point GetStartPoint() const;
	Point GetEndPoint() const;
	uint32_t GetOutlineColor() const override;
	std::string ToString() const override;

	void Draw(ICanvas& canvas) const override;

private:
	Point m_startPoint;
	Point m_endPoint;
	uint32_t m_outlineColor;
	std::string m_title;
};