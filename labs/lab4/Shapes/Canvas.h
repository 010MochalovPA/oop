#pragma once

#include "ICanvas.h"
#include "ICanvasDrawable.h"
#include "Point.h"
#include "SFML/Graphics.hpp"

class Canvas: public ICanvas
{
public:
	Canvas() = default;
	void Draw() const override;
	void DrawLine(Point from, Point to, uint32_t lineColor) override;
	void FillPolygon(std::vector<Point> points, uint32_t fillColor) override;
	void FillCircle(Point origin, double radius, uint32_t fillColor) override;
	void DrawCircle(Point origin, double radius, uint32_t lineColor) override;
	void ClearShapes() override;

private:
	std::vector<sf::Drawable*> m_shapes;
};
