#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HTTP URL/HttpUrl.h"
#include "../HTTP URL/UrlParsingError.h"

SCENARIO("Testing full url constructor")
{
	GIVEN("Valid URLs")
	{
		WHEN("URL has HTTP protocol and custom port")
		{
			HttpUrl url("http://example.com:8080/page");
			THEN("HttpUrl object is constructed correctly")
			{
				REQUIRE(url.GetDomain() == "example.com");
				REQUIRE(url.GetDocument() == "/page");
				REQUIRE(url.GetProtocol() == Protocol::HTTP);
				REQUIRE(url.GetPort() == 8080);
				REQUIRE(url.GetURL() == "http://example.com:8080/page");
			}
		}

		WHEN("URL has HTTP protocol and default port")
		{
			HttpUrl url("hTTp://example.com/page");
			THEN("HttpUrl object is constructed correctly")
			{
				REQUIRE(url.GetDomain() == "example.com");
				REQUIRE(url.GetDocument() == "/page");
				REQUIRE(url.GetProtocol() == Protocol::HTTP);
				REQUIRE(url.GetPort() == 80);
				REQUIRE(url.GetURL() == "http://example.com/page");
			}
		}

		WHEN("URL has HTTPS protocol and no document")
		{
			HttpUrl url("httPS://example.com");
			THEN("HttpUrl object is constructed correctly")
			{
				REQUIRE(url.GetDomain() == "example.com");
				REQUIRE(url.GetDocument() == "/");
				REQUIRE(url.GetProtocol() == Protocol::HTTPS);
				REQUIRE(url.GetPort() == 443);
				REQUIRE(url.GetURL() == "https://example.com/");
			}
		}

		WHEN("URL has HTTPS protocol and custom document")
		{
			HttpUrl url("HTTPs://example.com/page");
			THEN("HttpUrl object is constructed correctly")
			{
				REQUIRE(url.GetDomain() == "example.com");
				REQUIRE(url.GetDocument() == "/page");
				REQUIRE(url.GetProtocol() == Protocol::HTTPS);
				REQUIRE(url.GetPort() == 443);
				REQUIRE(url.GetURL() == "https://example.com/page");
			}
		}

		WHEN("URL has HTTP protocol and port 0")
		{
			HttpUrl url("http://example.com:1/page");
			THEN("HttpUrl object is constructed correctly")
			{
				REQUIRE(url.GetDomain() == "example.com");
				REQUIRE(url.GetDocument() == "/page");
				REQUIRE(url.GetProtocol() == Protocol::HTTP);
				REQUIRE(url.GetPort() == 1);
				REQUIRE(url.GetURL() == "http://example.com:1/page");
			}
		}

		WHEN("URL has FTP protocol and no document")
		{
			HttpUrl url("ftp://example.com/page");
			THEN("HttpUrl object is constructed correctly")
			{
				REQUIRE(url.GetDomain() == "example.com");
				REQUIRE(url.GetDocument() == "/page");
				REQUIRE(url.GetProtocol() == Protocol::FTP);
				REQUIRE(url.GetPort() == 21);
				REQUIRE(url.GetURL() == "ftp://example.com/page");
			}
		}

		WHEN("URL has FTP protocol and custom port")
		{
			HttpUrl url("ftp://example.com:21/page");
			THEN("HttpUrl object is constructed correctly")
			{
				REQUIRE(url.GetDomain() == "example.com");
				REQUIRE(url.GetDocument() == "/page");
				REQUIRE(url.GetProtocol() == Protocol::FTP);
				REQUIRE(url.GetPort() == 21);
				REQUIRE(url.GetURL() == "ftp://example.com/page");
			}

			WHEN("URL has FTP protocol and custom port")
			{
				HttpUrl url("ftp://example.com:65535/page");
				THEN("HttpUrl object is constructed correctly")
				{
					REQUIRE(url.GetDomain() == "example.com");
					REQUIRE(url.GetDocument() == "/page");
					REQUIRE(url.GetProtocol() == Protocol::FTP);
					REQUIRE(url.GetPort() == 65535);
					REQUIRE(url.GetURL() == "ftp://example.com:65535/page");
				}
			}
		}
	}

	GIVEN("Invalid URLs with custom document")
	{

		WHEN("URL has invalid port")
		{

			THEN("Exception is thrown")
			{
				CHECK_THROWS_AS(HttpUrl("example.com", "/page", Protocol::FTP, 0), UrlParsingError);
				CHECK_THROWS_AS(HttpUrl("example.com", "/page", Protocol::FTP, 65537), UrlParsingError);
				CHECK_THROWS_AS(HttpUrl("http://example.com:0/other_document.html?page=30&lang=en#title"), UrlParsingError);
			}
		}
		WHEN("URL has invalid port")
		{
			THEN("Exception is thrown")
			{
				CHECK_THROWS_AS(HttpUrl("http://example.com:65536/other_document.html?page=30&lang=en#title"), UrlParsingError);
				CHECK_THROWS_AS(HttpUrl("http://example.com:0/other_document.html?page=30&lang=en#title"), UrlParsingError);
			}
		}

		WHEN("URL has invalid protocol")
		{
			THEN("Exception is thrown")
			{
				CHECK_THROWS_AS(HttpUrl("httpp://example.com/other_document.html?page=30&lang=en#title"), UrlParsingError);
			}
		}

		WHEN("URL has missing domain")
		{
			THEN("Exception is thrown")
			{
				CHECK_THROWS_AS(HttpUrl("http:///example.com"), UrlParsingError);
			}
		}

		WHEN("URL has invalid port syntax")
		{
			THEN("Exception is thrown")
			{
				CHECK_THROWS_AS(HttpUrl("http://example.com:/custom_document:8080"), UrlParsingError);
			}
		}

		WHEN("URL has multiple colons")
		{
			THEN("Exception is thrown")
			{
				CHECK_THROWS(HttpUrl("http://example.com::/custom_document"));
			}
		}

		WHEN("URL has invalid port value")
		{
			THEN("Exception is thrown")
			{
				CHECK_THROWS_AS(HttpUrl("http://example.com:100:/custom_document"), UrlParsingError);
			}
		}
	}
}