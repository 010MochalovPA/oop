#pragma once

#include "stdafx.h"

class CValue
{
public:
	virtual double GetValue() const;

private:
	double m_value;
};
