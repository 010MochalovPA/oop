#include "Calculator.h"
#include "CalculatorApp.h"
#include "stdafx.h"

int main()
{
	Calculator calculator;
	CalculatorApp calculatorApp(calculator, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!calculatorApp.HandleCommand())
		{
			std::cout << "Incorrect input!" << std::endl;
		}
	}

	return 0;
}