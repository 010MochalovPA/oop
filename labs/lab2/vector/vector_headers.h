#include <iostream>
#include <optional>
#include <vector>

std::optional<std::vector<double>> GetVectorFromInput(std::istream& inputStream);
void MultiplyNegativeElementsOnProductMinAndMax(std::vector<double>& vector);
void OutputVector(const std::vector<double>& vector, std::ostream& outputStream);
void GetAndTransformVector(std::istream& inputStream, std::ostream& outputStream, void (*callback)(std::vector<double>& vector));
