#pragma once

#include "stdafx.h" // не подключать в заголовочных файлах. только в cpp
// у интерфейса IStringable нет клиентов, он не нужен
class IStringable
{
public:
	virtual ~IStringable() {}
	virtual std::string ToString() const = 0;
};