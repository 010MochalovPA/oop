#include "stdafx.h"

double CVariable::GetValue() const
{
	return m_value;
}

void CVariable::SetValue(const double value)
{
	m_value = value;
}