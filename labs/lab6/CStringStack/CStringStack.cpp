#include <iostream>
#include "StringStack.h"

int main()
{
	StringStack stack;

	stack.Push("1");
	stack.Push("1");
	stack.Push("1");

	StringStack moved(std::move(stack));
}