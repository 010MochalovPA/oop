#pragma once

#include "stdafx.h"

class CVariable : public CValue
{
public:
	CVariable(const double value)
	{
		m_value = value;
	}

	void SetValue(double const value);
	double GetValue() const override;

private:
	double m_value;
};