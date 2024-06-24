#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CMyStack/MyStack.h"

SCENARIO("Тестирование функциональности StringStack")
{
	GIVEN("Пустой стек StringStack")
	{
		MyStack<std::string> stack;

		THEN("Он изначально пустой")
		{
			REQUIRE(stack.IsEmpty());
			REQUIRE(stack.GetSize() == 0);
			CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
			CHECK_THROWS_AS(stack.Pop(), std::logic_error);
		}

		WHEN("Строка добавляется в стек")
		{
			stack.Push("test 1");

			THEN("Стек больше не пустой")
			{
				REQUIRE_FALSE(stack.IsEmpty());
				REQUIRE(stack.GetSize() == 1);
				REQUIRE(stack.GetTop() == "test 1");
			}

			WHEN("Еще одна строка добавляется в стек")
			{
				stack.Push("test 2");

				THEN("Верхний элемент стека - последнее добавленное значение")
				{
					REQUIRE(stack.GetTop() == "test 2");
					REQUIRE(stack.GetSize() == 2);
				}

				WHEN("Верхний элемент удаляется")
				{
					stack.Pop();

					THEN("Размер стека уменьшается, а новый верхний элемент - предыдущее значение")
					{
						REQUIRE(stack.GetTop() == "test 1");
						REQUIRE(stack.GetSize() == 1);
					}
				}
			}
		}

		WHEN("Стек очищается")
		{
			stack.Push("test 1");
			stack.Push("test 2");
			stack.Clear();

			THEN("Стек пустой")
			{
				REQUIRE(stack.IsEmpty());
				REQUIRE(stack.GetSize() == 0);
				CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
				CHECK_THROWS_AS(stack.Pop(), std::logic_error);
			}
		}
	}

	GIVEN("Стек с несколькими элементами")
	{
		MyStack<int> stack;
		stack.Push(1);
		stack.Push(2);
		stack.Push(3);

		WHEN("Создается копия стека с использованием конструктора копирования")
		{
			MyStack<int> copy(stack);

			THEN("Копия равна оригиналу")
			{
				REQUIRE(copy.GetSize() == stack.GetSize());
				REQUIRE(copy.GetTop() == stack.GetTop());

				copy.Pop();
				stack.Pop();

				REQUIRE(copy.GetTop() == stack.GetTop());
			}
		}

		WHEN("Один стек присваивается другому с использованием оператора копирования")
		{
			MyStack<int> copy;
			copy = stack;

			THEN("Копия равна оригиналу")
			{
				REQUIRE(copy.GetSize() == stack.GetSize());
				REQUIRE(copy.GetTop() == stack.GetTop());

				copy.Pop();
				stack.Pop();

				REQUIRE(copy.GetTop() == stack.GetTop());
			}
		}

		WHEN("Стек перемещается с использованием конструктора перемещения")
		{
			MyStack<int> moved(std::move(stack));

			THEN("Перемещенный стек содержит элементы, а оригинальный пуст")
			{
				REQUIRE(moved.GetSize() == 3);
				REQUIRE(moved.GetTop() == 3);
				REQUIRE(stack.IsEmpty());
			}
		}

		WHEN("Один стек присваивается другому с использованием оператора перемещения")
		{
			MyStack<int> moved;
			moved = std::move(stack);

			THEN("Перемещенный стек содержит элементы, а оригинальный пуст")
			{
				REQUIRE(moved.GetSize() == 3);
				REQUIRE(moved.GetTop() == 3);
				REQUIRE(stack.IsEmpty());
			}
		}
	}

	GIVEN("Стек с одним элементом")
	{
		MyStack<std::string> stack;
		stack.Push("1");

		WHEN("Создается копия стека с использованием конструктора копирования")
		{
			MyStack<std::string> copy(stack);

			THEN("Копия равна оригиналу")
			{
				REQUIRE(copy.GetSize() == 1);
				REQUIRE(copy.GetTop() == "1");
			}
		}

		WHEN("Стек присваивается самому себе с использованием оператора копирования")
		{
			stack = stack;

			THEN("Стек остается неизменным")
			{
				REQUIRE(stack.GetSize() == 1);
				REQUIRE(stack.GetTop() == "1");
			}
		}

		WHEN("Стек присваивается самому себе с использованием оператора перемещения")
		{
			stack = std::move(stack);

			THEN("Стек остается неизменным")
			{
				REQUIRE(stack.GetSize() == 1);
				REQUIRE(stack.GetTop() == "1");
			}
		}
	}

	GIVEN("Стек с несколькими элементами, добавленными и удаленными")
	{
		MyStack<std::string> stack;
		stack.Push("1");
		stack.Push("2");
		stack.Push("3");
		stack.Pop();

		THEN("Верхний элемент стека - предпоследний добавленный элемент")
		{
			REQUIRE(stack.GetTop() == "2");
			REQUIRE(stack.GetSize() == 2);
		}
	}
}
