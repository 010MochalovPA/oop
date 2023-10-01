#pragma once

#include "stdafx.h"

using BinaryFn = std::function<double(double, double)>;

const enum class OPERATION {
	Addition = '+',
	Multiply = '*',
	Division = '/',
	Difference = '-',
};

using UnaryArgs = struct
{
	std::string name;
	double value;
};