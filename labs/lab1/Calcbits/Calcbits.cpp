#include <iostream>
#include <string>

using namespace std;

const unsigned int RADIX = 10;
const unsigned int MAX_INT = numeric_limits<unsigned int>::max();
const unsigned int COUNT_BITS_IN_BYTE = 8;

string JoinExceptionString(const string&);
void ThrowExceptionForNonNumericValue(const string&);
void ThrowExceptionForInvalidSize(int);
void ThrowExceptionForInvalidCountArgs(const int&);
void ThrowExceptionForOverflowInt(unsigned int, unsigned int);
int CalculateBitsInByte(int);
int ConvertStringToInt(const string&);

string JoinExceptionString(const string& exception)
{
	return exception + '\n'
		+ "Usage: calcbits.exe <byte>" + '\n';
}

void ThrowExceptionForOverflowInt(unsigned int a, unsigned int b)
{
	if (MAX_INT - a < b)
	{
		throw "Invalid argument";
	}
}

int ConvertStringToInt(const string& value) 
{
	ThrowExceptionForNonNumericValue(value);

	int result = 0;

	for (char ch : value)
	{
		ThrowExceptionForOverflowInt(result * RADIX, ch - '0');

		result = (result * RADIX) + ch - '0';
	}

	return result;
}

void ThrowExceptionForInvalidCountArgs(const int& argc)
{
	if (argc != 2)
	{
		throw "Invalid argument count";
	}
}
void ThrowExceptionForNonNumericValue(const string& value)
{
	for (char ch : value)
	{
		if (!isdigit(ch))
		{
			throw "Invalid argument";
		}
	}
}

void ThrowExceptionForInvalidSize(int number)
{
	if (number >> COUNT_BITS_IN_BYTE != 0)
	{
		throw "Argument <byte> exceeds 1 byte";
	}
}

int CalculateBitsInByte(int byte)
{
	ThrowExceptionForInvalidSize(byte);

	int countBits = 0;
	
	while (byte != 0)
	{
		if (byte & 0x01)
		{
			++countBits;
		}
		byte >>= 1;
	}

	return countBits;
}

int main(int argc, char* argv[])
{
	try
	{
		ThrowExceptionForInvalidCountArgs(argc);

		int number = ConvertStringToInt(argv[1]);
					
		cout << CalculateBitsInByte(number);
		
		return 0;
		
	}
	catch (const char* exception)
	{
		cout << JoinExceptionString(exception);

		return 1;
	}
}