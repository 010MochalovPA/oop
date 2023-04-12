#include "polish_notation.h"
#include <iostream>
#include <sstream>

//inputStream ��� input

int CalculatePolishExpressionFromStream(std::istream& inputStream)
{
	char ch;
	inputStream >> ch;

	if (ch != '(')
	{
		// ���� runtime error ��� invalid argument
		throw std::runtime_error("ERROR");
	}

	inputStream >> ch;

	Operation operation; //TODO: use enum to store sign ++

	if (ch == '+')
	{
		operation = Operation::ADDITION;
	}
	else if (ch == '*')
	{
		operation = Operation::MULTYPLY;
	}
	else
	{
		throw std::runtime_error("ERROR");
	}

	int result = (operation == Operation::ADDITION) ? 0 : 1;

	if (inputStream >> ch && ch == ')')
	{
		throw std::runtime_error("ERROR");
	}

	inputStream.unget();

	while (inputStream >> ch && ch != ')')
	{
		inputStream.unget();

		if (isalpha(ch))
		{
			throw std::runtime_error("ERROR");
		}

		int value; // TODO: ����� ��������� ���������� � ������ ������� ��������� +

		if (ch == '(')
		{
			value = CalculatePolishExpressionFromStream(inputStream); // TODO: ��������� � ������������ ������� � ���-��� ������� �� ����� +
		}
		else
		{	
			inputStream >> value;
		}

		CalculateExpression(result, operation, value);
	}

	if (ch != ')')
	{
		throw std::runtime_error("ERROR");
	}

	return result;
}
// ��������� ����� ������� updateResult
void CalculateExpression(int& result, Operation operation, const int value)
{
	if (operation == Operation::ADDITION)
	{
		result += value;
		return;
	}

	result *= value;
}