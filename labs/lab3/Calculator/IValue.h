#pragma once

#include "stdafx.h"

class IValue
{
public:
	virtual double Get() const = 0;
};