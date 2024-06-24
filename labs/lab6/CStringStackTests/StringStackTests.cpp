#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CStringStack/StringStack.h"

SCENARIO("������������ ���������������� StringStack")
{
	GIVEN("������ ���� StringStack")
	{
		StringStack stack;

		THEN("�� ���������� ������")
		{
			REQUIRE(stack.IsEmpty());
			REQUIRE(stack.GetSize() == 0);
			CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
			CHECK_THROWS_AS(stack.Pop(), std::logic_error);
		}

		WHEN("������ ����������� � ����")
		{
			stack.Push("test 1");

			THEN("���� ������ �� ������")
			{
				REQUIRE_FALSE(stack.IsEmpty());
				REQUIRE(stack.GetSize() == 1);
				REQUIRE(stack.GetTop() == "test 1");
			}

			WHEN("��� ���� ������ ����������� � ����")
			{
				stack.Push("test 2");

				THEN("������� ������� ����� - ��������� ����������� ������")
				{
					REQUIRE(stack.GetTop() == "test 2");
					REQUIRE(stack.GetSize() == 2);
				}

				WHEN("������� ������� ���������")
				{
					stack.Pop();

					THEN("������ ����� �����������, � ����� ������� ������� - ���������� ������")
					{
						REQUIRE(stack.GetTop() == "test 1");
						REQUIRE(stack.GetSize() == 1);
					}
				}
			}
		}

		WHEN("���� ���������")
		{
			stack.Push("test 1");
			stack.Push("test 2");
			stack.Clear();

			THEN("���� ������")
			{
				REQUIRE(stack.IsEmpty());
				REQUIRE(stack.GetSize() == 0);
				CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
				CHECK_THROWS_AS(stack.Pop(), std::logic_error);
			}
		}
	}

	GIVEN("���� � ����������� ����������")
	{
		StringStack stack;
		stack.Push("1");
		stack.Push("2");
		stack.Push("3");

		WHEN("��������� ����� ����� � �������������� ������������ �����������")
		{
			StringStack copy(stack);

			THEN("����� ����� ���������")
			{
				REQUIRE(copy.GetSize() == stack.GetSize());
				REQUIRE(copy.GetTop() == stack.GetTop());

				copy.Pop();
				stack.Pop();

				REQUIRE(copy.GetTop() == stack.GetTop());
			}
		}

		WHEN("���� ���� ������������� ������� � �������������� ��������� �����������")
		{
			StringStack copy;
			copy = stack;

			THEN("����� ����� ���������")
			{
				REQUIRE(copy.GetSize() == stack.GetSize());
				REQUIRE(copy.GetTop() == stack.GetTop());

				copy.Pop();
				stack.Pop();

				REQUIRE(copy.GetTop() == stack.GetTop());
			}
		}

		WHEN("���� ������������ � �������������� ������������ �����������")
		{
			StringStack moved(std::move(stack));

			THEN("������������ ���� �������� ��������, � ������������ ����")
			{
				REQUIRE(moved.GetSize() == 3);
				REQUIRE(moved.GetTop() == "3");
				REQUIRE(stack.IsEmpty());
			}
		}

		WHEN("���� ���� ������������� ������� � �������������� ��������� �����������")
		{
			StringStack moved;
			moved = std::move(stack);

			THEN("������������ ���� �������� ��������, � ������������ ����")
			{
				REQUIRE(moved.GetSize() == 3);
				REQUIRE(moved.GetTop() == "3");
				REQUIRE(stack.IsEmpty());
			}
		}
	}

	GIVEN("���� � ����� ���������")
	{
		StringStack stack;
		stack.Push("1");

		WHEN("��������� ����� ����� � �������������� ������������ �����������")
		{
			StringStack copy(stack);

			THEN("����� ����� ���������")
			{
				REQUIRE(copy.GetSize() == 1);
				REQUIRE(copy.GetTop() == "1");
			}
		}

		WHEN("���� ������������� ������ ���� � �������������� ��������� �����������")
		{
			stack = stack;

			THEN("���� �������� ����������")
			{
				REQUIRE(stack.GetSize() == 1);
				REQUIRE(stack.GetTop() == "1");
			}
		}

		WHEN("���� ������������� ������ ���� � �������������� ��������� �����������")
		{
			stack = std::move(stack);

			THEN("���� �������� ����������")
			{
				REQUIRE(stack.GetSize() == 1);
				REQUIRE(stack.GetTop() == "1");
			}
		}
	}

	GIVEN("���� � ����������� ����������, ������������ � ����������")
	{
		StringStack stack;
		stack.Push("1");
		stack.Push("2");
		stack.Push("3");
		stack.Pop();

		THEN("������� ������� ����� - ������������� ����������� �������")
		{
			REQUIRE(stack.GetTop() == "2");
			REQUIRE(stack.GetSize() == 2);
		}
	}
}
