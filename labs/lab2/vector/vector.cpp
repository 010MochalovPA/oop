#include "vector_headers.h"

int main()
{
	try
	{
		auto vector = GetVectorFromInput(std::cin);

		MultiplyNegativeElementsOnProductMinAndMax(vector);

		SortVector(vector);

		OutputVector(vector, std::cout);
		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
}
