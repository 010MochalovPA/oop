#pragma once

#include "stdafx.h"
#include "AdditionalStruct.h"
#include "IValue.h"
#include "IValueObserver.h"

class BasicFunction : public IValue, public IValueObserver
{
public:
	void OnValueChange() override;
	double Get() override;
	std::unordered_set<IValue*> GetObservables() override;

protected:
	std::optional<double> m_value = std::nullopt;
	std::unordered_set<IValue*> m_observables;
	void AddObservables(IValue* value);

private:
	virtual double CalculateValue() = 0;
};