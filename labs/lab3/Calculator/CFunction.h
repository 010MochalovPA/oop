#pragma once

#include "stdafx.h"

class CFunction : public CValue
{
public:
	CFunction(CValue* operand1, CValue* operand2, const CCalculator::OPERATION& operation)
	{
		m_operand1 = operand1;
		m_operand2 = operand2;
		m_operation = operation;
		bool m_isSingleFunction = false;
	}

	CFunction(CValue* operand1)
	{
		m_operand1 = operand1;
	}

	double GetValue() const override;

private:
	CValue* m_operand1 = nullptr;
	CValue* m_operand2 = nullptr;
	CCalculator::OPERATION m_operation;
	bool m_isSingleFunction = true;
};