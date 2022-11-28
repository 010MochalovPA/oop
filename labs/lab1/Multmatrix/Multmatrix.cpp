#include <fstream>
#include <string>
#include <iostream>

using namespace std;
typedef double Matrix3x3[3][3];

int GetMatrix3x3FromStream(Matrix3x3 matrix, ifstream& input);
void CloseStreams(ifstream& input1, ifstream& input2);
void PrintMatrix3x3(Matrix3x3 matrix);
void MultiMatrix(Matrix3x3 matrix1, Matrix3x3 matrix2, Matrix3x3 result);
void PrintMessageInvalidMatrix3x3();
int CheckInputMatrix3x3Matching(ifstream& input);
int IsStringOfNumbers(string& str);

int CheckInputMatrix3x3Matching(ifstream& input)
{
	string temp;
	char ch;
	int count = 0;
	while (input >> temp)
	{
		count++;
		if (!IsStringOfNumbers(temp))
		{
			return 0;
		
		}
		if (count % 3 == 0 && input.get(ch) && ch != '\n')
		{
			return 0;
		}
		
		if (count > 9) return 0;
		
	}
	input.clear();
	input.seekg(0, ios::beg);
	return 1;
}

int IsStringOfNumbers(string& str) {
	
	for (char ch : str)
	{
		if (isalpha(ch))
		{
			return 0;
		}
	}

	return 1;
}

void PrintMessageInvalidMatrix3x3() 
{
	cout << "Invalid type of some matrix elements or format matrix" << endl
		 << "Usage: multmatrix.exe <matrix3x3 file1> <matrix3x3 file2>" << endl;
}

void CloseStreams(ifstream& input1, ifstream& input2)
{
	input1.close();
	input2.close();
}

int GetMatrix3x3FromStream(Matrix3x3 matrix, ifstream& input)
{
	if (!CheckInputMatrix3x3Matching(input))
	{
		return 0;
	}

	string temp;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			input >> temp;
			matrix[i][j] = stod(temp);
		}
	}

	return 1;
}

void PrintMatrix3x3(Matrix3x3 matrix)
{
	cout.setf(ios::fixed);
	cout.precision(3);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}

	cout.unsetf(ios::fixed);
}

void MultiMatrix(Matrix3x3 matrix1, Matrix3x3 matrix2, Matrix3x3 result)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
}
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid argument count" << endl
			 << "Usage: multmatrix.exe <matrix3x3 file1> <matrix3x3 file2>" << endl;
		return 1;
	}

	ifstream input1(argv[1]), input2(argv[2]);

	if (!input1.is_open() || !input2.is_open())
	{
		cout << "Failed to open " << (!input1.is_open() ? argv[1] : argv[2]) << " for reading" << endl;
		CloseStreams(input1, input2);
		return 1;
	}

	Matrix3x3 matrix1 = {};
	Matrix3x3 matrix2 = {};
	Matrix3x3 result = {};

	if (!GetMatrix3x3FromStream(matrix1, input1))
	{
		PrintMessageInvalidMatrix3x3();
		CloseStreams(input1, input2);
		return 1;
	}

	if (!GetMatrix3x3FromStream(matrix2, input2))
	{
		PrintMessageInvalidMatrix3x3();
		CloseStreams(input1, input2);
		return 1;
	}
	
	MultiMatrix(matrix1, matrix2, result);
	
	PrintMatrix3x3(result);

	CloseStreams(input1, input2);

	return 0;
}