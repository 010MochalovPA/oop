#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int COUNT_MATRIX_ROWS = 3;
const int COUNT_MATRIX_COLS = 3;

typedef double Matrix3x3[3][3];

string JoinExceptionString(const string&);
void ThrowExceptionForInvalidCountArgs(const int&);
ifstream OpenInputFileStream(const string&);
void GetMatrix3x3FromStream(Matrix3x3, ifstream&);
void PrintMatrix3x3(Matrix3x3);
void InvertMatrix3x3(Matrix3x3, Matrix3x3);
void ThrowExceptionForWrongMatrix(ifstream&);

ifstream OpenInputFileStream(const string& fileName)
{
	ifstream input(fileName, ios::binary);

	if (!input.is_open())
	{
		throw "Failed to open <input file> for reading";
	}

	return input;
}

void ThrowExceptionForInvalidCountArgs(const int& argc)
{
	if (argc != 2)
	{
		throw "Invalid argument count";
	}
}

string JoinExceptionString(const string& exception)
{
	return exception + '\n'
		+ "Usage: invert.exe <matrix file1>" + '\n';
}

void ThrowExceptionForWrongMatrix(ifstream& input)
{
	string line;
	double temp;

	int cols = 0;
	int rows = 0;
	
	while (getline(input, line))
	{
		istringstream lineStream(line);
		
		cols = 0;	
		
		while (lineStream >> temp)
		{
			cols++;
			
			if (cols > 3 || rows > 3)
			{
				throw "Invalid input matrix";
			}
		}

		rows++;
	}
	
	input.clear();
	input.seekg(0, ios::beg);
}

void GetMatrix3x3FromStream(Matrix3x3 destonationMatrix, ifstream& input)
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
				throw "Invalid input matrix";
			}
		}
	}

}

void PrintMatrix3x3(Matrix3x3 matrix)
{
	cout.setf(ios::fixed);
	cout.precision(3);

	for (int i = 0; i < COUNT_MATRIX_ROWS; i++)
	{
		for (int j = 0; j < COUNT_MATRIX_COLS; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}

	cout.unsetf(ios::fixed);
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
		ThrowExceptionForInvalidCountArgs(argc);

		ifstream input = OpenInputFileStream(argv[1]);

		Matrix3x3 matrix1 = {};
		
		GetMatrix3x3FromStream(matrix1, input);

		Matrix3x3 result = {};

		InvertMatrix3x3(matrix1, result);

		PrintMatrix3x3(result);
		
		return 0;
	}
	catch (const char* exception)
	{
		cout << JoinExceptionString(exception);
		return 1;
	}

}