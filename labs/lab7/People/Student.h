#pragma once

#include "StudentImpl.h"
#include "IStudent.h"

class Student : public StudentImpl<IStudent>
{
public:
	Student(
		const std::string& firstName,
		const std::string& lastName,
		const std::string& middleName, 
		const std::string& address,
		const std::string& universityName,
		const std::string& studentID
	)
		: StudentImpl<IStudent>(firstName, lastName, middleName, address, universityName, studentID)
	{
	}
};