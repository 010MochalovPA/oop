#include <iostream>
#include <string>

using namespace std;

const int MIN_RADIX = 2;
const int MAX_RADIX = 36;
const int DEC_RADIX = 10;
const int MAX_INT = numeric_limits<int>::max();

struct Args
{
	int sourseNotation;
	int destinationNotation;
	string value;
};

void ThrowExceptionForIncorrectChar(char ch, int radix);
void ThrowExceptionForIncorrectNotation(int radix);
void ThrowExceptionForOverflowInt(unsigned int, unsigned int);
int ConvertStringToInt(const string& strNumber, int radix);
string ConvertIntToString(int n, int radix);
string ConvertSourceToDestNotation(const string& value, int sourceNotation, int destinationNotation);
string JoinExceptionString(const string&);
Args ParseArgs(const int&, char*[]);

Args ParseArgs(const int& argc, char* argv[])
{
	if (argc != 4)
	{
		throw "Invalid argument count";
	}

	Args args = {};
	args.sourseNotation = ConvertStringToInt(argv[1], DEC_RADIX);
	args.destinationNotation = ConvertStringToInt(argv[2], DEC_RADIX);
	args.value = argv[3];

	return args;
}

void ThrowExceptionForOverflowInt(int a, int b)
{
	if (MAX_INT - a < b)
	{
		throw "Invalid argument";
	}
}

string JoinExceptionString(const string& exception)
{
	return exception + '\n'
		+ "Usage: radix.exe <source notation> <destination notation> <value>" + '\n';
}

int ConvertStringToInt(const string& strNumber, int radix)
{
	ThrowExceptionForIncorrectNotation(radix);

	int result = 0;
	for (unsigned int i = (strNumber[0] != '-') ? 0 : 1; i < strNumber.length(); i++)
	{
		
		ThrowExceptionForIncorrectChar(strNumber[i], radix);
		
 		ThrowExceptionForOverflowInt(result * radix, strNumber[i] > '9' ? strNumber[i] - 'A' + DEC_RADIX : strNumber[i] - '0');

		result = (result * radix) + (strNumber[i] > '9' ? strNumber[i] - 'A' + DEC_RADIX : strNumber[i] - '0');
		
	}

	return (strNumber[0] != '-') ? result : -result;

}

string ConvertIntToString(int number, int radix) 
{
	ThrowExceptionForIncorrectNotation(radix);

	string result = "";
	bool signMinus = false;

	if (number < 0)
	{
		number = -number;
		signMinus = true;		
	}
	
	while (number > 0)
	{
		result.insert(result.begin(), (number % radix) >= DEC_RADIX ? (number % radix) + 'A' - DEC_RADIX : (number % radix) + '0');
		number = number / radix;
	}

	if (signMinus)
	{
		result.insert(result.begin(), '-');
	}
		
	
	return result;
}

void ThrowExceptionForIncorrectChar(char ch, int radix)
{
	if (!isdigit(ch) && ch != toupper(ch))
	{
		throw "Invalid argument";
	}
	
	if (isdigit(ch) && ch - '0' > radix - 1)
	{
		throw "Invalid argument";
	}

	if (!isdigit(ch) && ch - 'A' + DEC_RADIX > radix - 1)
	{
		throw "Invalid argument";
	}
}

void ThrowExceptionForIncorrectNotation(int radix)
{
	if (MIN_RADIX > radix || radix > MAX_RADIX)
	{
		throw "Invalid source or destonation notation";
	}
}


string ConvertSourceToDestNotation(const string& value, int sourceNotation, int destinationNotation)
{
	int decValue = ConvertStringToInt(value, sourceNotation);
	string result = ConvertIntToString(decValue, destinationNotation);

	return result;
}

int main(int argc, char* argv[])
{

	try
	{
		Args args = ParseArgs(argc,argv);

		cout << ConvertSourceToDestNotation(args.value, args.sourseNotation, args.destinationNotation) << endl;

		return 0;

	}
	catch (const char* exception)
	{
		cout << JoinExceptionString(exception);

		return 1;
	}
	
}