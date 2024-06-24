#pragma once

#include "StudentImpl.h"
#include "IAdvancedStudent.h"

class AdvancedStudent : public StudentImpl<IAdvancedStudent>
{
public:
	AdvancedStudent(
		const std::string& firstName,
		const std::string& lastName,
		const std::string& middleName,
		const std::string& address,
		const std::string& universityName,
		const std::string& studentID,
		const std::string& dissertationTopic
	)
		: StudentImpl<IAdvancedStudent>(firstName, lastName, middleName, address, universityName, studentID)
		, m_dissertationTopic(dissertationTopic)
	{
	}

	const std::string& GetDissertationTopic() const override
	{
		return m_dissertationTopic;
	}

	void SetDissertationTopic(const std::string& dissertationTopic)
	{
		m_dissertationTopic = dissertationTopic;
	}

private:
	std::string m_dissertationTopic;
};
