#pragma once

#include "stdafx.h" // �� ���������� � ������������ ������. ������ � cpp
// � ���������� IStringable ��� ��������, �� �� �����
class IStringable
{
public:
	virtual ~IStringable() {}
	virtual std::string ToString() const = 0;
};