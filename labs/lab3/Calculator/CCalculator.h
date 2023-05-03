#pragma once

#include "stdafx.h"

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

	bool CreateVar(const std::string& name);
	bool CreateVar(const std::string& name, const std::string& value);

	bool CreateLet(const std::string& name, const std::string& value);
	bool CreateFunction(const std::string& name, const Function& function);
	
	
	double GetIdentifierValue(const std::string& name);
	std::map<std::string, double> GetVariables();
	std::map<std::string, double> GetFunctions();

private:

	double CalculateFunction(const Function& func);
	bool EditVar(const std::string& name, const std::string& value);
	bool IsUsed(const std::string& name);
	bool IsValidName(const std::string& name);
	bool IsValidIdentifier(const std::string& name);

	std::map<std::string, double> m_variables = {};
	std::map<std::string, Function> m_functions = {};
};