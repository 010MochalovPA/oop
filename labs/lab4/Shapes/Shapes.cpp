#include "stdafx.h"
#include "ShapeCreator.h"
#include "ShapesApp.h"
#include "Canvas.h"

int main()
{
	ShapeCreator shapeCreator;
	Canvas canvas;
	ShapesApp shapesApp(canvas, shapeCreator, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail() && !shapesApp.isExit())
	{
		try
		{
			shapesApp.HandleCommand();
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << "Error parsing input: " << e.what() << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	shapesApp.PrintShapesInfo();
	shapesApp.PrintInfo();
	shapesApp.Draw();
	shapesApp.ClearShapes();
	return 0;
}