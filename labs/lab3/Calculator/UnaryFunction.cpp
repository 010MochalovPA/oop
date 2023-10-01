#include "stdafx.h"
#include "UnaryFunction.h"

double UnaryFunction::Get() const
{
	return m_operand->Get();
}