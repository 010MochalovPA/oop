#include "CCalculator.h"
#include "CCalculatorApp.h"
#include "stdafx.h"

int main()
{
	CCalculator calculator;
	CCalculatorApp calculatorApp(calculator, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!calculatorApp.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}

	return 0;
}