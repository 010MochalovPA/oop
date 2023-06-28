#include "stdafx.h"
#include "CCalculator.h"

bool CCalculator::CreateVar(const std::string& name, const std::string& value)
{
	std::optional<CValue> newValue = GetValue(value);

	if (newValue.has_value())
	{
		CVariable newVariable{ name, newValue.value().GetValue() };
		m_variables.insert(std::pair<std::string, CVariable>(name, newVariable));
		return true;
	}
	else
	{
		CVariable newVariable{ name, value == "NAN" ? NAN : stod(value) };
		m_variables.insert(std::pair<std::string, CVariable>(name, newVariable));
		return true;
	}
}

std::map<std::string, CVariable> CCalculator::GetVariables()
{
	return m_variables;
}

bool CCalculator::IsValidName(const std::string& name)
{
	// TODO: use REGEXP
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
	if (m_variables.contains(name))// || m_functions.contains(name))
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

bool CCalculator::IsExists(const std::string& name) 
{
	if (m_variables.contains(name))// || m_functions.contains(name))
	{
		return true;
	}

	return false;
}

std::optional<CVariable> CCalculator::GetValue(const std::string& name)
{
	std::optional<CVariable> value;
	if (m_variables.contains(name))
	{
		value = m_variables.find(name)->second;
	}

	return { value };	
}