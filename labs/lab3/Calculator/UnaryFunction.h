#pragma once

#include "stdafx.h"
#include "IValue.h"

class UnaryFunction : public IValue
{
public:
	UnaryFunction(IValue* operand)
	{
		m_operand = operand;
	}

	double Get() const override;

private:
	IValue* m_operand;
};