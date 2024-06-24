#pragma once
#include <iterator>

class MyConstIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = const char;
	using reference = const char&;

	MyConstIterator(const char* ptr);

	reference operator*() const;

	MyConstIterator& operator++();
	MyConstIterator operator++(int);
	MyConstIterator& operator--();
	MyConstIterator operator--(int);
	MyConstIterator operator+(difference_type n) const;
	friend MyConstIterator operator+(difference_type n, const MyConstIterator& it);

	difference_type operator-(const MyConstIterator& other) const;

private:
	const char* m_ptr;
};

class MyIterator // вынести класс
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = char;
	using reference = char&;

	MyIterator(char* ptr);

	reference operator*();

	MyIterator& operator++();
	MyIterator operator++(int);
	MyIterator& operator--();
	MyIterator operator--(int);
	MyIterator operator+(difference_type n) const;
	difference_type operator-(const MyIterator& other) const;

	friend MyIterator operator+(difference_type n, const MyIterator& it);

private:
	char* m_ptr;
};