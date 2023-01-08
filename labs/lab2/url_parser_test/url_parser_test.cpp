#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../url_parser/url_parser.h"

TEST_CASE("Testing function GetProtocolFromString")
{
	CHECK(GetProtocolFromString("htTp") == Protocol::HTTP);
	CHECK(GetProtocolFromString("FTP") == Protocol::FTP);
	CHECK(GetProtocolFromString("HTtpS") == Protocol::HTTPS);
	CHECK(GetProtocolFromString("error") == Protocol::HTTPS);
}

TEST_CASE("Testing function GetPortFromString")
{
	CHECK(GetPortFromString("80", Protocol::HTTP) == 80);
	CHECK(GetPortFromString("", Protocol::HTTPS) == 443);
	CHECK(GetPortFromString("200", Protocol::HTTP) == 200);
	CHECK(GetPortFromString("", Protocol::FTP) == 21);
}

TEST_CASE("Testing function ParseURL")
{
	std::string line = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	
	URL url = { line };

	CHECK(ParseURL(url.url, url.protocol, url.port, url.host, url.document));
	CHECK(url.url == line);
	CHECK(url.protocol == Protocol::HTTP);
	CHECK(url.host == "www.mysite.com");
	CHECK(url.port == 80);
	CHECK(url.document == "/docs/document1.html?page=30&lang=en#title");

	std::string line2 = "http://www.mysite.com:8080";

	URL url2 = { line2 };

	CHECK(ParseURL(url2.url, url2.protocol, url2.port, url2.host, url2.document));
	CHECK(url2.url == line2);
	CHECK(url2.protocol == Protocol::HTTP);
	CHECK(url2.host == "www.mysite.com");
	CHECK(url2.port == 8080);
	CHECK(url2.document == "");

	std::string line3 = "https://www.mysite.com/lang=en#title";

	URL url3 = { line3 };

	CHECK(ParseURL(url3.url, url3.protocol, url3.port, url3.host, url3.document));
	CHECK(url3.url == line3);
	CHECK(url3.protocol == Protocol::HTTPS);
	CHECK(url3.host == "www.mysite.com");
	CHECK(url3.port == 443);
	CHECK(url3.document == "/lang=en#title");
}

TEST_CASE("Testing Invalid URL")
{
	std::string line1 = "http://www.mysite.com:65536/docs/document1.html?page=30&lang=en#title";
	URL url1 = { line1 };
	CHECK(!ParseURL(url1.url, url1.protocol, url1.port, url1.host, url1.document));

	std::string line2 = "http://www.mysite.com:0000/docs/document1.html?page=30&lang=en#title";
	URL url2 = { line2 };
	CHECK(!ParseURL(url2.url, url2.protocol, url2.port, url2.host, url2.document));

	std::string line3 = "http://www.mysite.com//docs/document1.html?page=30&lang=en#title";
	URL url3 = { line3 };
	CHECK(!ParseURL(url3.url, url3.protocol, url3.port, url3.host, url3.document));

	std::string line4 = "httpp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	URL url4 = { line4 };
	CHECK(!ParseURL(url4.url, url4.protocol, url4.port, url4.host, url4.document));

	std::string line5 = "http:///www.mysite.com";
	URL url5 = { line5 };
	CHECK(!ParseURL(url5.url, url5.protocol, url5.port, url5.host, url5.document));
}