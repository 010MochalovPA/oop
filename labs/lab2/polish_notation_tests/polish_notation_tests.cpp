#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../polish_notation/polish_notation.h"

TEST_CASE("correct value: (+ 7)")
{
	std::string line = "(+ 7)";
	std::stringstream stream(line);
	CHECK(CalculatePolishExpressionFromStream(stream) == 7);
}
// Добавить кейс со скобками  +++

TEST_CASE("incorrect value: (*)")
{
	std::string line = "(*)";
	std::stringstream stream(line);
	CHECK_THROWS(CalculatePolishExpressionFromStream(stream));
}

TEST_CASE("incorrect value: (+)")
{
	std::string line = "(+)";
	std::stringstream stream(line);
	CHECK_THROWS(CalculatePolishExpressionFromStream(stream));
}

TEST_CASE("correct value: (* 8)")
{
	std::string line = "(* 8)";
	std::stringstream stream(line);
	CHECK(CalculatePolishExpressionFromStream(stream) == 8);
}

TEST_CASE("correct value: (+ -1 2)")
{
	std::string line = "(+ -1 2)";
	std::stringstream stream(line);
	CHECK(CalculatePolishExpressionFromStream(stream) == 1);
}

TEST_CASE("correct value: (+ 2 3)")
{
	std::string line = "(+ 2 3)";
	std::stringstream stream(line);
	CHECK(CalculatePolishExpressionFromStream(stream) == 5);
}

TEST_CASE("correct value: (* (+ 5 -2) (+3 1))")
{
	std::string line = "(* (+ 5 -2) (+ 3 1))";
	std::stringstream stream(line);
	CHECK(CalculatePolishExpressionFromStream(stream) == 12);
}

TEST_CASE("correct value: (+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2)))")
{
	std::string line = "(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2)))";
	std::stringstream stream(line);
	CHECK(CalculatePolishExpressionFromStream(stream) == 33);
}

TEST_CASE("incorrect value: (+ a)")
{
	std::string line = "(+ a)";
	std::stringstream stream(line);
	CHECK_THROWS(CalculatePolishExpressionFromStream(stream));
}

TEST_CASE("incorrect value: (+ 5")
{
	std::string line = "(+ 5";
	std::stringstream stream(line);
	CHECK_THROWS(CalculatePolishExpressionFromStream(stream));
}

TEST_CASE("incorrect value: (+ 1 2 3 (1 2)))))")
{
	std::string line = "(+ 1 2 3 (1 2))";
	std::stringstream stream(line);
	CHECK_THROWS(CalculatePolishExpressionFromStream(stream));
}

TEST_CASE("incorrect value: (- 1 2)")
{
	std::string line = "(- 1 2)";
	std::stringstream stream(line);
	CHECK_THROWS(CalculatePolishExpressionFromStream(stream));
}

TEST_CASE("incorrect value: + 1 2)")
{
	std::string line = "+ 1 2)";
	std::stringstream stream(line);
	CHECK_THROWS(CalculatePolishExpressionFromStream(stream));
}