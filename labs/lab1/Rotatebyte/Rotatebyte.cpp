#include <iostream>
#include <string>

using namespace std;

bool isUnsignedNumber(string inputString);
bool validateSize(int number);
bool validateDirection(string direction);
int rotateB(int number, int countRotateB, char direction);

bool isUnsignedNumber(string inputString)
{
	for (char ch : inputString)
	{
		if (!isdigit(ch))
			return 0;
		}

	return 1;
}

bool validateSize(int number)
{
	if ((number >> 8) != 0)
	{
		return 0;
	}

	return 1;
}

bool validateDirection(string direction)
{
	if ((direction != "L") && (direction != "R"))
	{
		return 0;
	}

	return 1;
}

int rotateB(int number, int countRotateB, char direction)
{
	if (countRotateB > 0)
	{
		if (direction == 'L')
		{
			number = ((number << 1) | number >> 7) & 0b11111111;
			rotateB(number, --countRotateB, direction);
		}
		else
		{
			number = ((number >> 1) | (number & 0x01) << 7) & 0b11111111;
			rotateB(number, --countRotateB, direction);
		}
	}
	else
	{
		cout << number << endl;
	}
	
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid argument count" << endl
			 << "Usage: rotatebyte.exe <byte> <number of bits> <L / R>" << endl;
		return 1;
	}

	if (!isUnsignedNumber(argv[1]))
	{
		cout << "Invalid argument <byte>" << endl
			 << "Usage: rotatebyte.exe <byte> <number of bits> <L / R>" << endl;
		return 1;
	}

	if (!isUnsignedNumber(argv[2]))
	{
		cout << "Invalid argument <number of bits>" << endl
			 << "Usage: rotatebyte.exe <byte> <number of bits> <L / R>" << endl;
		return 1;
	}

	if (!validateDirection(argv[3]))
	{
		cout << "Invalid argument direction <L / R>" << endl
			 << "Usage: rotatebyte.exe <byte> <number of bits> <L / R>" << endl;
		return 1;
	}

	int number = atoi(argv[1]);
	int countRotateB = atoi(argv[2]);
	char direction = argv[3][0];

	if (!validateSize(number))
	{
		cout << "Size exceeds 1 byte" << endl;
		return 1;
	}

	return rotateB(number, countRotateB, direction);
}