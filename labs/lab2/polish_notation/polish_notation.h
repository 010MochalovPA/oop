#pragma once
// ������ ������ ������� ++
#include <iostream>
// ����� ������� Operation ++
enum class Operation
{
	ADDITION,
	MULTYPLY,
};

void CalculateExpression(int& result, Operation operation, const int value);
int CalculatePolishExpressionFromStream(std::istream& inputstream);
