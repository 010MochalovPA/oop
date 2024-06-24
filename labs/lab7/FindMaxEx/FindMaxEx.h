#pragma once

#include <optional>
#include <vector>

// какие гарантии безопастности бывают? Чем они друг от друга отличаются.
template <typename T, typename Less>
bool FindMaxEx(const std::vector<T>& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	// Используем итератор, чтобы избежать копирования элементов ++
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