#include "stdafx.h"
#include "Common.h"

std::string ColorToHex(uint32_t color)
{
	std::stringstream stream;
	stream << std::hex << std::setw(6) << std::setfill('0') << color;
	return stream.str();
}