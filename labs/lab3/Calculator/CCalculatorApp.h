#pragma once
#include "CCalculator.h"
#include "stdafx.h"

class CCalculatorApp
{
public:
	CCalculatorApp(CCalculator& calculator, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:

	CCalculator::Expression ParseArgs(const std::string& input);
	bool CreateVar(const std::string& args);
	bool AssignLet(const std::string& args);
	bool CreateFunction(const std::string& args);
	bool PrintVariables(const std::string& args);
	bool PrintFunctions(const std::string& args);
	bool PrintIdentifier(const std::string& args);
	bool Help(const std::string& args) const;

	using Handler = std::function<bool(std::string& args)>;
	using ActionMap = std::map<std::string, Handler>;

	CCalculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};