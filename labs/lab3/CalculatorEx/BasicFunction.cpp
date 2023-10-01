#include "stdafx.h"
#include "BasicFunction.h"

std::unordered_set<IValue*> BasicFunction::GetObservables()
{
	return m_observables;
};

void BasicFunction::AddObservables(IValue* value)
{
	std::unordered_set<IValue*> observables = value->GetObservables();
	m_observables.insert(observables.begin(), observables.end());
}

void BasicFunction::OnValueChange()
{
	this->m_value = std::nullopt;
}

double BasicFunction::Get()
{
	if (m_value.has_value())
	{
		return m_value.value();
	}

	return CalculateValue();
}