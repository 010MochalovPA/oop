#pragma once

#include "PersonImpl.h"
#include <string>

template <typename Base>
class StudentImpl : public PersonImpl<Base>
{
public:
	StudentImpl(
		const std::string& firstName,
		const std::string& lastName,
		const std::string& middleName,
		const std::string& address,
		const std::string& universityName,
		const std::string& studentID
	)
		: PersonImpl<Base>(firstName, lastName, middleName, address)
		, m_universityName(universityName)
		, m_studentID(studentID)
	{
	}

	const std::string& GetUniversityName() const override
	{
		return m_universityName;
	}

	const std::string& GetStudentID() const override
	{
		return m_studentID;
	}

	void SetUniversityName(const std::string& universityName)
	{
		m_universityName = universityName;
	}

	void SetStudentID(const std::string& studentID)
	{
		m_studentID = studentID;
	}

private:
	std::string m_universityName;
	std::string m_studentID;
};