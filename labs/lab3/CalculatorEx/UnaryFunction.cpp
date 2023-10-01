#include "stdafx.h"
#include "UnaryFunction.h"

void UnaryFunction::AddValueObserver(IValueObserver& observer)
{
	m_operand->AddValueObserver(observer);
}

double UnaryFunction::CalculateValue()
{
	m_value = m_operand->Get();
	return m_value.value();
}