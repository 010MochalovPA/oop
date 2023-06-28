#pragma once

#include "stdafx.h"

class CVariable : public CValue
{
public:
	CVariable(std::string name, double value)
	{
		m_name = name;
		m_value = value;
		m_links = {};
	}

	void AddLink(std::string name, CValue function)
	{
		m_links.insert(std::pair<std::string, CValue>(name, function));	
	}

	double GetValue() override;

private:
	std::string m_name;
	double m_value;
	std::map<std::string, CValue> m_links;
};