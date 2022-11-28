#include <iostream>
#include <limits>

using namespace std;

const unsigned int MAX_INT = numeric_limits<unsigned int>::max();
const int COUNT_BITS_IN_INT = 32;
const int RADIX = 10;

string JoinExceptionString(const string&);
string ConvertBinaryStringToDec(const string&);
string ConvertIntToString(unsigned int);
void ThrowExceptionForInvalidSize(const string&);
void ThrowExceptionForInvalidNotation(const string&);
void ThrowExceptionForInvalidCountArgs(const int);

string JoinExceptionString(const string& exception)
{
	return exception + '\n'
		+ "Usage: bin2dec.exe <binary number>" + '\n';
}

void ThrowExceptionForInvalidCountArgs(const int argc)
{
	if (argc != 2)
	{
		throw "Invalid argument count";
	}
}

string ConvertIntToString(unsigned int decNumber)
{
	if (decNumber == 0)
	{
		return "0";
	}

	string result = "";

	while (decNumber > 0)
	{
		result.insert(result.begin(), (decNumber % RADIX) + '0');
		decNumber = decNumber / RADIX;
	}

	return result;
}

void ThrowExceptionForInvalidSize(const string& value)
{
	if (value.length() > COUNT_BITS_IN_INT)
	{
		throw "Invalid size binary number";
	}
}

void ThrowExceptionForInvalidNotation(const string& value)
{
	for (char ch : value)
	{
		if (ch != '1' && ch != '0')
		{
			throw "Invalid notation"; 
		}
	}
}

string ConvertBinaryStringToDec(const string& value)
{
	ThrowExceptionForInvalidSize(value);

	ThrowExceptionForInvalidNotation(value);

	unsigned int result = 0;
	size_t index = value.length() - 1;

	for (char ch : value)
	{
		if (ch == '1')
		{
			result = result | (0b01 << index);
		}
		index--;
	}

	return ConvertIntToString(result);

}

int main(int argc, char* argv[])
{
	try
	{
		ThrowExceptionForInvalidCountArgs(argc);

		cout << ConvertBinaryStringToDec(string(argv[1]));

		return 0;
	}
	catch (const char* exception)
	{
		cout << JoinExceptionString(exception);

		return 1;
	}
	
}