#pragma once

#include "ICanvas.h"
#include "ICanvasDrawable.h"
#include "Point.h"
#include "SFML/Graphics.hpp"

class MockCanvas : public ICanvas
{
public:
	void Draw() const override;
	std::string GetShapes() const;
	void DrawLine(Point from, Point to, uint32_t lineColor) override;
	void FillPolygon(std::vector<Point> points, uint32_t fillColor) override;
	void FillCircle(Point origin, double radius, uint32_t fillColor) override;
	void DrawCircle(Point origin, double radius, uint32_t lineColor) override;
	void ClearShapes() override
	{
		// Простая заглушка
	}

private:
	std::string m_shapes;
};
