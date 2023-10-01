#include "stdafx.h"
#include "BinaryFunction.h"

double BinaryFunction::Get() const
{
	return m_fn(m_leftOperand->Get(), m_rightOperand->Get());
}