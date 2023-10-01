#include "stdafx.h"
#include "Variable.h"

std::unordered_set<IValue*> Variable::GetObservables(){
	std::unordered_set<IValue*> observables;
	observables.insert(this);
	return observables;
};

void Variable::AddValueObserver(IValueObserver& observer)
{
	m_observers.insert(&observer);
}

double Variable::Get()
{
	return m_value;
}

void Variable::Set(double value)
{
	for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
	{
		(*it)->OnValueChange();
	}
	
	m_value = value;
}