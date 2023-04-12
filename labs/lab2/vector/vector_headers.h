#include <iostream>
#include <optional>
#include <vector>

std::vector<double> GetVectorFromInput(std::istream& inputStream);
void MultiplyNegativeElementsOnProductMinAndMax(std::vector<double>& vector);
void OutputVector(const std::vector<double>& vector, std::ostream& outputStream);
void SortVector(std::vector<double>& vector);
