#pragma once

#include "stdafx.h"

class CValue
{
public:
	virtual double GetValue();

private:
	double m_value;
};