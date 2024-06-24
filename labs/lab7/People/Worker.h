#pragma once

#include "PersonImpl.h"
#include "IWorker.h"

class Worker : public PersonImpl<IWorker>
{
public:
	Worker(
		const std::string& firstName,
		const std::string& lastName,
		const std::string& middleName,
		const std::string& address,
		const std::string& specialty
	)
		: PersonImpl<IWorker>(firstName, lastName, middleName, address)
		, m_specialty(specialty)
	{
	}

	const std::string& GetSpecialty() const override
	{
		return m_specialty;
	}

	void SetSpecialty(const std::string& specialty)
	{
		m_specialty = specialty;
	}

private:
	std::string m_specialty;
};
