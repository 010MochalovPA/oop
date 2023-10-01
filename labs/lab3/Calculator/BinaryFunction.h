#pragma once

#include "stdafx.h"
#include "IValue.h"
#include "AdditionalStruct.h"

class BinaryFunction : public IValue
{
public:
	BinaryFunction(IValue* leftOperand, IValue* rightOperand, BinaryFn fn)
		: m_leftOperand(leftOperand)
		, m_rightOperand(rightOperand)
		, m_fn(std::move(fn))
	{
	}

	double Get() const override;

private:
	IValue* m_leftOperand;
	IValue* m_rightOperand;
	BinaryFn m_fn;
};