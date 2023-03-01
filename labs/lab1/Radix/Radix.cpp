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
int ConvertDigitToInt(char, int /*radix*/);
char ConvertIntToDigit(int, int /*radix*/);
void ThrowOnEmptyString(const std::string&);
void ThrowOnIncorrectNotation(int /*radix*/);
void ThrowOnOverflowOnAddition(int, int);
void ThrowOnOverflowOnMultiply(int, int);
std::string ConvertIntToString(int, int /*radix*/);
std::string ConvertSourceToDestNotation(const std::string& /*value*/, int /*sourceNotation*/, int /*destinationNotation*/);
std::string ConcatStringWithMessageUsage(const std::string&);
Args ParseArgs(const int, char*[]);

//argc принимать по значению +
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

// Название функции не должно зависеть от контекста её использования, если тело не зависит +
std::string ConcatStringWithMessageUsage(const std::string& string)
{
	return string + '\n'
		+ "Usage: radix.exe <source notation> <destination notation> <value>" + '\n';
}

// Переводит символ ch в число в системе счисления radix +
// Выбрасывает исключение, если ch -- не цифра в этой счисления ?

int ConvertDigitToInt(char ch, int radix)
{
	if (ch > '9')
	{
		if (ch < 'A' || ch > 'A' + radix - DEC_RADIX - 1)
		{
			throw std::invalid_argument("Invalid argument");
		}

		return ch - 'A' + DEC_RADIX;
	}
	else
	{
		if (ch - '0' >= radix || ch < '0')
		{
			throw std::invalid_argument("Invalid argument");
		}

		return ch - '0';
	}
}
// Функция пропускает цифры, равные основанию системы счисления, Например в двоичной системе пропустит 2, а в 16-й - G +
char ConvertIntToDigit(int a, int radix)
{
	if (a >= 0 && a <= 9)
	{
		return '0' + a;
	}
	
	if (a <= MAX_RADIX && a >= DEC_RADIX)
	{
		return 'A' + (a - DEC_RADIX);
	}

	if (a >= radix)
	{
		throw std::invalid_argument("Invalid argument");
	}

	throw std::invalid_argument("Invalid argument");
}

int ConvertStringToInt(const std::string& strNumber, int radix)
{
	// А если строка strNumber пустая? +
	ThrowOnEmptyString(strNumber);

	ThrowOnIncorrectNotation(radix);

	if (strNumber == "0")
	{
		return 0;
	}

	int result = 0;
	int digit = 0;

	bool signMinus = false;

	if (strNumber[0] == '-')
	{
		signMinus = true;
	}

	for (unsigned int i = (signMinus) ? 1 : 0; i < strNumber.length(); i++)
	{
		digit = ConvertDigitToInt(strNumber[i], radix);

		if (signMinus)
		{
			result = SafeAdd(SafeMultiply(result, radix), -digit);
		}
		else
		{
			result = SafeAdd(SafeMultiply(result, radix), digit);
		}
	}
	return result;
}
// Программа не пропускает число INT_MIN +
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
		// Возможно переполнение при number = INT_MIN +
		signMinus = true;		
	}
	
	while (number != 0)
	{
		int value = number % radix;

		if (signMinus)
		{
			value = -value;
			result.insert(result.begin(), ConvertIntToDigit(value, radix));
		}
		else
		{
			result.insert(result.begin(), ConvertIntToDigit(value, radix));
		}

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