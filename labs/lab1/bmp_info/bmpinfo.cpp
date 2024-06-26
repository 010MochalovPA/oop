﻿#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

<<<<<<< HEAD
const int FOUR_BYTES = 4;
const int TWO_BYTES = 2;
=======
const int BUFFER_SIZE = 4;
const int BITS_IN_BYTE = 8;
const int COUNT_BYTES_TWO = 2;
const int COUNT_BYTES_FOUR = 4;
>>>>>>> 8dc29fb6fff86071516e78a3f16afdec6eac0ba7

const uint32_t BITMAP_FILE_HEADER_SIZE = 14;

const uint32_t FILE_SIZE_OFFSET = 2;
const uint32_t STARTING_IMAGE_ADDRESS_OFFSET = 10;
const uint32_t WIDTH_OFFSET = 18;
const uint32_t HEIGHT_OFFSET = 22;
const uint32_t BITS_PER_PIXEL_OFFSET = 28;
const uint32_t COMPRESSION_TYPE_OFFSET = 30;

using TwoBytesBuffer = char[2];
using FourBytesBuffer = char[4];

const std::map<size_t, std::string> COMPRESSION_TYPES = { 
	{ 0, "BI_RGB" },
	{ 1, "BI_RLE8" },
	{ 2, "BI_RLE4" },
	{ 3, "BI_BITFIELDS" },
	{ 4, "BI_JPEG" },
	{ 5, "BI_PNG" },
	{ 6, "BI_ALPHABITFIELDS" },
	{ 11, "BI_CMYK" },
	{ 12, "BI_CMYKRLE8" },
	{ 13, "BI_CMYKRLE4" },
};

struct BitMapInfo
{
	uint32_t width;
	uint32_t height;
	uint32_t bitsPerPixel;
	uint32_t colors;
	uint32_t imageSize;
	std::string compressionType;
};

<<<<<<< HEAD
bool IsNotBmpFile(std::ifstream& input)
{
	TwoBytesBuffer buffer;
	input.read(buffer, TWO_BYTES);

	return buffer[0] != 'B' && buffer[1] != 'M';
}

uint32_t ReadNextBytes(std::ifstream& input, const size_t offset, const size_t countBits)
{
	FourBytesBuffer buffer{};
	uint32_t value{};

	input.seekg(offset, input.beg);

	if (input.read(buffer, countBits))
	{
		std::reverse(std::begin(buffer), std::end(buffer));
		for (uint8_t ch : buffer)
		{
			value = (value << CHAR_BIT) | ch;
		}
	}

	return value;
}

BitMapInfo GetBmpInfoFromStream(std::ifstream& input)
{
	BitMapInfo info{};

	if (IsNotBmpFile(input))
	{
		throw std::invalid_argument("Not bmp file");
	}

	info.width = ReadNextBytes(input, WIDTH_OFFSET, FOUR_BYTES);
	info.height = ReadNextBytes(input, HEIGHT_OFFSET, FOUR_BYTES);
	info.bitsPerPixel = ReadNextBytes(input, BITS_PER_PIXEL_OFFSET, TWO_BYTES);

	uint32_t compressionType = ReadNextBytes(input, COMPRESSION_TYPE_OFFSET, FOUR_BYTES);

	auto it = COMPRESSION_TYPES.find(compressionType);
	
	if (it == COMPRESSION_TYPES.end())
	{
		throw std::runtime_error("Invalid compression");
	}

	info.compressionType = it->second;

	uint32_t fileSize = ReadNextBytes(input, FILE_SIZE_OFFSET, FOUR_BYTES);
	uint32_t startingImageOffset = ReadNextBytes(input, STARTING_IMAGE_ADDRESS_OFFSET, FOUR_BYTES);

	info.imageSize = fileSize - startingImageOffset;

	uint32_t bitMapInfoHeaderSize = ReadNextBytes(input, BITMAP_FILE_HEADER_SIZE, FOUR_BYTES);

	uint32_t colorsOffset = BITMAP_FILE_HEADER_SIZE + bitMapInfoHeaderSize;

	uint32_t colors = ReadNextBytes(input, colorsOffset, FOUR_BYTES);

	info.colors = (uint32_t)pow(2, info.bitsPerPixel);

	return info;
};

=======
>>>>>>> 8dc29fb6fff86071516e78a3f16afdec6eac0ba7
std::string ParseArgs(const int& argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::runtime_error("Invalid argument count");
	}

	std::string bmpFileName = argv[1];

	if (bmpFileName.empty())
	{
		throw std::invalid_argument("Invalid argument");
	}

	return bmpFileName;
}

<<<<<<< HEAD
void PrintBmpInfo(const BitMapInfo& info)
=======
bool IsNotBmpFile(std::ifstream& input)
{
	const uint32_t offset = 0;
	
	char buffer[BUFFER_SIZE];
	
	input.seekg(offset, std::ios::beg);
	return input.read(buffer, COUNT_BYTES_TWO) && buffer[0] != 'B' && buffer[1] != 'M';
}

uint32_t GetValueFromOffset(std::ifstream& input, uint32_t offset, int countBits)
{
	char buffer[BUFFER_SIZE]{};

	uint32_t value{};

	input.seekg(offset, std::ios::beg);
	if (input.read(buffer, countBits))
	{
		std::reverse(std::begin(buffer), std::end(buffer));
		for (uint8_t ch : buffer)
		{
			value = (value << BITS_IN_BYTE) | ch;
		
		}
	}
	
	return value;
}

BmpInfo GetInfoFromFile(const std::string& bmpFileName)
{
	std::ifstream input(bmpFileName, std::ios::binary);

	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open <input file> for reading");
	}

	BmpInfo info{};

	if (IsNotBmpFile(input))
	{
		throw std::invalid_argument("Not bmp file");
	}

	uint32_t fileSize = GetValueFromOffset(input, SIZE_FILE_OFFSET, COUNT_BYTES_FOUR);
	uint32_t dataOffset = GetValueFromOffset(input, DATA_OFFSET, COUNT_BYTES_FOUR);
	info.width = GetValueFromOffset(input, WIDTH_OFFSET, COUNT_BYTES_FOUR);
	info.height = GetValueFromOffset(input, HEIGHT_OFFSET, COUNT_BYTES_FOUR);
	info.bitsPerPixel = GetValueFromOffset(input, BIT_PER_PIXEL_OFFSET, COUNT_BYTES_TWO);
	uint32_t compressionType = GetValueFromOffset(input, COMPRESSION_TYPE_OFFSET, COUNT_BYTES_FOUR);

	auto type = COMPRESSION_TYPES.find(compressionType);

	if (type != COMPRESSION_TYPES.end())
	{
		info.compressionType = type->second;
	}

	uint32_t size = GetValueFromOffset(input, IMAGE_SIZE_OFFSET, COUNT_BYTES_FOUR);

	if (size)
	{
		info.size = size;
	}
	else
	{
		info.size = fileSize - dataOffset;
	}

	uint32_t colors = GetValueFromOffset(input, COLORS_OFFSET, COUNT_BYTES_FOUR);

	if (colors && colors <= 8)
	{
		info.colors = colors;
	}

	return info;
}

void PrintBmpInfo(const BmpInfo& info)
>>>>>>> 8dc29fb6fff86071516e78a3f16afdec6eac0ba7
{
	std::cout << "Resolution:\t" << info.width << "x" << info.height << std::endl
			  << "Bits in pixel:\t" << info.bitsPerPixel << std::endl
			  << "Colors:\t\t" << info.colors << std::endl
			  << "Compression:\t" << info.compressionType << std::endl
			  << "Size image:\t" << info.imageSize << std::endl;
}

int main(int argc, char* argv[])
{
	try
	{
		std::string bmpFileName = ParseArgs(argc, argv);
		
		std::ifstream inputStream(bmpFileName, std::ios::binary);

		if (!inputStream.is_open())
		{
			throw std::runtime_error("Failed to open <input file> for reading");
		}
		
		BitMapInfo info = GetBmpInfoFromStream(inputStream);

		PrintBmpInfo(info);

		return 0;
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl
				  << "Usage: bmpinfo.exe <input file name>" << std::endl;

		return 1;
	}
	
}