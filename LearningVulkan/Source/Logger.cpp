#include "PCH.h"
#include "Logger.h"

Logger* Logger::GetLogger()
{
	return logger;
}

void Logger::SetDebug(bool flag)
{
	enabled = flag;
}

bool Logger::IsActive()
{
	return enabled;
}

void Logger::Print(std::string msg)
{
	if (!enabled) return;

	std::cout << msg;
}

void Logger::Print(const char* msg)
{
	if (!enabled) return;

	std::cout << msg;
}


