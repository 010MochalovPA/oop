#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <optional>
#include <set>

//labyrinth
const __int64 LABYRINTH_ROWS = 100;
const __int64 LABYRINTH_COLS = 100;
const std::set<char> AVALIBLE_CHARS = { ' ', 'A', 'B', '#', '\n' };
const std::set<std::string> DIRECTIONS = { "left", "right", "top", "bottom" };

using Labyrinth = std::array<std::array<char, LABYRINTH_COLS>, LABYRINTH_ROWS>;
using WavesMatrix = std::array<std::array<int, LABYRINTH_COLS>, LABYRINTH_ROWS>;

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

struct LabyrinthPoint
{
	__int64 row;
	__int64 col;
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

	char character;
	bool hasStart = false;
	bool hasExit = false; 
	int row = 0;
	int col = 0;

	Labyrinth labyrinth = InitializateLabyrinth(labyrinth);

	while (input >> character)
	{
		if (AVALIBLE_CHARS.find(character) == AVALIBLE_CHARS.end())
		{
			throw std::invalid_argument("Invalid Labyrinth."); 	
		}
		
		if (character == '\n')
		{
			row++;
			col = 0;
		}
		else
		{
			labyrinth[row][col] = character;
			col++;
		}

	    if (character == 'A')
		{
			if (hasStart)
			{
				throw std::invalid_argument("Invalid Labyrinth."); 						
			}
		
			hasStart = true;
		}

		if (character == 'B')
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

void AddNextStepWaves(const Labyrinth& lab, WavesMatrix& waves, bool& hasPath, int step)
{
	hasPath = false;
	for (size_t row = 0; row < LABYRINTH_ROWS; row++)
	{
		for (size_t col = 0; col < LABYRINTH_COLS; col++)
		{
			if (waves[row][col] == step) //дублирование, слишком длинные строчки ++
			{
				if (col != 0)
				{
					const int& leftFieldLabyrinthValue = lab[row][col - 1];
					int& leftFieldWavesValue = waves[row][col - 1];
					
					if (IsAvaliblePoint(leftFieldLabyrinthValue, leftFieldWavesValue))
					{
						leftFieldWavesValue = step + 1;
						hasPath = true;
					}
				}		
			
				if (col != LABYRINTH_COLS - 1)
				{
					const int& rightFieldLabyrinthValue = lab[row][col + 1];
					int& rightFieldWavesValue = waves[row][col + 1];

					if (IsAvaliblePoint(rightFieldLabyrinthValue, rightFieldWavesValue))
					{
						rightFieldWavesValue = step + 1;
						hasPath = true;
					}
				}

				if (row != 0)
				{
					const int& topFieldLabyrinthValue = lab[row - 1][col];
					int& topFieldWavesValue = waves[row - 1][col];

					if (IsAvaliblePoint(topFieldLabyrinthValue, topFieldWavesValue))
					{
						topFieldWavesValue = step + 1;
						hasPath = true;
					}
				} 

				if (row != (LABYRINTH_ROWS - 1))
				{
					const int& bottomFieldLabyrinthValue = lab[row + 1][col];
					int& bottomFieldWavesValue = waves[row + 1][col];

					if (IsAvaliblePoint(bottomFieldLabyrinthValue, bottomFieldWavesValue))
					{
						bottomFieldWavesValue = step + 1;
						hasPath = true;
					}
				}
			}
		}
	}
}

void FillWaves(const Labyrinth& labyrinth, WavesMatrix& waves, LabyrinthPoint exit)
{
	int step = 1;
	bool hasPath = true;
	bool isFound = false;
	//3 цикла - сложно (исправил) ++
	while (!waves[exit.row][exit.col])
	{
		AddNextStepWaves(labyrinth, waves, hasPath, step);
		step++;

		if (!hasPath)
		{
			throw std::invalid_argument("Invalid Labyrinth.");
		}	
	}
}

CheckedValues GetCheckedFieldsValue(__int64 row, __int64 col, const WavesMatrix& waves)
{
	int top = waves[row][col];
	int bottom = waves[row][col];
	int right = waves[row][col];
	int left = waves[row][col];

	if (row > 0)
	{
		top = waves[row - 1][col];
	}

	if (col < LABYRINTH_COLS - 1)
	{
		right = waves[row][col + 1];
	}

	if (row < LABYRINTH_ROWS - 1)
	{
		bottom = waves[row + 1][col];
	}

	if (col > 0)
	{
		left = waves[row][col - 1];
	}

	return { top, bottom, right, left };
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

		if (top != 0 && top < currentValue)
		{
			minRow = row - 1;
			minCol = col;
		}
		
		if (right != 0 && right < currentValue)
		{
			minRow = row;
			minCol = col + 1;
		}
		
		if (bottom != 0 && bottom < currentValue)
		{
			minRow = row + 1;
			minCol = col;
		}

		if (left != 0 && left < currentValue)
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

	for (int i = 0; i < LABYRINTH_ROWS; i++)
	{
		for (int j = 0; j < LABYRINTH_COLS; j++)
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

//возврат значения из функции, а не входной параметр
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
