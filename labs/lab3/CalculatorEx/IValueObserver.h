#pragma once

#include "stdafx.h"
#include "IValue.h"

class IValueObserver
{
public:
	virtual void OnValueChange() = 0;
};