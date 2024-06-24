#pragma once

#include "IPerson.h"
#include <string>

class IPupil : public IPerson
{
public:
	virtual const std::string& GetSchoolName() const = 0;
	virtual const std::string& GetClassName() const = 0;
};