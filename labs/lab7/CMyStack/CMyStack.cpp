#include "MyStack.h"
#include <iostream>
#include <string>

int main()
{
	MyStack<int> stack;

	stack.Push(1);
	stack.Push(1);
	stack.Push(1);

	MyStack<int> moved(std::move(stack));
}