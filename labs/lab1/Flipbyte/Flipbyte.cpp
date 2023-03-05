#include <iostream>
#include <string>

const unsigned int COUNT_BITS_IN_BYTE = 8;

std::string ConcatStringWithMessage(const std::string&);
int FlipByte(uint8_t b);

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