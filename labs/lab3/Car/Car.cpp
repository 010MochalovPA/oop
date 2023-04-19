#include "stdafx.h"
#include "CCar.h"
#include "CCarApp.h"

int main()
{
	CCar car;
	CCarApp carApp(car, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!carApp.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}

	return 0;
}