#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <optional>
#include <set>
#include <queue>

//labyrinth
const size_t LABYRINTH_ROWS = 100;
const size_t LABYRINTH_COLS = 100;
const std::set<char> AVALIBLE_CHARS = { ' ', 'A', 'B', '#', '\n' };

using Labyrinth = std::array<std::array<char, LABYRINTH_COLS>, LABYRINTH_ROWS>;
using WavesMatrix = std::array<std::array<int, LABYRINTH_COLS>, LABYRINTH_ROWS>;

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

struct LabyrinthPoint
{
	size_t row, col;
};

struct LabyrinthPoints
{
	LabyrinthPoint start;
	LabyrinthPoint exit;
};

struct CheckedValues
{
	int top, bottom, right, left;
};

Args ParseArgs(const int& argc, char* argv[]);
Labyrinth GetLabyrinthFromFile(std::string& inputFileName);
void OutputLabyrinthToFile(std::string& outputFileName,const Labyrinth& labyrinth);
WavesMatrix InitializateWaves(WavesMatrix& waves);
Labyrinth InitializateLabyrinth(Labyrinth& labyrinth);
void FillWaves(const Labyrinth& labyrinth, WavesMatrix& waves, LabyrinthPoint exit);
Labyrinth DrowPointsToExit(Labyrinth& labyrinth, const WavesMatrix& waves,
	const LabyrinthPoint exitPoint, const LabyrinthPoint startPoint);
Labyrinth FindWayInLabyrinth(Labyrinth& labyrinth);
std::string ConcatStringWithMessage(const std::string& exception);

void OutputLabyrinthToFile(std::string& outputFileName, const Labyrinth& labyrinth) 
{
	std::ofstream output;
	output.open(outputFileName);

	if (!output.is_open())
	{
		throw std::invalid_argument("Failed to open <output file> for reading");
	}

	for (int i = 0; i < LABYRINTH_ROWS; i++)
	{
		for (int j = 0; j < LABYRINTH_COLS; j++)
		{
			output << labyrinth[i][j];
		}

		output << std::endl;
	}
}

Labyrinth GetLabyrinthFromFile(std::string& inputFileName)
{
	std::ifstream input;
	input.open(inputFileName);

	if (!input.is_open())
	{
		throw std::invalid_argument("Failed to open <input file> for reading");
	}

	input.unsetf(std::ios_base::skipws);

	char ch;
	bool hasStart = false;
	bool hasExit = false; 
	int row = 0;
	int col = 0;

	Labyrinth labyrinth = InitializateLabyrinth(labyrinth);

	while (input >> ch)
	{
		if (AVALIBLE_CHARS.find(ch) == AVALIBLE_CHARS.end())
		{
			throw std::invalid_argument("Invalid Labyrinth."); 	
		}
		
		if (ch == '\n')
		{
			row++;
			col = 0;
		}
		else
		{
			labyrinth[row][col] = ch;
			col++;
		}

	    if (ch == 'A')
		{
			if (hasStart)
			{
				throw std::invalid_argument("Invalid Labyrinth."); 						
			}
		
			hasStart = true;
		}

		if (ch == 'B')
		{
			if (hasExit)
			{
				throw std::invalid_argument("Invalid Labyrinth.");
			}

			hasExit = true;
		}
	}

	if (!hasStart || !hasExit)
	{
		throw std::invalid_argument("Invalid Labyrinth.");
	}

	return labyrinth;
}

Args ParseArgs(const int& argc, char* argv[])
{
	if (argc != 3)
	{
		throw std::invalid_argument("Invalid argument count");
	}

	Args args = {};

	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	if (args.inputFileName.empty() || args.outputFileName.empty())
	{
		throw std::invalid_argument("Invalid argument");
	}

	return args;
}
//просто вернуть результат ++
WavesMatrix InitializateWaves(WavesMatrix& waves)
{
	for (int i = 0; i < LABYRINTH_ROWS; i++)
	{
		for (int j = 0; j < LABYRINTH_COLS; j++)
		{
			waves[i][j] = 0;
		}
	}

	return waves;
}

Labyrinth InitializateLabyrinth(Labyrinth& labyrinth)
{
	for (int i = 0; i < LABYRINTH_ROWS; i++)
	{
		for (int j = 0; j < LABYRINTH_COLS; j++)
		{
			labyrinth[i][j] = ' ';
		}
	}

	return labyrinth;
}

bool IsAvaliblePoint(char labyrinthPoint, int wavesPoint)
{
	return (labyrinthPoint == ' ' || labyrinthPoint == 'B') && wavesPoint == 0;
}

void MarkFieldWaves(const int& labyrinthFieldValue, int& wavesFieldValue, bool& hasPath, int step,
	const LabyrinthPoint& field, std::queue<LabyrinthPoint>& queue)
{
	if (IsAvaliblePoint(labyrinthFieldValue, wavesFieldValue))
	{
		wavesFieldValue = step + 1;
		hasPath = true;
		queue.push(field);
	}
}

void MarkFieldsWavesAround(size_t row, size_t col, const Labyrinth& lab,
	WavesMatrix& waves, bool& hasPath, int& step, std::queue<LabyrinthPoint>& queue)
{
	if (col != 0)
	{
		const int& leftFieldLabyrinthValue = lab[row][col - 1];
		int& leftFieldWavesValue = waves[row][col - 1];
		LabyrinthPoint field = { row, col - 1 };
		MarkFieldWaves(leftFieldLabyrinthValue, leftFieldWavesValue, hasPath, step, field, queue);
	}

	if (col != LABYRINTH_COLS - 1)
	{
		const int& rightFieldLabyrinthValue = lab[row][col + 1];
		int& rightFieldWavesValue = waves[row][col + 1];
		LabyrinthPoint field = { row, col + 1 };
		MarkFieldWaves(rightFieldLabyrinthValue, rightFieldWavesValue, hasPath, step, field, queue);
	}

	if (row != 0)
	{
		const int& topFieldLabyrinthValue = lab[row - 1][col];
		int& topFieldWavesValue = waves[row - 1][col];
		LabyrinthPoint field = { row - 1, col};
		MarkFieldWaves(topFieldLabyrinthValue, topFieldWavesValue, hasPath, step, field, queue);
	}

	if (row != (LABYRINTH_ROWS - 1))
	{
		const int& bottomFieldLabyrinthValue = lab[row + 1][col];
		int& bottomFieldWavesValue = waves[row + 1][col];
		LabyrinthPoint field = { row + 1, col};
		MarkFieldWaves(bottomFieldLabyrinthValue, bottomFieldWavesValue, hasPath, step, field, queue);
	}
}

LabyrinthPoint FindStart(WavesMatrix& waves)
{
	for (size_t row = 0; row < LABYRINTH_ROWS; row++)
	{
		for (size_t col = 0; col < LABYRINTH_COLS; col++)
		{
			if (waves[row][col] == 1) // дублирование, слишком длинные строчки ++
			{
				return { row, col };
			}
		}
	}
}

void FillWaves(const Labyrinth& lab, WavesMatrix& waves, LabyrinthPoint exit)
{
	std::queue<LabyrinthPoint> queue; 
	int step = 1;
	bool hasPath = true;
	bool isFound = false;
	LabyrinthPoint start = FindStart(waves);
	waves[start.row][start.col] = 1;
	queue.push(start);
	//3 цикла - сложно (исправил) ++
	while (!waves[exit.row][exit.col] || !queue.empty())
	{
		LabyrinthPoint field = queue.front();
		queue.pop();
		MarkFieldsWavesAround(field.row, field.col, lab, waves, hasPath, step);
		step++;

		if (!hasPath)
		{
			throw std::invalid_argument("Invalid Labyrinth.");
		}	
	}
}

CheckedValues GetCheckedFieldsValue(__int64 row, __int64 col, const WavesMatrix& waves)
{
	CheckedValues checkedValues = {};

	if (row > 0)
	{
		checkedValues.top = waves[row - 1][col];
	}

	if (col < LABYRINTH_COLS - 1)
	{
		checkedValues.right = waves[row][col + 1];
	}

	if (row < LABYRINTH_ROWS - 1)
	{
		checkedValues.bottom = waves[row + 1][col];
	}

	if (col > 0)
	{
		checkedValues.left = waves[row][col - 1];
	}

	return checkedValues;
}

Labyrinth DrowPointsToExit(Labyrinth& labyrinth, const WavesMatrix& waves,
	const LabyrinthPoint curPoint, const LabyrinthPoint startPoint)
{ // сложный код, строки не более 100
	auto [row, col] = curPoint;
	
	while (row != startPoint.row || col != startPoint.col)
	{
		__int64 minCol = col;
		__int64 minRow = row;

		int currentValue = waves[row][col];

		auto [top, bottom, right, left] = GetCheckedFieldsValue(row, col, waves);

		if (top == 1 || bottom == 1 || right == 1 || left == 1)
		{
			return labyrinth;
		}

		if (top && top < currentValue)
		{
			minRow = row - 1;
			minCol = col;
		}
		
		if (right && right < currentValue)
		{
			minRow = row;
			minCol = col + 1;
		}
		
		if (bottom && bottom < currentValue)
		{
			minRow = row + 1;
			minCol = col;
		}

		if (left && left < currentValue)
		{
			minRow = row;
			minCol = col - 1;
		}

		row = minRow;
		col = minCol;
		labyrinth[row][col] = '.';
	}
}

LabyrinthPoints GetStartAndExitPosition(Labyrinth& labyrinth)
{
	LabyrinthPoint start, exit;

	for (size_t i = 0; i < LABYRINTH_ROWS; i++)
	{
		for (size_t j = 0; j < LABYRINTH_COLS; j++)
		{
			if (labyrinth[i][j] == 'A')
			{
				start = { i, j };
			}

			if (labyrinth[i][j] == 'B')
			{
				exit = { i, j };
			}
		}
	}
	return { start, exit };
}

Labyrinth FindWayInLabyrinth(Labyrinth& labyrinth)
{
	auto [start, exit] = GetStartAndExitPosition(labyrinth); // использовал деструктуризацию

	WavesMatrix waves = InitializateWaves(waves);

	waves[start.row][start.col] = 1;
	
	FillWaves(labyrinth, waves, exit);
	return DrowPointsToExit(labyrinth, waves, exit, start);	
}

std::string ConcatStringWithMessage(const std::string& exception)
{
	return exception + '\n'
		+ "Usage: labyrinth.exe <input file> <output file>" + '\n';
}

//возврат значения из функции, а не входной параметр ++
int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArgs(argc, argv);
		
		Labyrinth labyrinth = GetLabyrinthFromFile(args.inputFileName); // возвращать значение +
		
		Labyrinth result = FindWayInLabyrinth(labyrinth); // функция может создать внутри waves +
		
		OutputLabyrinthToFile(args.outputFileName, result);

		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cout << ConcatStringWithMessage(exception.what());

		return 1;
	}
}
