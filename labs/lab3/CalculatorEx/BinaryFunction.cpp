#include "stdafx.h"
#include "BinaryFunction.h"

void BinaryFunction::AddValueObserver(IValueObserver& observer)
{
	m_leftOperand->AddValueObserver(observer);
	m_rightOperand->AddValueObserver(observer);
}

double BinaryFunction::CalculateValue()
{
	m_value = m_fn(m_leftOperand->Get(), m_rightOperand->Get()) ;
	return m_value.value();
}