#pragma once

#include <optional>
#include <vector>

// ����� �������� ������������� ������? ��� ��� ���� �� ����� ����������.
template <typename T, typename Less>
bool FindMaxEx(const std::vector<T>& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	// ���������� ��������, ����� �������� ����������� ��������� ++
	auto max = arr.begin();

	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		if (less(*max, *it))
		{
			max = it;
		}
	}

	maxValue = *max;
	return true;
}