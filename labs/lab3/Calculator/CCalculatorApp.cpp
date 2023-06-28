#include "CCalculatorApp.h"
#include "stdafx.h"

CCalculatorApp::CCalculatorApp(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "var", [this](const std::string& args) { return CreateVar(args); } },
		  { "let", [this](const std::string& args) { return CreateLet(args); } },
		  { "fn", [this](const std::string& args) { return CreateFunction(args); } },
		  { "print", [this](const std::string& args) { return PrintIdentifier(args); } },
		  { "printvars", [this](const std::string& args) { return PrintVariables(args); } },
		  { "printfns", [this](const std::string& args) { return PrintFunctions(args); } },
		  { "help", [this](const std::string& args) { return Help(args); } } })
{
}//TODO: Unknown command! заменить на осмысленный текст ошибки
//TODO: > fn woo = a / 0
//		> print woo
//		woo : -inf

bool CCalculatorApp::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);

	std::istringstream stream(commandLine);

	std::string action;
	std::string args;
	std::getline(stream, action, ' ');

	args = std::getline(stream, args) ? args : "";
	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(args);
	}

	return false;
}

bool CCalculatorApp::CreateVar(const std::string& args)
{
	CCalculator::Function func = ParseArgs(args);
	if (func.name.empty())
	{
		return false;
	}

	return m_calculator.CreateVar(func.name, "NAN");
}

bool CCalculatorApp::CreateLet(const std::string& args)
{
	return true;
	/*CCalculator::Function func = ParseArgs(args);

	if (func.name.empty() || func.operand1.empty())
	{
		return false;
	}

	return m_calculator.CreateLet(func.name, func.operand1);*/
}

bool CCalculatorApp::CreateFunction(const std::string& args)
{
	return true;
	/*CCalculator::Function func = ParseArgs(args);
	if (func.name.empty())
	{
		return false;
	}

	CCalculator::Function function = { func.name, func.operand1, func.operand2, func.operation };

	return m_calculator.CreateFunction(func.name, function);*/
}

bool CCalculatorApp::PrintVariables(const std::string& /*args*/)
{
	std::map<std::string, CVariable> variables = m_calculator.GetVariables();
	
	for (auto var : variables)
	{
		if (std::isnan(var.second.GetValue()))
		{
			m_output << var.first << " : nan" << std::endl;
		}
		else
		{
			m_output << var.first << " : " << std::fixed << std::setprecision(2) << var.second.GetValue() << std::endl;
		}
	}

	return true;
}

bool CCalculatorApp::PrintFunctions(const std::string& /*args*/)
{
	return true;
	/*std::map<std::string, double> functions = m_calculator.GetFunctions();
	
	for (const auto func : functions)
	{
		if (std::isnan(func.second))
		{
			m_output << func.first << " : nan" << std::endl;
		}
		else
		{
			m_output << func.first << " : " << std::fixed << std::setprecision(2) << func.second << std::endl;
		}
	}

	return true;*/
}

bool CCalculatorApp::PrintIdentifier(const std::string& args)
{
	return true;
	/*CCalculator::Function func = ParseArgs(args);
	if (func.name.empty())
	{
		return false;
	}

	std::string name = func.name;
	auto value = m_calculator.GetIdentifierValue(func.name);

	if (std::isnan(value))
	{
		m_output << name << " : nan" << std::endl;
	}
	else
	{
		m_output << name << " : " << std::fixed << std::setprecision(2) << value << std::endl;
	}

	return true;*/
}

CCalculator::Function CCalculatorApp::ParseArgs(const std::string& input)//TODO: не понятно что возвращаем и запрашиваем
{
	CCalculator::Function func = { "", "0", "0", CCalculator::OPERATION::Addition };
	std::stringstream stream(input);

	stream >> func.name;
	if (func.name.empty())
	{
		return func;
	}

	std::string symbol;
	stream >> symbol;
	if (symbol != "=")
	{
		return func;
	}

	stream >> func.operand1;

	if (func.operand1.empty())
	{
		return func;
	}
	
	char operation;
	stream >> operation;

	switch (operation)
	{
		case '+':
			func.operation = CCalculator::OPERATION::Addition;
			break;
		case '*':
			func.operation = CCalculator::OPERATION::Multiply;
			break;
		case '-':
			func.operation = CCalculator::OPERATION::Difference;
			break;
		case '/':
			func.operation = CCalculator::OPERATION::Division;
			break;
		default:
			func.operation = CCalculator::OPERATION::Addition;
			return func;
	}
	
	stream >> func.operand2;

	return func;
}

bool CCalculatorApp::Help(const std::string& /*args*/) const
{
	m_output << "- var <identifier> " << std::endl
			 << "- let <identifier1> = <floating point number> or let<identifier1> = <identifier2>" << std::endl
			 << "- fn <identifier1> = <identifier2> or fn<identifier1> = <identifier2><operation><identifier3>" << std::endl
			 << "- print <identifier>" << std::endl
			 << "- printvars" << std::endl
			 << "- printfns" << std::endl;

	return true;
}