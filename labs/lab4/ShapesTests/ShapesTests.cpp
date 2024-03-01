#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Shapes/Point.h"
#include "../Shapes/LineSegment.h"
#include "../Shapes/Circle.h"
#include "../Shapes/Triangle.h"
#include "../Shapes/Rectangle.h"
#include "../Shapes/ShapeCreator.h"
#include "../Shapes/MockCanvas.h"
#include "../Shapes/ShapesApp.h"

TEST_CASE("create Shapes")
{
	GIVEN("Points")
	{
		Point p1(100, 100);
		Point p2(100, 200);
		Point p3(250, -100);
		Point p4(3, 2);
		Point p5(7, 5);
		Point p6(0, 0);

		THEN("Correct x and y values")
		{
			CHECK(p1.GetX() == 100);
			CHECK(p1.GetY() == 100);

			CHECK(p2.GetX() == 100);
			CHECK(p2.GetY() == 200);

			CHECK(p3.GetX() == 250);
			CHECK(p3.GetY() == -100);
		}

		WHEN("Create Lines")
		{
			LineSegment line1(p1, p2, 0);
			LineSegment line2(p2, p3, 1024);

			THEN("Check startPoint")
			{
				const Point startPoint = line1.GetStartPoint();

				CHECK(p1.GetX() == startPoint.GetX());
				CHECK(p1.GetY() == startPoint.GetY());
			}

			THEN("Check endPoint")
			{
				const Point endPoint = line1.GetEndPoint();

				CHECK(p2.GetX() == endPoint.GetX());
				CHECK(p2.GetY() == endPoint.GetY());
			}

			THEN("Check color")
			{
				CHECK(line1.GetOutlineColor() == 0);
				CHECK(line2.GetOutlineColor() == 1024);
			}

			THEN("Check area")
			{
				CHECK(line1.GetArea() == 0);
				CHECK(line2.GetArea() == 0);
			}

			THEN("Check perimeter")
			{
				CHECK(line1.GetPerimeter() == 100);
			}
		}

		WHEN("Create Circle")
		{
			Circle circ1(p1, 100, 0, 0);
			Circle circ2(p2, 80, 12500, 12500);
			Circle circ3(p3, -10, 12500, 12500);

			THEN("Check color")
			{
				CHECK(circ1.GetOutlineColor() == 0);
				CHECK(circ1.GetFillColor() == 0);

				CHECK(circ2.GetOutlineColor() == 12500);
				CHECK(circ2.GetFillColor() == 12500);
			}

			THEN("Check radius")
			{
				CHECK(circ1.GetRadius() == 100);
				CHECK(circ2.GetRadius() == 80);
				CHECK(circ3.GetRadius() == 10);
			}

			THEN("Check origin")
			{
				Point origin1 = circ1.GetOrigin();
				Point origin2 = circ2.GetOrigin();

				CHECK(origin1.GetX() == 100);
				CHECK(origin1.GetY() == 100);

				CHECK(origin2.GetX() == 100);
				CHECK(origin2.GetY() == 200);
			}

			THEN("Check area")
			{
				CHECK(circ1.GetArea() == circ1.GetRadius() * circ1.GetRadius() * M_PI);
				CHECK(circ2.GetArea() == circ2.GetRadius() * circ2.GetRadius() * M_PI);
			}

			THEN("Check perimeter")
			{
				CHECK(circ1.GetPerimeter() == 2 * circ1.GetRadius() * M_PI);
				CHECK(circ2.GetPerimeter() == 2 * circ2.GetRadius() * M_PI);
			}
		}

		WHEN("Create Triangle")
		{
			Triangle tri(p4, p5, p6, 0, 64000);

			LineSegment l1(p4, p5, 0);
			LineSegment l2(p5, p6, 0);
			LineSegment l3(p6, p4, 0);

			THEN("Check color")
			{
				CHECK(tri.GetOutlineColor() == 0);

				CHECK(tri.GetFillColor() == 64000);
			}

			THEN("Check area")
			{
				//CHECK(tri.GetArea() == 0.5);
			}

			THEN("Check perimeter")
			{
				CHECK(tri.GetPerimeter() == l1.GetPerimeter() + l2.GetPerimeter() + l3.GetPerimeter());
			}
		}

		/*WHEN("Create Rectangle")
		{
			Point p8(2, 2);
			Point p9(4, 4);
			
			Rectangle rect(p8, p9, 0, 64000);

			THEN("Check color")
			{
				CHECK(rect.GetOutlineColor() == 0);

				CHECK(rect.GetFillColor() == 64000);
			}
		}*/
	}
}

TEST_CASE("ShapesApp Canvas")
{
	GIVEN("MockCanvas")
	{
		ShapeCreator shapeCreator;
		MockCanvas mockCanvas;
		
		ShapesApp shapesApp(mockCanvas, shapeCreator, std::cin, std::cout);
		WHEN("Creating line")
		{
			shapesApp.CreateLine("0 0 1 1 FF0000");

			THEN("MockCanvas DrawLine should be called with correct parameters")
			{
				shapesApp.Draw();
				REQUIRE(mockCanvas.GetShapes() == "l0000000000010001ff0000");
			}

			shapesApp.CreateLine("2 2 3 3 FFFFFF");

			THEN("MockCanvas DrawLine should be called with correct parameters")
			{
				shapesApp.Draw();
				REQUIRE(mockCanvas.GetShapes() == "l0000000000010001ff0000l0002000200030003ffffff");
			}
		}

		WHEN("Creating rectangle")
		{
			shapesApp.CreateRectangle("0 0 2 2 00FF00 0000FF");

			THEN("MockCanvas DrawLine and FillPolygon should be called with correct parameters")
			{
				shapesApp.Draw();
				REQUIRE(mockCanvas.GetShapes() == "p000000000002000000020002000000020000ff"
												  "l000000000002000000ff00"
												  "l000200000002000200ff00"
												  "l000200020000000200ff00"
												  "l000000020000000000ff00");
			}
		}

		WHEN("Creating triangle")
		{
			shapesApp.CreateTriangle("0 0 1 1 2 0 0000FF FFFF00");

			THEN("MockCanvas DrawLine and FillPolygon should be called with correct parameters")
			{
				shapesApp.Draw();
				REQUIRE(mockCanvas.GetShapes() == "p000000000001000100020000ffff00"
												  "l00000000000100010000ff"
												  "l00010001000200000000ff"
												  "l00020000000000000000ff");
			}
		}

		WHEN("Creating circle")
		{
			shapesApp.CreateCircle("0 0 3 FF00FF 000000");

			THEN("MockCanvas DrawCircle and FillCircle should be called with correct parameters")
			{
				shapesApp.Draw();
				REQUIRE(mockCanvas.GetShapes() == "fc000000000003000000"
					                              "dc000000000003ff00ff");
			}
		}

		WHEN("Creating shapes")
		{
			shapesApp.CreateLine("0 0 1 1 FF0000");
			shapesApp.CreateRectangle("0 0 2 2 00FF00 0000FF");
			shapesApp.CreateTriangle("0 0 1 1 2 0 0000FF FFFF00");
			shapesApp.CreateCircle("0 0 3 FF00FF 000000");

			THEN("Shapes should be created with correct parameters")
			{
				shapesApp.Draw();
				REQUIRE(mockCanvas.GetShapes() == "l0000000000010001ff0000"
												  "p000000000002000000020002000000020000ff"
												  "l000000000002000000ff00"
												  "l000200000002000200ff00"
												  "l000200020000000200ff00"
												  "l000000020000000000ff00"
												  "p000000000001000100020000ffff00"
												  "l00000000000100010000ff"
												  "l00010001000200000000ff"
												  "l00020000000000000000ff"
												  "fc000000000003000000"
												  "dc000000000003ff00ff");
			}
			THEN("ShapesApp should get min perimeter and max area")
			{
				REQUIRE(shapesApp.GetMaxAreaShapeInfo() == "Circle: (0.00, 0.00) area 28.27 perimeter 18.85 radius 3.00 outline ff00ff fill 000000");
				REQUIRE(shapesApp.GetMinPerimeterShapeInfo() == "Line: (0.00, 0.00) (1.00, 1.00) area 0.00 perimeter 1.41 length 1.41 outline ff0000");
			}
		}
	}
}