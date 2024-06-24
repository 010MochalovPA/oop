#pragma once
#include <string>

class StringStack
{
public:
	bool IsEmpty() const;
	const std::string& GetTop() const;
	void Push(const std::string& string);
	void Pop();
	void Clear() noexcept;
	size_t GetSize() const;

	StringStack() noexcept;
	~StringStack() noexcept;
	StringStack(const StringStack& stack);
	StringStack(StringStack&& stack) noexcept;
	StringStack& operator=(StringStack const& stack);
	StringStack& operator=(StringStack&& stack) noexcept;

private:
	struct Node
	{
		Node(const std::string& data, Node* prev)
			: m_data(data)
			, m_prev(prev)
		{
		}

		std::string m_data;
		Node* m_prev;
	};

	void SwapStack(StringStack& stack) noexcept;

	Node* m_top = nullptr;
	size_t m_size = 0;
};