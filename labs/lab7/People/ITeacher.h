#pragma once

#include "IPerson.h"
#include <string>

class ITeacher : public IPerson
{
public:
	virtual const std::string& GetSubjectName() const = 0;
};