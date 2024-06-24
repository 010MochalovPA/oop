#pragma once

#include "IPerson.h"
#include <concepts>
#include <string>

template <typename Base>
	requires(std::derived_from<Base, IPerson>)
class PersonImpl

	: public Base
{
public:
	PersonImpl(
		const std::string& firstName,
		const std::string& lastName,
		const std::string& middleName,
		const std::string& address)
		: m_firstName(firstName)
		, m_lastName(lastName)
		, m_middleName(middleName)
		, m_address(address)
	{
	}

	const std::string& GetFirstName() const override
	{
		return m_firstName;
	}

	const std::string& GetLastName() const override
	{
		return m_lastName;
	}

	const std::string& GetMiddleName() const override
	{
		return m_middleName;
	}

	const std::string& GetAddress() const override
	{
		return m_address;
	}

	void SetFirstName(const std::string& firstName)
	{
		m_firstName = firstName;
	}

	void SetLastName(const std::string& lastName)
	{
		m_lastName = lastName;
	}

	void SetMiddleName(const std::string& middleName)
	{
		m_middleName = middleName;
	}

	void SetAddress(const std::string& address)
	{
		m_address = address;
	}

private:
	std::string m_firstName;
	std::string m_lastName;
	std::string m_middleName;
	std::string m_address;
};