#include "stdafx.h"
#include "CCar.h"
#include "CCarApp.h"

int main()
{
	// не должгл быть можно включить заднюю передачу не остановившись
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