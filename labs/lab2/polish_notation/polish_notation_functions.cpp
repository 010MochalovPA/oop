#include "polish_notation.h"

void CalculateExpression(int& result, char sign, const int value)
{
}

int CalculatePolishExpressionFromStream(std::istream& inputstream)
{
	char ch;
	inputstream >> ch;

	if (ch != '(')
	{
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

	int result = sign == Sign::ADDITION ? 0 : 1; // TODO: ��� �������� ��� ������������� result
	

	while (inputstream >> ch && ch != ')')
	{
		inputstream.unget();

		if (isalpha(ch))
		{
			throw std::exception("ERROR");
		}

		int value; // TODO: ����� ��������� ���������� � ������ ������� ��������� +

		if (ch == '(')
		{
			value = CalculatePolishExpressionFromStream(inputstream); // TODO: ��������� � ������������ ������� � ���-��� ������� �� ����� +
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

void CalculateExpression(int& result, Sign sign, const int value)
{
	if (sign == Sign::ADDITION)
	{
		result += value;
		return;
	}
	result *= value;
}