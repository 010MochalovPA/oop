#pragma once

#include "ISolidShape.h"
#include "Point.h"

class Rectangle : public ISolidShape
{
public:
	Rectangle(Point leftTop, Point rightBottom, uint32_t outlineColor = 0, uint32_t fillColor = 0)
		: m_leftTop(leftTop)
		, m_rightBottom(rightBottom)
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
		, m_title("Rectangle")
	{
	}

	double GetPerimeter() const override;
	double GetArea() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	std::string ToString() const override;
	Point GetLeftTop() const;
	Point GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	void Draw(ICanvas& canvas) const override;

private:
	Point m_leftTop;
	Point m_rightBottom;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
	std::string m_title;
};