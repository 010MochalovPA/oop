#pragma once

#include <algorithm>
#include <iostream>
#include <math.h>
#include <set>
#include <string>
#include <vector>
#include <optional>

std::set<int> GeneratePrimeNumbersSet(const int upperBound);
void PrintSet(const std::set<int>& primeNumbers);
bool isUnsignedNumber(const std::string& string);