#include "CalculatorApp.h"
#include "stdafx.h"
#include "AdditionalStruct.h"

CalculatorApp::CalculatorApp(Calculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "var", [this](const std::string& args) { return CreateVar(args); } },
		  { "let", [this](const std::string& args) { return AssignLet(args); } },
		  { "fn", [this](const std::string& args) { return CreateFunction(args); } },
		  { "print", [this](const std::string& args) { return PrintIdentifier(args); } },
		  { "printvars", [this](const std::string& args) { return PrintVariables(args); } },
		  { "printfns", [this](const std::string& args) { return PrintFunctions(args); } },
		  { "help", [this](const std::string& args) { return Help(args); } } })
{
}

bool CalculatorApp::HandleCommand()
{
	std::string line;
	std::getline(m_input, line);

	std::istringstream stream(line);

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

bool CalculatorApp::IsOperation(char op)
{
	return op == '+' || op == '-' || op == '*' || op == '/';
}

bool CalculatorApp::CreateVar(const std::string& args)
{
	std::stringstream stream(args);

	std::string name;
	stream >> name;

	if (!std::regex_match(name, std::regex("^[a-zA-Z]+[0-9a-zA-Z]*$")))
	{
		return false;
	}

	std::string rest;
	stream >> rest;

	if (!rest.empty())
	{
		return false;
	}

	return m_calculator.CreateVar(name, "NAN");
}

bool CalculatorApp::AssignLet(const std::string& args)
{
	std::stringstream stream(args);
	
	std::string name;
	stream >> name;

	if (!std::regex_match(name, std::regex("^[a-zA-Z]+[0-9a-zA-Z]*$")))
	{
		return false;
	}

	char separator;

	if (stream >> separator && separator != '=')
	{
		return false;
	}

	std::string value;
	stream >> value;

	if (!std::regex_match(value, std::regex("^([a-zA-Z]+[0-9a-zA-Z]*|[-+]?(0|[1-9]\\d*)([.]\\d+)?)$"))) // move regex string to another file. Make const
	{
		return false;
	}

	std::string rest;
	stream >> rest;

	if (!rest.empty())
	{
		return false;
	}

	return m_calculator.AssignLet(name, value);
}

bool CalculatorApp::CreateFunction(const std::string& args)
{
	std::stringstream stream(args);

	std::string name;
	stream >> name;

	if (!std::regex_match(name, std::regex("^[a-zA-Z]+[0-9a-zA-Z]*$")))
	{
		return false;
	}

	char separator;

	if (stream >> separator && separator != '=')
	{
		return false;
	}
	
	std::string operand1;
	stream >> operand1;

	if (!std::regex_match(operand1, std::regex("^[a-zA-Z]+[0-9a-zA-Z]*$")))
	{
		return false;
	}

	char operation = 0;

	if (!(stream >> operation))
	{
		return m_calculator.CreateUnaryFunction(name, operand1);
	}

	if (!IsOperation(operation))
	{
		std::cout << "if (!IsOperation(operation))" << std::endl;
		return false;
	}

	std::string operand2;
	stream >> operand2;

	if (!std::regex_match(operand2, std::regex("^[a-zA-Z]+[0-9a-zA-Z]*$")))
	{
		return false;
	}

	std::string rest;
	stream >> rest;

	if (rest.empty())
	{
		const BinaryFn fn = GetBinaryFn(operation);
		return m_calculator.CreateBinaryFunction(name, operand1, operand2, fn);
	}

	return false;
}

BinaryFn CalculatorApp::GetBinaryFn(char op)
{
	switch (op)
	{
	case '+':
		return [](double a, double b) { return a + b; };
		break;
	case '-':
		return [](double a, double b) { return a - b; };
		break;
	case '*':
		return [](double a, double b) { return a * b; };
		break;
	case '/':
		return [](double a, double b) { return a / b; };
		break;
	default:
		return [](double a, double b) { return NAN; };
	}
}

bool CalculatorApp::PrintVariables(const std::string& /*args*/)
{
	std::map<std::string, Variable> variables = m_calculator.GetVariables();
	
	for (auto variable : variables)
	{
		if (std::isnan(variable.second.Get()))
		{
			m_output << variable.first << " : nan" << std::endl;
		}
		else
		{
			m_output << variable.first << " : " << std::fixed << std::setprecision(2) << variable.second.Get() << std::endl;
		}
	}

	return true;
}

bool CalculatorApp::PrintFunctions(const std::string& /*args*/)
{
	std::map<std::string, double> functions = m_calculator.GetFunctions();
	
	for (auto& func : functions)
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

	return true;
}

bool CalculatorApp::PrintIdentifier(const std::string& args)
{
	std::stringstream stream(args);
	std::string name;
	stream >> name;

	if (!std::regex_match(name, std::regex("^[a-zA-Z]+[0-9a-zA-Z]*$")))
	{
		return false;
	}

	std::string rest = std::getline(stream, rest) ? rest : "";

	if (!rest.empty() || !m_calculator.IsExists(name))
	{
		return false;
	}

	auto value = m_calculator.GetIdentifierValue(name);

	if (std::isnan(value))
	{
		m_output << name << " : nan" << std::endl;
	}
	else
	{
		m_output << name << " : " << std::fixed << std::setprecision(2) << value << std::endl;
	}

	return true;
}

bool CalculatorApp::Help(const std::string& /*args*/) const
{
	m_output << "- var <identifier> " << std::endl
			 << "- let <identifier1> = <floating point number> or let<identifier1> = <identifier2>" << std::endl
			 << "- fn <identifier1> = <identifier2> or fn<identifier1> = <identifier2><operation><identifier3>" << std::endl
			 << "- print <identifier>" << std::endl
			 << "- printvars" << std::endl
			 << "- printfns" << std::endl;

	return true;
}