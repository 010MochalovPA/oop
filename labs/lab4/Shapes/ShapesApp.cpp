#include "ShapesApp.h"

namespace
{
	const std::regex HEX_COLOR_REGEX = std::regex("^[A-Fa-f0-9]{6}$");
	
	bool IsHex(const std::string& string)
	{
		return std::regex_match(string, HEX_COLOR_REGEX);
	}

	uint32_t HexToInt(const std::string& string)
	{
		if (!IsHex(string))
		{
			throw std::invalid_argument("Invalid color format");
		}

		std::istringstream stream(string);
		uint32_t color;

		stream >> std::hex >> color;

		return color;
	}

	uint32_t ParseColorFromStream(std::istream& stream)
	{
		std::string colorStr;
		if (!(stream >> colorStr))
		{
			return 0;
		}

		return HexToInt(colorStr);
	}
}

ShapesApp::ShapesApp(ICanvas& canvas, ShapeCreator& shapeCreator, std::istream& input, std::ostream& output)
	: m_canvas(canvas)
	, m_shapeCreator(shapeCreator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "line", [this](const std::string& args) { return CreateLine(args); } },
		{ "rectangle", [this](const std::string& args) { return CreateRectangle(args); } },
		{ "triangle", [this](const std::string& args) { return CreateTriangle(args); } },
		{ "circle", [this](const std::string& args) { return CreateCircle(args); } },
		{ "exit", [this](const std::string& args) { return Exit(/*args*/); } },
		{ "print", [this](const std::string& args) { return PrintInfo(/*args*/); } },
		//  { "help", [this](const std::string& args) { return PrintFunctions(args); } } 
		})
{
}

void ShapesApp::HandleCommand()
{
	std::string line;
	std::getline(m_input, line);

	std::istringstream stream(line);

	std::string action;
	std::string args;
	std::getline(stream, action, ' ');

	args = std::getline(stream, args) ? args : "";
	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(args);
	}

	throw std::invalid_argument("Incorrect command!");
}

void ShapesApp::CreateLine(const std::string& args)
{
	LineArgs lineArgs = ParseLineArgs(args);

	Point startPoint(lineArgs.startX, lineArgs.startY);
	Point endPoint(lineArgs.endX, lineArgs.endY);

	return m_shapeCreator.CreateLine(startPoint, endPoint, lineArgs.color);
}

void ShapesApp::CreateRectangle(const std::string& args)
{
	RectArgs rectArgs = ParseRectangleArgs(args);

	Point leftTop(rectArgs.leftTopX, rectArgs.leftTopY);
	Point rightBottom(rectArgs.rightBottomX, rectArgs.rightBottomY);

	m_shapeCreator.CreateRectangle(leftTop, rightBottom, rectArgs.outlineColor, rectArgs.fillColor);
}

void ShapesApp::CreateTriangle(const std::string& args)
{
	TriangleArgs triangleArgs = ParseTriangleArgs(args);

	Point p1(triangleArgs.x1, triangleArgs.y1);
	Point p2(triangleArgs.x2, triangleArgs.y2);
	Point p3(triangleArgs.x3, triangleArgs.y3);

	m_shapeCreator.CreateTriangle(p1, p2, p3, triangleArgs.outlineColor, triangleArgs.fillColor);
}

void ShapesApp::CreateCircle(const std::string& args)
{
	CircleArgs circleArgs = ParseCircleArgs(args);

	Point origin(circleArgs.originX, circleArgs.originY);
	
	m_shapeCreator.CreateCircle(origin, circleArgs.radius, circleArgs.outlineColor, circleArgs.fillColor);
}

void ShapesApp::Exit()
{
	m_exit = true;
}

bool ShapesApp::isExit() const
{
	return m_exit;
}

void ShapesApp::PrintInfo() const
{
	std::vector<IShape*> shapes = m_shapeCreator.GetShapes();
	m_output << "Shapes:" << std::endl;
	for (auto shape: shapes)
	{
		m_output << shape->ToString() << std::endl;
	}
}

std::string ShapesApp::GetMaxAreaShapeInfo() const
{
	std::vector<IShape*> shapes = m_shapeCreator.GetShapes();
	auto maxAreaShape = std::max_element(shapes.begin(), shapes.end(),
		[](const IShape* a, const IShape* b) {
			return a->GetPerimeter() < b->GetPerimeter();
		});

	return (*maxAreaShape)->ToString();
}

std::string ShapesApp::GetMinPerimeterShapeInfo() const
{
	std::vector<IShape*> shapes = m_shapeCreator.GetShapes();

	auto maxAreaShape = std::min_element(shapes.begin(), shapes.end(),
		[](const IShape* a, const IShape* b) {
			return a->GetPerimeter() < b->GetPerimeter();
		});

	return (*maxAreaShape)->ToString();
}



void ShapesApp::PrintShapesInfo() const
{
	std::vector<IShape*> shapes = m_shapeCreator.GetShapes();

	if (shapes.empty())
	{
		m_output << "No shapes" << std::endl;
		return;
	}

	m_output << std::endl 
			 << "Shape with the maximum area:" << std::endl
			 << GetMaxAreaShapeInfo() << std::endl
			 << std::endl
			 << "Shape with the minimum perimeter:" << std::endl
			 << GetMinPerimeterShapeInfo() << std::endl
			 << std::endl;
}

void ShapesApp::Draw() const
{
	std::vector<IShape*> shapes = m_shapeCreator.GetShapes();

	for (auto shape : shapes)
	{
		shape->Draw(m_canvas);
	}

	m_canvas.Draw();
}

void ShapesApp::ClearShapes()
{
	m_canvas.ClearShapes();
}

LineArgs ShapesApp::ParseLineArgs(const std::string& string)
{
	LineArgs args{};
	std::string color;
	std::stringstream stream(string);

	if (!(stream >> args.startX >> args.startY >> args.endX >> args.endY))
	{
		throw std::invalid_argument("Invalid numeric values in input");
	}

	args.color = ParseColorFromStream(stream);

	std::string extra;
	if (stream >> extra)
	{
		throw std::invalid_argument("Unexpected extra input");
	}

	return { args };
}

RectArgs ShapesApp::ParseRectangleArgs(const std::string& string)
{
	RectArgs args{};
	std::string outlineColor, fillColor;
	std::stringstream stream(string);

	if (!(stream >> args.leftTopX >> args.leftTopY >> args.rightBottomX >> args.rightBottomY))
	{
		throw std::invalid_argument("Invalid numeric values in input");
	}

	args.outlineColor = ParseColorFromStream(stream);
	args.fillColor = ParseColorFromStream(stream);

	std::string extra;
	if (stream >> extra)
	{
		throw std::invalid_argument("Unexpected extra input");
	}

	return args;
}

TriangleArgs ShapesApp::ParseTriangleArgs(const std::string& string)
{
	TriangleArgs args{};
	std::string outlineColor, fillColor;
	std::stringstream stream(string);

	if (!(stream >> args.x1 >> args.y1 >> args.x2 >> args.y2 >> args.x3 >> args.y3))
	{
		throw std::invalid_argument("Invalid numeric values in input");
	}

	args.outlineColor = ParseColorFromStream(stream);
	args.fillColor = ParseColorFromStream(stream);

	std::string extra;
	if (stream >> extra)
	{
		throw std::invalid_argument("Unexpected extra input");
	}

	return args;
}

CircleArgs ShapesApp::ParseCircleArgs(const std::string& string)
{
	CircleArgs args{};
	std::string outlineColor, fillColor;
	std::stringstream stream(string);

	if (!(stream >> args.originX >> args.originY >> args.radius))
	{
		throw std::invalid_argument("Invalid numeric values in input");
	}

	args.outlineColor = ParseColorFromStream(stream);
	args.fillColor = ParseColorFromStream(stream);

	std::string extra;
	if (stream >> extra)
	{
		throw std::invalid_argument("Unexpected extra input");
	}

	return args;
}

std::vector<IShape*> ShapesApp::GetShapes() const
{
	return m_shapeCreator.GetShapes();
}

