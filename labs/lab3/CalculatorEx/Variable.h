#pragma once

#include "stdafx.h"
#include "IValue.h"
#include "IValueObserver.h"

class Variable : public IValue
{
public:
	Variable(double value)
		: m_value(value)
	{
	}

	void Set(double value);
	double Get() override;
	void AddValueObserver(IValueObserver& observer) override;
	std::unordered_set<IValue*> GetObservables() override;

private:
	std::unordered_set<IValueObserver*> m_observers;
	double m_value;
	std::unordered_set<IValue*> m_observables;
};