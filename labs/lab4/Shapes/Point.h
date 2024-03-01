#pragma once

#include "stdafx.h"
#include "IStringable.h"

class Point : public IStringable
{
public:
	Point(const double x = 0, const double y = 0)
	{
		m_x = x;
		m_y = y;
	}

	std::string ToString() const override;
	double GetX() const;
	double GetY() const;

	double m_x;
	double m_y;
};