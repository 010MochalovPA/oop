#pragma once

#include "stdafx.h"
#include "IValue.h"
#include "BasicFunction.h"

class UnaryFunction : public BasicFunction
{
public:
	UnaryFunction(IValue* operand)
		: m_operand(operand)
	{	
		AddObservables(m_operand);

		for (auto it = m_observables.begin(); it != m_observables.end(); ++it)
		{
			(*it)->AddValueObserver(*this);
		}
	}

private:
	void AddValueObserver(IValueObserver& observer);
	double CalculateValue();
	IValue* m_operand;
};