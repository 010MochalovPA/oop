#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

const int BUFFER_SIZE = 4;
const int BITS_IN_BYTE = 8;

const uint32_t SIZE_FILE_OFFSET = 2;
const uint32_t DATA_OFFSET = 10;
const uint32_t DIB_HEADER_SIZE_OFFSET = 14;
const uint32_t WIDTH_OFFSET = 18;
const uint32_t HEIGHT_OFFSET = 22;
const uint32_t BIT_PER_PIXEL_OFFSET = 28;
const uint32_t COMPRESSION_TYPE_OFFSET = 30;
const uint32_t IMAGE_SIZE_OFFSET = 34;
const uint32_t COLORS_OFFSET = 46;

const std::map<int, std::string> COMPRESSION_TYPES = { 
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

struct BmpInfo
{
	uint32_t width;
	uint32_t height;
	uint32_t bitsPerPixel;
	std::string compressionType;
	uint32_t size;
	uint32_t colors;
};



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

bool IsNotBmpFile(std::ifstream& input)
{
	const uint32_t offset = 0;
	
	char buffer[BUFFER_SIZE];
	
	input.seekg(offset, std::ios::beg);
	return input.read(buffer, 2) && buffer[0] != 'B' && buffer[1] != 'M';
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

	uint32_t fileSize = GetValueFromOffset(input, SIZE_FILE_OFFSET, 4);
	uint32_t dataOffset = GetValueFromOffset(input, DATA_OFFSET, 4);
	info.width = GetValueFromOffset(input, WIDTH_OFFSET, 4);
	info.height = GetValueFromOffset(input, HEIGHT_OFFSET, 4);
	info.bitsPerPixel = GetValueFromOffset(input, BIT_PER_PIXEL_OFFSET, 2);
	uint32_t compressionType = GetValueFromOffset(input, COMPRESSION_TYPE_OFFSET, 4);

	auto it = COMPRESSION_TYPES.find(compressionType);

	if (it != COMPRESSION_TYPES.end())
	{
		info.compressionType = it->second;
	}

	uint32_t size = GetValueFromOffset(input, IMAGE_SIZE_OFFSET, 4);

	if (size)
	{
		info.size = size;
	}
	else
	{
		info.size = fileSize - dataOffset;
	}

	uint32_t colors = GetValueFromOffset(input, COLORS_OFFSET, 4);

	if (colors && colors < 8)
	{
		info.colors = colors;
	}

	return info;
}

void PrintBmpInfo(const BmpInfo& info)
{
	std::cout << "Resolution:\t" << info.width << "x" << info.height << std::endl
			  << "Bits in pixel:\t" << info.bitsPerPixel << std::endl;
	
	if (info.colors)
	{
		std::cout << "Colors:\t" << info.colors << std::endl;
	}

	std::cout << "Compression:\t" << info.compressionType << std::endl
			  << "Size image:\t" << info.size << std::endl;
}

int main(int argc, char* argv[])
{
	try
	{
		std::string bmpFileName = ParseArgs(argc, argv);
		
		BmpInfo info = GetInfoFromFile(bmpFileName);

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