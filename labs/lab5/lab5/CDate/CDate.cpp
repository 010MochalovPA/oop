#include <iostream>
#include "Date.h"

int main()
{
	Date date(1, Month::JANUARY, 2023);
	std::cout << date << std::endl;
	date = date - 15;
	std::cout << date << std::endl;
	date = ++date;
	std::cout << date << std::endl;
	date = date + 3;
	std::cout << date << std::endl;
	date = --date;
	std::cout << date << std::endl;
}
