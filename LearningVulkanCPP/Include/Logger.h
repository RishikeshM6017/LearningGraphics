#pragma once

#include "PCH.h"



class Logger
{
public:
	static Logger* GetLogger()
	{
		static Logger instance;
		return &instance;
	}

	void SetMode(B8 mode);
	void Print(const char* msg);
	void PrintList(const char** list, U32 size);

private:
	OutputStream& console = std::cout;

	Logger();

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
};

