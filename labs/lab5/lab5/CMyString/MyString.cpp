#include "MyString.h"

MyString::MyString()
	: m_size(0)
	, m_ptrString(std::make_unique<char[]>(1))
	, m_capacity(1)
{
}

MyString::MyString(const char* ptrString, size_t size)
	: m_capacity(size + 1)
	, m_ptrString(std::make_unique<char[]>(size + 1))
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
	: m_capacity(string.m_capacity)
	, m_ptrString(std::move(string.m_ptrString))
	, m_size(string.m_size)
{
	string.m_size = 0;
	string.m_capacity = 0;
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

void MyString::Clear() noexcept // сделать noexcept ++
{
	m_ptrString.reset();
	m_size = 0;
	m_capacity = 0;
}

MyString MyString::SubString(size_t start, size_t size) const
{
	// лучше сделать, чтобы старт был равен ++
	if (start > size)
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
		MyString tmp(string);
		std::swap(m_size, tmp.m_size);
		std::swap(m_capacity, tmp.m_capacity);
		std::swap(m_ptrString, tmp.m_ptrString);
	}

	return *this;
}

MyString& MyString::operator=(MyString&& string) noexcept
{
	if (this != &string)
	{
		m_ptrString.reset();
		m_size = 0; // у строки донора неправилная длина ++
		m_capacity = 0;
	
		std::swap(m_ptrString, string.m_ptrString);
		std::swap(m_size, string.m_size);
		std::swap(m_capacity, string.m_capacity);
	}

	return *this;
}

MyString MyString::operator+(const MyString& string) const
{
	MyString result(*this);
	result += string;
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

MyString& MyString::operator+=(const MyString& string) // вынести метод по резервированию вместимости
{
	size_t newSize = m_size + string.m_size;

	if (m_capacity < newSize + 1) // исправить название
	{
		m_capacity = newSize * 2 + 1; // проверить на переполнение
		std::unique_ptr<char[]> tmpPtr = std::make_unique<char[]>(m_capacity);

		std::copy(m_ptrString.get(), m_ptrString.get() + m_size, tmpPtr.get());

		m_ptrString = std::move(tmpPtr);
	}

	std::copy(string.m_ptrString.get(), string.m_ptrString.get() + string.m_size, m_ptrString.get() + m_size);

	m_size = newSize;
	m_ptrString[m_size] = CODE_ZERO_CHAR;

	return *this;
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

std::strong_ordering MyString::operator<=>(const MyString& string) const
{
	const char* left = GetStringData();
	const char* right = string.GetStringData();

	return std::lexicographical_compare_three_way(left, left + m_size, right, right + string.m_size);
}

std::ostream& operator<<(std::ostream& stream, const MyString& string) noexcept
{
	stream << string.GetStringData();

	return stream;
}

std::istream& operator>>(std::istream& stream, MyString& string) noexcept
{
	std::string stlString;
	stream >> stlString;
	string = MyString(stlString);
	return stream;
}

MyConstIterator MyString::Begin() const
{
	return MyConstIterator(m_ptrString.get());
}

MyConstIterator MyString::End() const
{
	return MyConstIterator(m_ptrString.get() + m_size);
}

MyIterator MyString::Begin()
{
    return MyIterator(m_ptrString.get());
}

MyIterator MyString::End()
{
    return MyIterator(m_ptrString.get() + m_size);
}