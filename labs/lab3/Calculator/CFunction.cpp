#include "stdafx.h"

double CFunction::GetValue() const
{
	if (m_isSingleFunction)
	{
		return m_operand1.GetValue();
	}
}