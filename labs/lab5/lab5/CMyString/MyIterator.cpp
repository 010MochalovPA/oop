#include "MyIterator.h"

MyConstIterator::MyConstIterator(const char* ptr)
	: m_ptr(ptr)
{
}

MyConstIterator::reference MyConstIterator::operator*() const
{
	return *m_ptr;
}

MyConstIterator& MyConstIterator::operator++()
{
	++m_ptr;
	return *this;
}

MyConstIterator MyConstIterator::operator++(int)
{
	MyConstIterator it = *this;
	++m_ptr;
	return it;
}

MyConstIterator& MyConstIterator::operator--()
{
	--m_ptr;
	return *this;
}

MyConstIterator MyConstIterator::operator--(int)
{
	MyConstIterator it = *this;
	--m_ptr;
	return it;
}

MyConstIterator MyConstIterator::operator+(difference_type n) const
{
	return MyConstIterator(m_ptr + n);
}

MyConstIterator operator+(MyConstIterator::difference_type n, const MyConstIterator& it)
{
	return MyConstIterator(n + it.m_ptr);
}

MyConstIterator::difference_type MyConstIterator::operator-(const MyConstIterator& other) const
{
	return m_ptr - other.m_ptr;
}

MyIterator::MyIterator(char* ptr)
	: m_ptr(ptr)
{
}

MyIterator::reference MyIterator::operator*()
{
	return const_cast<reference>(*m_ptr);
}

MyIterator& MyIterator::operator++()
{
	++m_ptr;
	return *this;
}

MyIterator& MyIterator::operator--()
{
	--m_ptr;
	return *this;
}

MyIterator MyIterator::operator++(int)
{
	MyIterator it = *this;
	++m_ptr;
	return it;
}

MyIterator MyIterator::operator--(int)
{
	MyIterator it = *this;
	--m_ptr;
	return it;
}

MyIterator MyIterator::operator+(difference_type n) const
{
	return MyIterator(m_ptr + n);
}

MyIterator::difference_type MyIterator::operator-(const MyIterator& other) const
{
	return m_ptr - other.m_ptr;
}

MyIterator operator+(MyIterator::difference_type n, const MyIterator& it)
{
	return MyIterator(n + it.m_ptr);
}