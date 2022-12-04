#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

const int COUNT_MATRIX_ROWS = 3;
const int COUNT_MATRIX_COLS = 3;

typedef double Matrix3x3[COUNT_MATRIX_ROWS][COUNT_MATRIX_COLS];

std::string ConcatStringWithMessage(const std::string&);
std::ifstream OpenInputFileStream(const std::string&);
void ThrowOnInvalidCountArgs(const int);
void GetMatrix3x3FromStream(Matrix3x3, std::ifstream&);
void PrintMatrix3x3(Matrix3x3);
void InvertMatrix3x3(Matrix3x3, Matrix3x3);
void ThrowExceptionForWrongMatrix(std::ifstream&);

std::ifstream OpenInputFileStream(const std::string& fileName)
{
	std::ifstream input(fileName, std::ios::binary);

	if (!input.is_open())
	{
		throw std::invalid_argument("Failed to open <input file> for reading");
	}

	return input;
}

void ThrowOnInvalidCountArgs(const int argc)
{
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid argument count");
	}
}

std::string ConcatStringWithMessage(const std::string& exception)
{
	return exception + '\n'
		+ "Usage: invert.exe <matrix file1>" + '\n';
}

void ThrowExceptionForWrongMatrix(std::ifstream& input)
{
	std::string line;
	double temp;

	int cols = 0;
	int rows = 0;
	
	while (getline(input, line))
	{
		std::istringstream lineStream(line);
		
		cols = 0;	
		
		while (lineStream >> temp)
		{
			cols++;
			
			if (cols > COUNT_MATRIX_COLS || rows > COUNT_MATRIX_ROWS)
			{
				throw std::invalid_argument("Invalid input matrix");
			}
		}

		rows++;
	}
	input.clear();
	input.seekg(0, std::ios::beg);
}

void GetMatrix3x3FromStream(Matrix3x3 destonationMatrix, std::ifstream& input)
{
	ThrowExceptionForWrongMatrix(input);

	double temp = 0;

	for (int i = 0; i < COUNT_MATRIX_ROWS; i++)
	{
		for (int j = 0; j < COUNT_MATRIX_COLS; j++)
		{
			if (input >> temp)
			{
				destonationMatrix[i][j] = temp;
			}
			else
			{
				throw std::invalid_argument("Invalid input matrix");
			}
		}
	}
}

void PrintMatrix3x3(Matrix3x3 matrix)
{
	std::cout.setf(std::ios::fixed);
	std::cout.precision(3);

	for (int i = 0; i < COUNT_MATRIX_ROWS; i++)
	{
		for (int j = 0; j < COUNT_MATRIX_COLS; j++)
		{
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	std::cout.unsetf(std::ios::fixed);
}

void InvertMatrix3x3(Matrix3x3 matrix1, Matrix3x3 result)
{
	for (int i = 0; i < COUNT_MATRIX_ROWS; i++)
	{
		for (int j = 0; j < COUNT_MATRIX_COLS; j++)
		{
			result[i][j] = matrix1[j][i];
		}
	}
}

int main(int argc, char* argv[])
{
	try
	{
		ThrowOnInvalidCountArgs(argc);

		std::ifstream input = OpenInputFileStream(argv[1]);

		Matrix3x3 matrix1 = {};
		GetMatrix3x3FromStream(matrix1, input);

		Matrix3x3 result = {};
		InvertMatrix3x3(matrix1, result);

		PrintMatrix3x3(result);
		
		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cout << ConcatStringWithMessage(exception.what());

		return 1;
	}

}