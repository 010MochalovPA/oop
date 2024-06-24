#pragma once

#include "PersonImpl.h"
#include "IPupil.h"

class Pupil : public PersonImpl<IPupil>
{
public:
	Pupil(
		const std::string& firstName,
		const std::string& lastName,
		const std::string& middleName,
		const std::string& address,
		const std::string& schoolName,
		const std::string& className
	)
		: PersonImpl<IPupil>(firstName, lastName, middleName, address)
		, m_schoolName(schoolName)
		, m_className(className)
	{
	}

	const std::string& GetSchoolName() const override
	{
		return m_schoolName;
	}

	const std::string& GetClassName() const override
	{
		return m_className;
	}

	void SetSchoolName(const std::string& schoolName)
	{
		m_schoolName = schoolName;
	}

	void SetClassName(const std::string& className)
	{
		m_className = className;
	}

private:
	std::string m_schoolName;
	std::string m_className;
};
