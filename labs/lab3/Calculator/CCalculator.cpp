#include "stdafx.h"
#include "CCalculator.h"

bool CCalculator::IsValidName(const std::string& name)
{
	if (name.empty() || std::isdigit(name[0]))
	{
		return false;
	}

	for (char ch : name)
	{
		if (!std::isdigit(ch) && !std::isalpha(ch))
		{
			return false;
		}
	}

	return true;
}

bool CCalculator::IsValidIdentifier(const std::string& name)
{
	if (m_variables.contains(name) || m_functions.contains(name))
	{
		return true;
	}

	std::istringstream stream(name);

	double value;

	if (!(stream >> value))
	{
		return false;
	}

	return true;
}

bool CCalculator::IsUsed(const std::string& name)
{
	if (m_variables.contains(name) || m_functions.contains(name))
	{
		return true;
	}

	return false;
}

bool CCalculator::CreateVar(const std::string& name)
{
	if (!IsValidName(name) || IsUsed(name))
	{
		return false;
	}

	m_variables.insert(std::pair<std::string, double>(name, NAN));
	return true;
}

bool CCalculator::CreateVar(const std::string& name, const std::string& value)
{
	if (!IsValidName(name) || IsUsed(name))
	{
		return false;
	}

	m_variables.insert(std::pair<std::string, double>(name, GetIdentifierValue(value)));
	return true;
}

bool CCalculator::EditVar(const std::string& name, const std::string& value)
{
	if (IsUsed(value))
	{
		if (m_variables.contains(value))
		{
			m_variables.find(name)->second = m_variables.find(value)->second;
		}
		else
		{
			m_functions.find(name)->second = m_functions.find(value)->second;
		}
	}
	else
	{
		m_variables.find(name)->second = stod(value);
	}
	return true;
}

bool CCalculator::CreateLet(const std::string& name, const std::string& value)
{
	if (!IsValidName(name) || !IsValidIdentifier(value))
	{
		return false;
	}

	if (m_variables.contains(name))
	{
		EditVar(name, value);
	}
	else
	{
		CreateVar(name, value);
	}

	return true;
}

bool CCalculator::CreateFunction(const std::string& name, const Function& func)
{
	if (!IsValidName(name) || IsUsed(name))
	{
		return false;
	}
	
	if (!IsValidIdentifier(func.operand1))
	{
		return false;
	}

	Function function = { name, func.operand1, func.operand2, func.operation };

	m_functions.insert(std::pair<std::string, Function>(name, function));
}

std::map<std::string, double> CCalculator::GetVariables()
{
	return m_variables;
}

std::map<std::string, double> CCalculator::GetFunctions()
{
	std::map<std::string, double> function{};

	for (auto func : m_functions)
	{
		function.insert(std::pair<std::string, double>(func.first, CalculateFunction(func.second)));
	}

	return function;
}


double CCalculator::GetIdentifierValue(const std::string& name)
{
	if (IsUsed(name))
	{
		if (m_variables.contains(name))
		{
			return  m_variables.find(name)->second ;
		}
		else
		{
			return CalculateFunction(m_functions.find(name)->second);
		}	
	}
	return stod(name);
}

double CCalculator::CalculateFunction(const Function& func)
{	
	auto value1 = GetIdentifierValue(func.operand1);
	auto value2 = GetIdentifierValue(func.operand2);

	if (std::isnan(value1) || std::isnan(value2))
	{
		return NAN;
	}

	switch (func.operation)
	{
	case OPERATION::Addition:
		return value1 + value2;

	case OPERATION::Multiply:
		return value1 * value2;

	case OPERATION::Division:
		return value1 / value2;
	
	case OPERATION::Difference:
		return value1 - value2;
	}
}