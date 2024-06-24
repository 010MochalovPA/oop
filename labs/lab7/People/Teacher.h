#pragma once

#include "PersonImpl.h"
#include "ITeacher.h"

class Teacher : public PersonImpl<ITeacher>
{
public:
	Teacher(
		const std::string& firstName,
		const std::string& lastName,
		const std::string& middleName,
		const std::string& address,
		const std::string& subjectName
	)
		: PersonImpl<ITeacher>(firstName, lastName, middleName, address)
		, m_subjectName(subjectName)
	{
	}

	const std::string& GetSubjectName() const override
	{
		return m_subjectName;
	}

	void SetSubjectName(const std::string& subjectName)
	{
		m_subjectName = subjectName;
	}

private:
	std::string m_subjectName;
};
