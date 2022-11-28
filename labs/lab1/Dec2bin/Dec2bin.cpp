#include <iostream>
#include <string>

using namespace std;

const unsigned int RADIX = 10;
const unsigned int MAX_INT = numeric_limits<unsigned int>::max();

unsigned int ConvertStringToInt(const string&);
void ThrowExceptionForInvalidCountArgs(const int);
void ThrowExceptionForNonNumericValue(const string&);
void ThrowExceptionForOverflowInt(unsigned int, unsigned int);
string ConvertDecStringToBin(string&);
string JoinExceptionString(const string&);

string JoinExceptionString(const string& exception)
{
	return exception + '\n'
		+ "Usage: dec2bin.exe <binary number>" + '\n';
}

void ThrowExceptionForInvalidCountArgs(const int argc)
{
	if (argc != 2)
	{
		throw "Invalid argument count";
	}
}

void ThrowExceptionForOverflowInt(unsigned int a, unsigned int b)
{
	if (MAX_INT - a < b)
	{
		throw "Invalid argument";
	}
}

unsigned int ConvertStringToInt(const string& value)
{
	ThrowExceptionForNonNumericValue(value);

	unsigned int result = 0;

	for (char ch : value)
	{
		ThrowExceptionForOverflowInt(result * RADIX, ch - '0');

		result = (result * RADIX) + (ch - '0');
	}

	return result;
}

void ThrowExceptionForNonNumericValue(const string& value)
{
	for (char ch : value)
	{
		if (!isdigit(ch))
			throw "Invalid notation"; 
	}
}

string ConvertDecStringToBin(const string& value)
{
	unsigned int decimalNumber = ConvertStringToInt(value);

	string result = "";

	while (decimalNumber != 0)
	{
		result.insert(result.begin(), (decimalNumber & 0x01) + '0');
		decimalNumber >>= 1;
	}

	return result == "" ? "0" : result;
}

int main(int argc, char* argv[])
{
	try
	{
		ThrowExceptionForInvalidCountArgs(argc);
		cout << ConvertDecStringToBin(argv[1]);
		return 0;
	}
	catch (const char* exception)
	{
		cout << JoinExceptionString(exception);
		return 1;
	}

}