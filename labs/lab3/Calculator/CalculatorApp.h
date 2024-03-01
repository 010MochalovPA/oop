#pragma once
#include "Calculator.h"
#include "stdafx.h"
#include "AdditionalStruct.h"

class CalculatorApp
{
public:
	CalculatorApp(Calculator& calculator, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool CreateVar(const std::string& args);
	bool AssignLet(const std::string& args);
	bool CreateFunction(const std::string& args);
	bool PrintVariables(const std::string& args);
	bool PrintFunctions(const std::string& args);
	bool IsOperation(char op);
	bool PrintIdentifier(const std::string& args);
	BinaryFn GetBinaryFn(char operation);
	bool Help(const std::string& args) const;

	using Handler = std::function<bool(std::string& args)>;
	using ActionMap = std::map<std::string, Handler>;

	Calculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};