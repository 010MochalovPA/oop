#include <iostream>
#include <string>

const unsigned int RADIX = 10;
const unsigned int COUNT_BITS_IN_BYTE = 8;

std::string ConcatStringWithMessage(const std::string&);
int FlipByte(uint8_t b);
int SafeMultiply(int a, int b);
int SafeAdd(int a, int b);

int SafeMultiply(int a, int b)
{
	if (a > 0 && b > 0 && a > (INT_MAX / b))
	{
		throw std::overflow_error("Invalid argument");
	}

	if (a > 0 && b < 0 && b < (INT_MIN / a))
	{
		throw std::overflow_error("Invalid argument");
	}

	if (a < 0 && b > 0 && a < (INT_MIN / b))
	{
		throw std::overflow_error("Invalid argument");
	}

	if (a < 0 && b < 0 && b < (INT_MAX / a))
	{
		throw std::overflow_error("Invalid argument");
	}
	return a * b;
}

int SafeAdd(int a, int b)
{
	if (b > 0 && a > (INT_MAX - b))
	{
		throw std::overflow_error("Invalid argument");
	}

	if (b < 0 && a < (INT_MAX - b))
	{
		throw std::overflow_error("Invalid argument");
	}

	return a + b;
}

int ConvertStringToInt(const std::string& value)
{
	for (char ch : value)
	{
		if (!isdigit(ch))
		{
			throw std::invalid_argument("Invalid argument");
		}
	}

	int result = 0;

	for (char ch : value)
	{
		result = SafeAdd(SafeMultiply(result, RADIX), ch - '0');
	}

	return result;
}
// флипать биты по степени двойке +
int FlipByte(uint8_t byte)
{
	byte = (byte & 0b11110000) >> 4 | (byte & 0b00001111) << 4;
	byte = (byte & 0b11001100) >> 2 | (byte & 0b00110011) << 2;
	byte = (byte & 0b10101010) >> 1 | (byte & 0b01010101) << 1;
	
	return byte;
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			throw std::invalid_argument("Invalid argument count");
		}

		// использовать stoi +

		int number = std::stoi(argv[1]);

		if (number >> COUNT_BITS_IN_BYTE != 0)
		{
			throw std::invalid_argument("Argument <byte> exceeds 1 byte");
		}

		uint8_t byte = number;

		std::cout << FlipByte(byte) << std::endl;

		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		std::cout << "Usage: flipbyte.exe <byte>" << std::endl;
		return 1;
	}
}