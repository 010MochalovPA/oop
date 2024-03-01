#include "MyString.h"

MyString::MyString()
	: m_size(0)
	, m_ptrString(std::make_unique<char[]>(1))
{
}

MyString::MyString(const char* ptrString, size_t size)
	: m_ptrString(std::make_unique<char[]>(size + 1))
	, m_size(size)
{
	std::copy(ptrString, ptrString + size, m_ptrString.get());
	m_ptrString[m_size] = CODE_ZERO_CHAR;
}

MyString::MyString(const MyString& string)
	: MyString(string.GetStringData(), string.GetLength())
{
}

MyString::MyString(MyString&& string) noexcept
	: MyString(nullptr, 0)
{
	std::swap(m_size, string.m_size);
	std::swap(m_ptrString, string.m_ptrString);
}

MyString::MyString(const char* ptrString)
	: MyString(ptrString, strlen(ptrString))
{
}

MyString::MyString(const std::string& stlString)
	: MyString(stlString.c_str(), stlString.size())
{
}

size_t MyString::GetLength() const
{
	return m_size;
}

const char* MyString::GetStringData() const
{
	return m_size != 0 ? m_ptrString.get() : "\0";
}

void MyString::Clear()
{
	m_ptrString.reset();
	m_size = 0;
}

MyString MyString::SubString(size_t start, size_t size) const
{
	if (start >= size)
	{
		throw std::out_of_range("Substring out of range");
	}

	if (size == SIZE_MAX || size > m_size - start)
	{
		size = m_size - start;
	}

	return MyString(m_ptrString.get() + start, size);
}

MyString& MyString::operator=(const MyString& string)
{
	if (this != &string)
	{
		MyString temp(string);
		std::swap(m_size, temp.m_size);
		std::swap(m_ptrString, temp.m_ptrString);
	}

	return *this;
}

MyString& MyString::operator=(MyString&& string) noexcept
{
	if (this != &string)
	{
		m_ptrString.reset();

		std::swap(m_ptrString, string.m_ptrString);
		std::swap(m_size, string.m_size);
	}

	return *this;
}

MyString MyString::operator+(const MyString& string) const
{
	MyString result;
	result.m_size = m_size + string.m_size;
	result.m_ptrString = std::make_unique<char[]>(result.m_size + 1);

	std::copy(m_ptrString.get(), m_ptrString.get() + m_size, result.m_ptrString.get());
	std::copy(string.m_ptrString.get(), string.m_ptrString.get() + string.m_size, result.m_ptrString.get() + m_size);

	result.m_ptrString[result.m_size] = CODE_ZERO_CHAR;

	return result;
}

MyString MyString::operator+(const std::string& stlString) const
{
	return *this + MyString(stlString);
}

MyString operator+(const std::string& stlString, const MyString& myString)
{
	return MyString(stlString) + myString;
}

MyString operator+(const char* ptrString, const MyString& myString)
{
	return MyString(ptrString) + myString;
}

MyString MyString::operator+(const char* ptrString) const
{
	return *this + MyString(ptrString);
}

MyString& MyString::operator+=(const MyString& string)
{
	return *this = *this + string;
}

bool MyString::operator==(const MyString& string) const
{
	if (m_size != string.m_size)
	{
		return false;
	}

	return std::equal(m_ptrString.get(), m_ptrString.get() + m_size, string.m_ptrString.get());
}

char& MyString::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index is out of range");
	}

	return m_ptrString[index];
}

const char& MyString::operator[](size_t index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index is out of range");
	}

	return m_ptrString[index];
}

std::strong_ordering MyString::operator<=>(MyString const& string) const
{
	const char* leftString = GetStringData();
	const char* rightString = string.GetStringData();

	return std::lexicographical_compare_three_way(leftString, leftString + m_size, rightString, rightString + string.m_size);
}

std::ostream& operator<<(std::ostream& stream, MyString const& string)
{
	stream << string.GetStringData();

	return stream;
}

std::istream& operator>>(std::istream& stream, MyString& string)
{
	std::string stlString;
	std::getline(stream, stlString);
	string = MyString(stlString);

	return stream;
}