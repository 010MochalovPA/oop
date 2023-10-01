#pragma once

#include "stdafx.h"
#include "IValue.h"

class Variable : public IValue
{
public:
	Variable(double value)
	{
		m_value = value;
	}

	void Set(double value);
	double Get() const override;

private:
	double m_value;
};