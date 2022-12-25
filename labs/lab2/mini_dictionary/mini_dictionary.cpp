#include "./mini_dictionary.h"



int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc > 2)
	{
		std::cout << "Usage: mini_dictionary.exe or mini_dictionary.exe <dictionary path>" << std::endl;
		return 1;
	}

	std::string dictionaryPath = argv[1] ? argv[1] : "dictionary.txt";

	RunDictionary(std::cin, std::cout, dictionaryPath);

	return 0;
}
