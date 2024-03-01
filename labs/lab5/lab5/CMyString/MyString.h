#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <compare>
#include <iostream>

const char CODE_ZERO_CHAR = '\0';

class MyString
{
public:
	MyString();
	MyString(const char* pString);
	MyString(const char* pString, size_t size);
	MyString(MyString const& string);
	MyString(MyString&& string) noexcept;
	MyString(std::string const& stlString);

	size_t GetLength() const;
	const char* GetStringData() const;
	MyString SubString(size_t start, size_t size = SIZE_MAX) const;
	void Clear();

	MyString& operator=(MyString const& string);
	MyString& operator=(MyString&& string) noexcept;
	MyString operator+(MyString const& string) const;
	MyString operator+(const std::string& stlString) const;
	friend MyString operator+(const std::string& stlString, const MyString& myString);
	MyString operator+(const char* ptrString) const;
	friend MyString operator+(const char* ptrString, const MyString& myString);
	MyString& operator+=(const MyString& string);
	bool operator==(const MyString& other) const;
	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	std::strong_ordering operator<=>(MyString const& str) const;
	friend std::istream& operator>>(std::istream& is, MyString& str);
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);

private:
	std::unique_ptr<char[]> m_ptrString;
	size_t m_size;
};