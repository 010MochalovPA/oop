#include <iostream>
#include <string>

const unsigned int RADIX = 10;
const unsigned int COUNT_BITS_IN_BYTE = 8;

std::string ConcatStringWithMessage(const std::string&);
void ThrowExceptionForNonNumericValue(const std::string&);
void ThrowExceptionForInvalidSize(int);
void ThrowExceptionForInvalidCountArgs(const int);
void ThrowExceptionForOverflowInt(unsigned int, unsigned int);
int ConvertStringToInt(const std::string&);
int FlipByte(int b);
int SafeMultiply(int a, int b);
int SafeAdd(int a, int b);

std::string ConcatStringWithMessage(const std::string& exception)
{
	return exception + '\n'
		+ "Usage: flipbyte.exe <byte>" + '\n';
}

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
	ThrowExceptionForNonNumericValue(value);

	int result = 0;

	for (char ch : value)
	{
		result = SafeAdd(SafeMultiply(result,RADIX), ch - '0');
	}

	return result;
}

void ThrowExceptionForInvalidCountArgs(const int argc)
{
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid argument count");
	}
}

void ThrowExceptionForNonNumericValue(const std::string& value)
{
	for (char ch : value)
	{
		if (!isdigit(ch))
		{
			throw std::invalid_argument("Invalid argument");
		}
	}
}

void ThrowExceptionForInvalidSize(int number)
{
	if (number >> COUNT_BITS_IN_BYTE != 0)
	{
		throw std::invalid_argument("Argument <byte> exceeds 1 byte");
	}
}

int FlipByte(int byte)
{
	ThrowExceptionForInvalidSize(byte);

	int result = 0;
	for (int countFlips = 0; countFlips < 8; countFlips++)
	{
		result <<= 1;
		result = result | (byte & (0x01));
		byte >>= 1;
	}
	
	return result;
}

int main(int argc, char* argv[])
{
	try
	{
		ThrowExceptionForInvalidCountArgs(argc);

		int number = ConvertStringToInt(argv[1]);

		std::cout << FlipByte(number) << std::endl;

		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cout << ConcatStringWithMessage(exception.what());

		return 1;
	}
}