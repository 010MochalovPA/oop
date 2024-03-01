#pragma once

#include "stdafx.h"
#include "IStringable.h"
#include "ICanvasDrawable.h"

class IShape : public IStringable, public ICanvasDrawable
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
};