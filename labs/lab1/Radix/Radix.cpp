#include <iostream>
#include <string>
#include <limits>

const int MIN_RADIX = 2;
const int MAX_RADIX = 36;
const int DEC_RADIX = 10;

struct Args
{
	int sourseNotation;
	int destinationNotation;
	std::string value;
};

int SafeAdd(int, int);
int SafeMultiply(int, int);
int ConvertStringToInt(const std::string&, int /*radix*/);
int DigitToInt(char, int /*radix*/);
void ThrowOnEmptyString(const std::string&);
void ThrowOnIncorrectNotation(int /*radix*/);
void ThrowOnIncorrectDigitNotation(char, int /*radix*/);
void ThrowOnOverflowOnAddition(int, int);
void ThrowOnOverflowOnMultiply(int, int);
std::string ConvertIntToString(int, int /*radix*/);
std::string ConvertSourceToDestNotation(const std::string& /*value*/, int /*sourceNotation*/, int /*destinationNotation*/);
std::string ConcatStringWithMessageUsage(const std::string&);
Args ParseArgs(const int, char*[]);

//argc принимать по значению
Args ParseArgs(const int argc, char* argv[])
{
	if (argc != 4)
	{
		throw std::range_error("Invalid argument count");
	}

	Args args = {};
	args.sourseNotation = ConvertStringToInt(argv[1], DEC_RADIX);
	args.destinationNotation = ConvertStringToInt(argv[2], DEC_RADIX);
	args.value = argv[3];

	return args;
}

void ThrowOnEmptyString(const std::string& str)
{
	if (str.length() == 0)
	{
		throw std::invalid_argument("Invalid argument");
	}
}

void ThrowOnOverflowOnAddition(int a, int b)
{
	if (b > 0 && a > (INT_MAX - b))
	{
		throw std::overflow_error("Invalid argument");
	}

	if (b < 0 && a < (INT_MAX - b))
	{
		throw std::overflow_error("Invalid argument");
	}
}

// Функция пропускает цифры, равные основанию системы счисления, Например в двоичной системе пропустит 2, а в 16-й - G
void ThrowOnIncorrectDigitNotation(char ch, int radix)
{
	if (ch > '9')
	{
		if (ch < 'A' || ch > 'A' + radix - DEC_RADIX - 1)
		{
			throw std::invalid_argument("Invalid argument");
		}
	}
	else
	{
		if (ch - '0' > radix || ch < '0')
		{
			throw std::invalid_argument("Invalid argument");
		}
	}
}

void ThrowOnOverflowOnMultiply(int a, int b)
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

// Название функции не должно зависеть от контекста её использования, если тело не зависит
std::string ConcatStringWithMessageUsage(const std::string& string)
{
	return string + '\n'
		+ "Usage: radix.exe <source notation> <destination notation> <value>" + '\n';
}

// Переводит символ ch в число в системе счисления radix
// Выбрасывает исключение, если ch -- не цифра в этой счисления
int DigitToInt(char ch, int radix)
{
	ThrowOnIncorrectDigitNotation(ch, radix);
	
	if (ch > '9')
	{
		return ch - 'A' + DEC_RADIX;
	}

	return ch - '0';
}

char IntToDigit(int a, int radix)
{
	if (a > 9)
	{
		char result = a + 'A' - DEC_RADIX;

		ThrowOnIncorrectDigitNotation(result, radix);

		return result;
	}

	char result = a + '0';

	ThrowOnIncorrectDigitNotation(result, radix);

	return result;
}

int ConvertStringToInt(const std::string& strNumber, int radix)
{
	// А если строка strNumber пустая?
	ThrowOnEmptyString(strNumber);

	ThrowOnIncorrectNotation(radix);

	if (strNumber == "0")
	{
		return 0;
	}

	int result = 0;

	for (unsigned int i = (strNumber[0] != '-') ? 0 : 1; i < strNumber.length(); i++)
	{
		result = SafeAdd(SafeMultiply(result, radix), DigitToInt(strNumber[i], radix));
	}

	return (strNumber[0] != '-') ? result : -result;

}
// Программа не пропускает число INT_MIN
std::string ConvertIntToString(int number, int radix)
{
	ThrowOnIncorrectNotation(radix);

	if (number == 0)
	{
		return "0";
	}

	std::string result = "";
	bool signMinus = false;

	if (number < 0)
	{
		// Возможно переполнение при number = INT_MIN
		number = -number;
		signMinus = true;		
	}
	
	while (number > 0)
	{
		result.insert(result.begin(), IntToDigit(number % radix, radix));
		number = number / radix;
	}

	if (signMinus)
	{
		result.insert(result.begin(), '-');
	}
		
	return result;
}

void ThrowOnIncorrectNotation(int radix)
{
	if (MIN_RADIX > radix || radix > MAX_RADIX)
	{
		throw std::invalid_argument("Invalid source or destonation notation");
	}
}


std::string ConvertSourceToDestNotation(const std::string& value, int sourceNotation, int destinationNotation)
{
	int decValue = ConvertStringToInt(value, sourceNotation);
	
	return ConvertIntToString(decValue, destinationNotation);
}

int main(int argc, char* argv[])
{

	try
	{
		Args args = ParseArgs(argc,argv);

		std::cout << ConvertSourceToDestNotation(args.value, args.sourseNotation, args.destinationNotation) << std::endl;

		return 0;

	}
	catch (const std::exception& exception)
	{
		std::cout << ConcatStringWithMessageUsage(exception.what());

		return 1;
	}
	
}