#pragma once

#include "stdafx.h"
#include "Variable.h"
#include "UnaryFunction.h"
#include "BinaryFunction.h"
#include "AdditionalStruct.h"

class Calculator
{
public:
	Calculator()
	{
	}
	
	bool IsValidName(const std::string& name);
	bool IsIdentifier(const std::string& name);
	bool IsNumber(const std::string& value);
	bool IsExists(const std::string& name);
	double GetIdentifierValue(const std::string& name);
	std::optional<IValue*>GetIdentifier(const std::string& name);
	bool CreateVar(const std::string& name, const std::string& value);
	bool EditVar(const std::string& name, const std::string& value);
	bool CreateUnaryFunction(const std::string& name, const std::string& operand);
	bool CreateBinaryFunction(const std::string& name, const std::string& operand1, const std::string& operand2, std::function<double(double, double)> fn);
	bool AssignLet(const std::string& name, const std::string& value);
	std::map<std::string, Variable> GetVariables();
	std::map<std::string, double> GetFunctions();

private:
	std::map<std::string, Variable> m_variables;
	std::map<std::string, std::unique_ptr<IValue>> m_functions;
};