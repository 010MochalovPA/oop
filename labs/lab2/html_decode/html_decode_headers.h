//в программе вектот выполнить тоже самое
#pragma once
#include <iostream>

void DecodeInputStream(std::istream& inputStream, std::ostream& outputStream);
std::string HtmlDecode(const std::string& html);