#include "StringStack.h"
#include <algorithm>
#include <stdexcept>

StringStack::StringStack() noexcept
	: m_size(0)
	, m_top(nullptr)
{
}

StringStack::StringStack(const StringStack& other)
{
	if (other.IsEmpty())
	{
		return;
	}

	StringStack tmp;
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

StringStack::StringStack(StringStack&& stack) noexcept
	: m_size(stack.m_size)
	, m_top(stack.m_top)
{
	stack.m_size = 0;
	stack.m_top = nullptr;
}

StringStack::~StringStack() noexcept
{
	Clear();
}

StringStack& StringStack::operator=(const StringStack& stack)
{
	if (&stack != this)
	{
		StringStack tmp(stack);
		// сделать метод swap ++
		SwapStack(tmp);
	}
	return *this;
}

void StringStack::SwapStack(StringStack& stack) noexcept
{
	std::swap(m_size, stack.m_size);
	std::swap(m_top, stack.m_top);
}

StringStack& StringStack::operator=(StringStack&& other) noexcept
{
	if (&other != this)
	{
		Clear();
		SwapStack(other);
	}
	return *this;
}

bool StringStack::IsEmpty() const
{
	return !m_size;
}

// тут лучше возвращать конст ссылку ++
const std::string& StringStack::GetTop() const
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}

	return m_top->m_data;
}

void StringStack::Push(const std::string& string)
{
	m_top = new Node(string, m_top);
	++m_size;
}

void StringStack::Pop()
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

void StringStack::Clear() noexcept
{
	while (m_top != nullptr)
	{
		Node* node = m_top;
		m_top = m_top->m_prev;
		delete node;
	}

	m_size = 0;
}

size_t StringStack::GetSize() const
{
	return m_size;
}