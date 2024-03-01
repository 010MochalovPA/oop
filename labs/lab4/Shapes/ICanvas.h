#pragma once

#include "stdafx.h"
#include "Point.h"

class ICanvas
{
public:
	virtual ~ICanvas(){};
	// Draw и clearShapes() удалить
	virtual void Draw() const = 0;
	virtual void DrawLine(Point from, Point to, uint32_t lineColor) = 0;
	virtual void FillPolygon(std::vector<Point> points, uint32_t fillColor) = 0;
	virtual void FillCircle(Point origin, double radius, uint32_t fillColor) = 0;
	virtual void DrawCircle(Point origin, double radius, uint32_t lineColor) = 0;
	virtual void ClearShapes() = 0;
};