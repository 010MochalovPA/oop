#pragma once

#include "stdafx.h"
#include "IValue.h"
#include "AdditionalStruct.h"
#include "BasicFunction.h"

class BinaryFunction : public BasicFunction
{
public:
	BinaryFunction(IValue* leftOperand, IValue* rightOperand, BinaryFn fn)
		: m_leftOperand(leftOperand)
		, m_rightOperand(rightOperand)
		, m_fn(std::move(fn))
	{
		AddObservables(m_leftOperand);
		AddObservables(m_rightOperand);

		for (auto obs : m_observables)
		{
			obs->AddValueObserver(*this);
		}
	}

private:
	void AddValueObserver(IValueObserver& observer);
	double CalculateValue();

	IValue* m_leftOperand;
	IValue* m_rightOperand;
	BinaryFn m_fn;
};