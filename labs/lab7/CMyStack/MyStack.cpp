#include "MyStack.h"
#include <algorithm>
#include <stdexcept>

template <typename T>
MyStack<T>::MyStack(const MyStack<T>& other)
{
	if (other.IsEmpty())
	{
		return;
	}

	MyStack tmp;
	Node* node = other.m_top;
	Node* prev = nullptr;

	while (node != nullptr)
	{
		Node* newNode = new Node(node->m_data, nullptr);

		if (prev == nullptr)
		{
			tmp.m_top = newNode;
		}
		else
		{
			prev->m_prev = newNode;
		}

		prev = newNode;
		node = node->m_prev;
		++tmp.m_size;
	}

	SwapStack(tmp);
}

template <typename T>
MyStack<T>::MyStack(MyStack<T>&& stack) noexcept
	: m_size(stack.m_size)
	, m_top(stack.m_top)
{
	stack.m_size = 0;
	stack.m_top = nullptr;
}

template <typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T>& stack)
{
	if (&stack != this)
	{
		MyStack tmp(stack);
		SwapStack(tmp);
	}
	return *this;
}

template <typename T>
MyStack<T>& MyStack<T>::operator=(MyStack<T>&& stack) noexcept
{
	if (&stack != this)
	{
		Clear();
		SwapStack(stack);
	}
	return *this;
}

template <typename T>
bool MyStack<T>::IsEmpty() const
{
	return !m_size;
}

template <typename T>
const T& MyStack<T>::GetTop() const
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}

	return m_top->m_data;
}

template <typename T>
void MyStack<T>::Push(const T& value)
{
	m_top = new Node(value, m_top);
	++m_size;
}

template <typename T>
void MyStack<T>::Pop()
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}

	Node* node = m_top;
	m_top = m_top->m_prev;
	delete node;

	--m_size;
}

template <typename T>
void MyStack<T>::Clear() noexcept
{
	while (m_top != nullptr)
	{
		Node* node = m_top;
		m_top = m_top->m_prev;
		delete node;
	}

	m_size = 0;
}

template <typename T>
size_t MyStack<T>::GetSize() const
{
	return m_size;
}

template <typename T>
MyStack<T>::MyStack() noexcept
	: m_size(0)
	, m_top(nullptr)
{
}

template <typename T>
MyStack<T>::~MyStack() noexcept
{
	Clear();
}

template <typename T>
void MyStack<T>::SwapStack(MyStack<T>& stack) noexcept
{
	std::swap(m_size, stack.m_size);
	std::swap(m_top, stack.m_top);
}