#pragma once

#include "stdafx.h"
#include "CVariable.h"

class CCalculator
{
public:
	const enum class OPERATION 
	{
		Addition = '+',
		Multiply = '*',
		Division = '/',
		Difference = '-'
	};

	using Function = struct
	{
		std::string name;
		std::string operand1;
		std::string operand2;
		OPERATION operation;
	};

	CCalculator()
	{
		m_variables = {};
		m_functions = {};
	}
	
	bool IsValidName(const std::string& name);
	bool IsValidIdentifier(const std::string& name);
	bool IsExists(const std::string& name);
	std::optional<CVariable> GetValue(const std::string& name);
	bool CreateVar(const std::string& name, const std::string& value);
	std::map<std::string, CVariable> GetVariables();
	//std::map<std::string, double> GetFunctions();

private:


	std::map<std::string, CVariable> m_variables;
	std::map<std::string, CValue> m_functions;
};