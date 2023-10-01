#include "Calculator.h"

//namespace
//{
//
//}

bool Calculator::CreateVar(const std::string& name, const std::string& value)
{
	if (IsExists(name))
	{
		return false;
	}

	if (value == "NAN")
	{
		m_variables.insert(std::pair<std::string, Variable>(name, Variable(NAN)));
		return true;
	}
	
	if (IsExists(value))
	{
		if (auto it = m_variables.find(value); it != m_variables.end())
		{
			m_variables.insert(std::pair<std::string, Variable>(name, Variable(it->second.Get())));
			return true;
		}

		if (auto it = m_functions.find(value); it != m_functions.end())
		{
			m_variables.insert(std::pair<std::string, Variable>(name, Variable(it->second.get()->Get())));
			return true;
		}

		return false;
	}

	if (IsNumber(value))
	{
		m_variables.insert(std::pair<std::string, Variable>(name, Variable(stod(value))));
		return true;
	}

	return false;
}

bool Calculator::EditVar(const std::string& name, const std::string& value)
{
	if (IsExists(value))
	{
		if (auto it = m_variables.find(name); it != m_variables.end())
		{
			auto identifierValue = GetIdentifier(value);

			it->second.Set(identifierValue.value()->Get());
			return true;
		}

		return false;
	}

	if (IsNumber(value))
	{
		
		if (auto it = m_variables.find(name); it != m_variables.end())
		{
			it->second.Set(stod(value));
			return true;
		}
	}
	
	return false;
}

bool Calculator::CreateUnaryFunction(const std::string& name, const std::string& operand)
{
	if (IsExists(name) || !IsExists(operand))
	{
		return false;
	}

	if (auto it = m_variables.find(operand); it != m_variables.end())
	{
		m_functions.insert({name, std::make_unique<UnaryFunction>(&it->second)});
		return true;
	}

	return false;
}

bool Calculator::CreateBinaryFunction(
	const std::string& name,
	const std::string& operand1,
	const std::string& operand2,
	std::function<double(double, double)> fn
)
{
	if (IsExists(name) || !IsExists(operand1) || !IsExists(operand2))
	{
		return false;
	}

	auto leftOperand = GetIdentifier(operand1);
	auto rightOperand = GetIdentifier(operand2);

	m_functions.insert({ name, std::make_unique<BinaryFunction>(leftOperand.value(), rightOperand.value(), fn) });
	return true;
}

std::optional<IValue*> Calculator::GetIdentifier(const std::string& name)
{
	if (auto it = m_variables.find(name); it != m_variables.end())
	{
		return { &it->second };
	}

	if (auto it = m_functions.find(name); it != m_functions.end())
	{
		return { it->second.get() };
	}

	return std::nullopt;
}

bool Calculator::AssignLet(const std::string& name, const std::string& value)
{
	if (IsExists(name))
	{
		return EditVar(name, value);
	}
	else
	{
		return CreateVar(name, value);
	}
}

std::map<std::string, Variable> Calculator::GetVariables()
{
	return m_variables;
}

std::map<std::string, double> Calculator::GetFunctions()
{
	std::map<std::string, double> functionValues {};
	for (auto &func: m_functions)
	{
		auto f = func.second.get();
		const double value = f->Get();

		functionValues[func.first] = value;
	}

	return functionValues;
}

bool Calculator::IsValidName(const std::string& name) 	// TODO: use REGEXP +++  // TODO: move to namespace
{
	return std::regex_match(name, std::regex("^[a-zA-Z]+[0-9a-zA-Z]*$"));
}

bool Calculator::IsExists(const std::string& name) 
{
	if (m_variables.contains(name) || m_functions.contains(name)) // TODO:  simplify
	{
		return true;
	}

	return false;
}

bool Calculator::IsNumber(const std::string& value) // TODO: move to namespace
{
	return std::regex_match(value, std::regex("^[-+]?(0|[1-9]\\d*)([.]\\d+)?$"));
}

double Calculator::GetIdentifierValue(const std::string& name)
{
	if (m_variables.contains(name))
	{
		return m_variables.find(name)->second.Get();
	}

	auto func = m_functions.find(name)->second.get();
	return func->Get();
}

bool Calculator::IsIdentifier(const std::string& name)
{
	return IsExists(name);
}