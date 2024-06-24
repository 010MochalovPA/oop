#pragma once

#include "IPerson.h"
#include <string>

class IWorker : public IPerson
{
public:
	virtual const std::string& GetSpecialty() const = 0;
};