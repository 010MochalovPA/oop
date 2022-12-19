#include <iostream>
#include <optional>
#include <vector>
#include <algorithm>
#include "vector_headers.h"

std::optional<std::vector<double>> GetVectorFromInput(std::istream& inputStream)
{
	std::vector<double> vector;

	double value;

	while (inputStream >> value)
	{
		vector.push_back(value);
	}

	if (vector.empty() || !inputStream.eof())
	{
		return std::nullopt;
	}

	return { vector };
}

void OutputVector(const std::vector<double>& vector, std::ostream& outputStream)
{
	outputStream.setf(std::ios::fixed);
	outputStream.precision(3);

	for (size_t i = 0; i < vector.size(); i++)
	{
		outputStream << vector[i] << ' ';
	}
	outputStream << std::endl;

	outputStream.unsetf(std::ios::fixed);
}

void MultiplyNegativeElementsOnProductMinAndMax(std::vector<double>& vector)
{
	double min = *std::min_element(vector.begin(), vector.end());

	double max = *std::max_element(vector.begin(), vector.end());

	std::transform(vector.begin(), vector.end(), vector.begin(), [min, max](double element) {
		if (element < 0)
		{
			element = element * (min * max);
		}
		return element;
	});
}

void GetAndTransformVector(std::istream& inputStream, std::ostream& outputStream, void (*callback)(std::vector<double>& vector)) 
{
	auto vector = GetVectorFromInput(inputStream);

	if (!vector.has_value())
	{
		std::cout << "Invalid input" << std::endl;
		return;
	}

	callback(vector.value());

	std::sort(vector.value().begin(), vector.value().end());

	OutputVector(vector.value(), outputStream);
}