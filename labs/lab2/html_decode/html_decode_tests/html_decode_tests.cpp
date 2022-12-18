#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../html_decode_headers.h"

TEST_CASE("Testing a function for an correct value")
{
	std::istringstream input("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
	std::ostringstream output("");
	DecodeInputStream(input, output);
	CHECK(output.str() == "Cat <says> \"Meow\". M&M\'s\n");
}

TEST_CASE("Testing a function for an brocken mnemonic")
{
	std::istringstream input("Cat &lt;says&gt &quot;Meow&quot;. M&amp;M&apos;s");
	std::ostringstream output("");
	DecodeInputStream(input, output);
	CHECK(output.str() == "Cat <says&gt \"Meow\". M&M\'s\n");
}

TEST_CASE("Testing a function for an non-existent mnemonic")
{
	std::istringstream input("Cat &let;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
	std::ostringstream output("");
	DecodeInputStream(input, output);
	CHECK(output.str() == "Cat &let;says> \"Meow\". M&M\'s\n");
}

TEST_CASE("Testing a function for an empty input")
{
	std::istringstream input("");
	std::ostringstream output("");
	DecodeInputStream(input, output);
	CHECK(output.str() == "");
}