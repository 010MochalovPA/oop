#include "polish_notation.h"

//inputStream или input
int CalculatePolishExpressionFromStream(std::istream& inputstream)
{
	char ch;
	inputstream >> ch;

	if (ch != '(')
	{
		// либо runtime error или invalid argument
		throw std::exception("ERROR");
	}

	inputstream >> ch;

	Sign sign; //TODO: use enum to store sign ++

	if (ch == '+')
	{
		sign = Sign::ADDITION;
	}
	else if (ch == '*')
	{
		sign = Sign::MULTYPLY;
	}
	else
	{
		throw std::exception("ERROR");
	}

	int result = (sign == Sign::ADDITION) ? 0 : 1;

	while (inputstream >> ch && ch != ')')
	{
		inputstream.unget();

		if (isalpha(ch))// изменить условие например not is digit 
		{
			throw std::exception("ERROR");
		}

		int value; // TODO: лучше обьявлять переменные с учетом области видимости +

		if (ch == '(')
		{
			value = CalculatePolishExpressionFromStream(inputstream); // TODO: порабоать с оптимизацией условий и кол-вом выходов из цикла +
		}
		else
		{	
			inputstream >> value;
		}

		CalculateExpression(result, sign, value);
	}

	if (ch != ')')
	{
		throw std::exception("ERROR");
	}

	return result;
}
// возмоджно стоит назвать updateResult
void CalculateExpression(int& result, Sign sign, const int value)
{
	if (sign == Sign::ADDITION)
	{
		result += value;
		return;
	}
	result *= value;
}