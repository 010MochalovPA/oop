#pragma once

#include "stdafx.h"
#include "IValueObserver.h"

class IValue
{
public:
	virtual double Get() = 0;
	virtual void AddValueObserver(IValueObserver& observer) = 0;
	virtual std::unordered_set<IValue*> GetObservables() = 0;
};