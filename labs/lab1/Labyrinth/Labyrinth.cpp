#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <optional>
//labyrinth
const int LABYRINTH_ROWS = 100;
const int LABYRINTH_COLS = 100;

using Labyrinth = std::array<std::array<char, LABYRINTH_COLS>, LABYRINTH_ROWS>;
using Waves = std::array<std::array<int, LABYRINTH_COLS>, LABYRINTH_ROWS>;

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

struct LabyrinthPoint
{
	int row;
	int col;
};

Args ParseArgs(const int& argc, char* argv[]);
void GetLabyrinthFromFile(std::string& inputFileName, Labyrinth& labyrinth);
void OutputLabyrinthToFile(std::string& outputFileName, Labyrinth& labyrinth);
void WavesInitialization(Waves& waves);
void LabyrinthInitialization(Labyrinth& labyrinth);
void FillWaves(Labyrinth& labyrinth, Waves& waves, LabyrinthPoint exit);
void DrowPointsToExit(Labyrinth& labyrinth, Waves& waves, LabyrinthPoint exitPoint, LabyrinthPoint startPoint);
void FindWayInLabyrunth(Labyrinth& labyrinth, Waves& waves);
std::string ConcatStringWithMessage(const std::string& exception);

void OutputLabyrinthToFile(std::string& outputFileName, Labyrinth& labyrinth) 
{
	std::ofstream output;
	output.open(outputFileName);

	if (!output.is_open())
	{
		throw std::invalid_argument("Failed to open <output file> for reading");
	}

	output.setf(std::ios_base::skipws);

	for (int i = 0; i < LABYRINTH_ROWS; i++)
	{
		for (int j = 0; j < LABYRINTH_COLS; j++)
		{
			output << labyrinth[i][j];
		}

		output << std::endl;
	}
}
void GetLabyrinthFromFile(std::string& inputFileName, Labyrinth& labyrinth)
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
	int labyrinthRow = 0;
	int labyrinthCol = 0;

	while (input >> character)
	{
		if (character == ' ' || character == '#' || character == 'A' || character == 'B')
		{
			labyrinth[labyrinthRow][labyrinthCol] = character;
			labyrinthCol++;

			if (character == 'A')
			{
				hasStart = true;
			}

			if (character == 'B')
			{
				hasExit = true;
			}
				
		}
		else if (character == '\n')
		{
			labyrinthRow++;
			labyrinthCol = 0;
		}
		else
		{
			throw std::invalid_argument("Invalid Labyrinth.");
		}

		if (labyrinthRow > LABYRINTH_ROWS - 1 || labyrinthCol > LABYRINTH_COLS - 1)
		{
			throw std::invalid_argument("Invalid Labyrinth.");
		}
	}

	if (!hasStart || !hasExit)
	{
		throw std::invalid_argument("Invalid Labyrinth.");
	}
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

void WavesInitialization(Waves& waves)
{
	for (int i = 0; i < LABYRINTH_ROWS; i++)
	{
		for (int j = 0; j < LABYRINTH_COLS; j++)
		{
			waves[i][j] = 0;
		}
	}
}

void LabyrinthInitialization(Labyrinth& labyrinth)
{
	for (int i = 0; i < LABYRINTH_ROWS; i++)
	{
		for (int j = 0; j < LABYRINTH_COLS; j++)
		{
			labyrinth[i][j] = ' ';
		}
	}
}


void FillWaves(Labyrinth& labyrinth, Waves& waves, LabyrinthPoint exit)
{
	int step = 1;
	bool hasPath = true;
	bool isFound = false;
	while (waves[exit.row][exit.col] == 0)
	{
		hasPath = false;
		for (int row = 0; row < LABYRINTH_ROWS; row++)
		{
			for (int col = 0; col < LABYRINTH_COLS; col++)
			{
				
				if (waves[row][col] == step)
				{
					
					if (col > 0 && (labyrinth[row][col - 1] == ' ' || labyrinth[row][col - 1] == 'B') && waves[row][col - 1] == 0)
					{
						waves[row][col - 1] = step + 1;
						hasPath = true;
					}

					if (col < (LABYRINTH_COLS - 1) && (labyrinth[row][col + 1] == ' ' || labyrinth[row][col + 1] == 'B') && waves[row][col + 1] == 0)
					{
						waves[row][col + 1] = step + 1;
						hasPath = true;
					}

					if (row > 0 && (labyrinth[row - 1][col] == ' ' || labyrinth[row - 1][col] == 'B') && waves[row - 1][col] == 0)
					{
						waves[row - 1][col] = step + 1;
						hasPath = true;
					}

					if (row < (LABYRINTH_ROWS - 1) && (labyrinth[row + 1][col] == ' ' || labyrinth[row + 1][col] == 'B') && waves[row + 1][col] == 0)
					{
						waves[row + 1][col] = step + 1;
						hasPath = true;
					}
				}
			}
		}

		step++;

		if (!hasPath)
		{
			throw std::invalid_argument("Invalid Labyrinth.");
		}
		
	}
	

}

void DrowPointsToExit(Labyrinth& labyrinth, Waves& waves, LabyrinthPoint exitPoint, LabyrinthPoint startPoint)
{
	LabyrinthPoint curPoint = exitPoint;
	
	while (curPoint.row != startPoint.row || curPoint.col != startPoint.col)
	{
		LabyrinthPoint minPoint = {};
		
		if (curPoint.row > 0 && waves[curPoint.row - 1][curPoint.col] < waves[curPoint.row][curPoint.col] && waves[curPoint.row - 1][curPoint.col] != 0)
		{
			minPoint.row = curPoint.row - 1;
			minPoint.col = curPoint.col;
		}
		
		if (curPoint.col < LABYRINTH_COLS - 1 && waves[curPoint.row][curPoint.col + 1] < waves[curPoint.row][curPoint.col] && waves[curPoint.row][curPoint.col + 1] != 0)
		{
			minPoint.row = curPoint.row;
			minPoint.col = curPoint.col + 1;
		}
		
		if (curPoint.row < LABYRINTH_ROWS - 1 && waves [curPoint.row + 1][curPoint.col] < waves[curPoint.row][curPoint.col] && waves[curPoint.row + 1][curPoint.col] != 0)
		{
			minPoint.row = curPoint.row + 1;
			minPoint.col = curPoint.col;
		}

		if (curPoint.col > 0 && waves [curPoint.row][curPoint.col - 1] < waves[curPoint.row][curPoint.col] && waves[curPoint.row][curPoint.col - 1] != 0)
		{
			minPoint.row = curPoint.row;
			minPoint.col = curPoint.col - 1;
		}

		labyrinth[minPoint.row][minPoint.col] = '.';
		curPoint = minPoint;
	}

	labyrinth[curPoint.row][curPoint.col] = 'A';
}

void FindWayInLabyrunth(Labyrinth& labyrinth, Waves& waves)
{
	LabyrinthPoint start = {};
	LabyrinthPoint exit = {};
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

	waves[start.row][start.col] = 1;
	
	FillWaves(labyrinth, waves, exit);
	DrowPointsToExit(labyrinth, waves, exit, start);	
}

std::string ConcatStringWithMessage(const std::string& exception)
{
	return exception + '\n'
		+ "Usage: labyrinth.exe <input file> <output file>" + '\n';
}

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArgs(argc, argv);

		Labyrinth labyrinth;
		LabyrinthInitialization(labyrinth);

		Waves waves;
		WavesInitialization(waves);

		GetLabyrinthFromFile(args.inputFileName, labyrinth);

		FindWayInLabyrunth(labyrinth, waves);
		
		OutputLabyrinthToFile(args.outputFileName, labyrinth);

		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cout << ConcatStringWithMessage(exception.what());

		return 1;
	}
}
