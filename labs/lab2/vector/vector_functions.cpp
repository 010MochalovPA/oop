#include <iostream>
#include <optional>
#include <vector>
#include <algorithm>
#include "vector_headers.h"

std::vector<double> GetVectorFromInput(std::istream& inputStream)
{
	std::vector<double> vector;

	double value;

	while (inputStream >> value)
	{
		vector.push_back(value);
	}

	if (!inputStream.eof())
	{
		throw std::runtime_error("Invalid vector!"); 
	}

	return vector;
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
// покрыть тестами результат, когда вектор пустой
void MultiplyNegativeElementsOnProductMinAndMax(std::vector<double>& vector)
{ // переделать за один проход ++
	// неопределенное поведение при пустом векторе++
	if (vector.empty())
	{
		return;	
	}

	const auto [min, max] = std::minmax_element(vector.begin(), vector.end());

	// посчитать произведение min max один раз ++
	
	std::transform(vector.begin(), vector.end(), vector.begin(), [minmax = *min * *max](double element) {
		if (element < 0)
		{
			element = element * minmax;
		}
		return element;
	});
}

void SortVector(std::vector<double>& vector)
{
	if (vector.empty())
	{
		return;
	}

	std::sort(vector.begin(), vector.end());
}