#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <optional>

const int COUNT_MATRIX_ROWS = 3;
const int COUNT_MATRIX_COLS = 3;

const int COUNT_MINOR_MATRIX_ROWS = 2;
const int COUNT_MINOR_MATRIX_COLS = 2;
// всегда возвращает optional
using Matrix3x3 = std::array<std::array<double, COUNT_MATRIX_COLS>, COUNT_MATRIX_ROWS>;
using Matrix2x2 = std::array<std::array<double, COUNT_MINOR_MATRIX_COLS>, COUNT_MINOR_MATRIX_ROWS>;

Matrix3x3 GetMatrix3x3FromFile(const std::string& fileName);
void PrintMatrix3x3(const Matrix3x3& matrix);
void ThrowExceptionForWrongMatrix(std::ifstream& input);
double GetDeterminantMatrix2x2(const Matrix2x2& matrix);
double GetDeterminantMatrix3x3(const Matrix3x3& matrix);
std::string ConcatStringWithMessage(const std::string& exception);
Matrix3x3 GetTranspositionMatrix3x3(const Matrix3x3& matrix);
Matrix2x2 GetMinorMatrixForElement(const Matrix3x3& matrix, int rowMinor, int colMinor);
Matrix3x3 GetComplementMatrix3x3(const Matrix3x3& matrix);
Matrix3x3 MultiMatrix3x3AndNumber(const Matrix3x3& matrix, double number);
Matrix3x3 InvertMatrix(const Matrix3x3& matrix);
//не надо выносить в отдельную функцию
void ThrowExceptionForWrongMatrix(std::ifstream& input)
{
	std::string line;
	double value;

	int cols = 0;
	int rows = 0;

	while (getline(input, line))
	{
		std::istringstream lineStream(line);

		cols = 0;

		while (lineStream >> value)
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

std::string ConcatStringWithMessage(const std::string& exception)
{
	return exception + '\n'
		+ "Usage: invert.exe <matrix file1>" + '\n';
}

double GetDeterminantMatrix3x3(const Matrix3x3& matrix) 
{
	return (matrix[0][0] * matrix[1][1] * matrix[2][2]) 
		+ (matrix[0][2] * matrix[1][0] * matrix[2][1]) 
		+ (matrix[0][1] * matrix[1][2] * matrix[2][0])
		- (matrix[2][0] * matrix[1][1] * matrix[0][2])
		- (matrix[0][0] * matrix[1][2] * matrix[2][1])
		- (matrix[2][2] * matrix[1][0] * matrix[0][1]);
}

double GetDeterminantMatrix2x2(const Matrix2x2& matrix)
{
	return (matrix[0][0] * matrix[1][1]) - matrix[0][1] * matrix[1][0];
}

Matrix3x3 GetMatrix3x3FromFile(const std::string& fileName)
{
	std::ifstream input;
	input.open(fileName);

	if (!input.is_open())
	{
		throw std::invalid_argument("Failed to open <input file> for reading");
	}

	ThrowExceptionForWrongMatrix(input);

	double temp = 0;

	Matrix3x3 matrix;

	for (int i = 0; i < COUNT_MATRIX_ROWS; i++)
	{
		for (int j = 0; j < COUNT_MATRIX_COLS; j++)
		{
			if (input >> temp)
			{
				matrix[i][j] = temp;
			}
			else
			{
				throw std::invalid_argument("Invalid input matrix");
			}
		}
	}

	return matrix;
}

void PrintMatrix3x3(const Matrix3x3& matrix)
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

Matrix3x3 GetTranspositionMatrix3x3(const Matrix3x3& matrix)
{
	Matrix3x3 result;
	for (int i = 0; i < COUNT_MATRIX_ROWS; i++)
	{
		for (int j = 0; j < COUNT_MATRIX_COLS; j++)
		{
			result[i][j] = matrix[j][i];
		}
	}
	return result;
}

Matrix2x2 GetMinorMatrixForElement(const Matrix3x3& matrix, int rowMinor, int colMinor)
{
	Matrix2x2 minor;

	int offsetRow = 0;
	int offsetCol = 0;

	for (int i = 0; i < COUNT_MINOR_MATRIX_ROWS; i++)
	{
		if (i == rowMinor)
		{
			offsetRow = 1;
		}

		offsetCol = 0;
		for (int j = 0; j < COUNT_MINOR_MATRIX_COLS; j++)
		{
			
			if (j == colMinor)
			{
				offsetCol = 1; 
			}

			minor[i][j] = matrix[i + offsetRow][j + offsetCol];
		}
	}

	return minor;
}

Matrix3x3 GetComplementMatrix3x3(const Matrix3x3& matrix)
{
	Matrix3x3 result;

	for (int i = 0; i < COUNT_MATRIX_ROWS; i++)
	{
		for (int j = 0; j < COUNT_MATRIX_COLS; j++)
		{
			Matrix2x2 minorMatrix = GetMinorMatrixForElement(matrix, i, j);
			//главное слово в конце
			result[i][j] = GetDeterminantMatrix2x2(minorMatrix);
		}
	}

	result[0][1] = -result[0][1];
	result[1][0] = -result[1][0];
	result[1][2] = -result[1][2];
	result[2][1] = -result[2][1];

	return result;
}

Matrix3x3 MultiMatrix3x3AndNumber(const Matrix3x3& matrix, double number) 
{
	Matrix3x3 result;

	for (int i = 0; i < COUNT_MATRIX_ROWS; i++)
	{
		for (int j = 0; j < COUNT_MATRIX_COLS; j++)
		{
			result[i][j] = matrix[i][j] * number;
		}
	}

	return result;
}

Matrix3x3 InvertMatrix(const Matrix3x3& matrix) 
{
	double determinant = GetDeterminantMatrix3x3(matrix);

	if (determinant == 0)
	{
		//нет конструктора принимающего строку
		throw std::domain_error("Determinant is 0! Matrix cannot be inverted!");
	}

	Matrix3x3 complimentMatrix = GetComplementMatrix3x3(matrix);

	Matrix3x3 transpositedMatrix = GetTranspositionMatrix3x3(complimentMatrix);

	Matrix3x3 invertMatrix = MultiMatrix3x3AndNumber(transpositedMatrix, 1 / (determinant));

	return invertMatrix;
}


int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			throw std::invalid_argument("Invalid argument count");
		}

		std::string fileName = argv[1];
		//не возвращать optional если не проверяю исключения
		Matrix3x3 matrix = GetMatrix3x3FromFile(fileName);

		Matrix3x3 result = InvertMatrix(matrix);

		PrintMatrix3x3(result);
		
		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cout << ConcatStringWithMessage(exception.what());

		return 1;
	}

}