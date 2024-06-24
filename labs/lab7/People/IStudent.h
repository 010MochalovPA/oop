#pragma once

#include "IPerson.h"
#include <string>

class IStudent : public IPerson
{
public:
	virtual const std::string& GetUniversityName() const = 0;
	virtual const std::string& GetStudentID() const = 0;
};