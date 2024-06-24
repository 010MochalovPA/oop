#pragma once

#include "IStudent.h"
#include <string>

class IAdvancedStudent : public IStudent
{
public:
	virtual const std::string& GetDissertationTopic() const = 0;
};