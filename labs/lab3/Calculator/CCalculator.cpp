#include "stdafx.h"
#include "CCalculator.h"

bool CCalculator::CreateVar(const std::string& name, const std::string& value)
{
	if (value == "NAN")
	{
		m_variables.insert(std::pair<std::string, CVariable>(name, { NAN }));
		return true;
	}
	else
	{
		m_variables.insert(std::pair<std::string, CVariable>(name, { stod(value) }));
		return true;
	}
}

bool CCalculator::EditVar(const std::string& name, const std::string& value)
{
	m_variables.at(name) = stod(value);
	return true;
}

bool CCalculator::AssignLet(const std::string& name, const std::string& value)
{
	if (IsExists(name))
	{
		EditVar(name, value);
		return true;
	}
	else
	{
		CreateVar(name, value);
		return true;
	}
}

std::map<std::string, CVariable> CCalculator::GetVariables()
{
	return m_variables;
}

std::map<std::string, double> CCalculator::GetFunctions()
{
	return m_functions;
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

bool CCalculator::IsExists(const std::string& name) 
{
	if (m_variables.contains(name) || m_functions.contains(name))
	{
		return true;
	}

	return false;
}


CVariable CCalculator::GetIdentifier(const std::string& name)
{
	if (m_variables.contains(name))
	{
		return m_variables.find(name)->second;
	}
}