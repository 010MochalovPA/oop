#pragma once
// убрать лишние инклуды
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
// стоит назвать 
enum class Sign
{
	ADDITION,
	MULTYPLY,
};

void CalculateExpression(int& result, Sign sign, const int value);
int CalculatePolishExpressionFromStream(std::istream& inputstream);
