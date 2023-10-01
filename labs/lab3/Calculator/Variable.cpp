#include "stdafx.h"
#include "Variable.h"

double Variable::Get() const
{
	return m_value;
}

void Variable::Set(double value)
{
	m_value = value;
}