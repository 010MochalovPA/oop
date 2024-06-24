#pragma once

#include <string>

class IPerson
{
public:
	virtual ~IPerson() = default;
	virtual const std::string& GetFirstName() const = 0;
	virtual const std::string& GetLastName() const = 0;
	virtual const std::string& GetMiddleName() const = 0;
	virtual const std::string& GetAddress() const = 0;
};