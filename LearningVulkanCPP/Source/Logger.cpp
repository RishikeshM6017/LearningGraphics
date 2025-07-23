#include "PCH.h"
#include "Logger.h"

void Logger::SetMode(B8 mode)
{

}

void Logger::Print(const char* msg)
{
	console << msg << "\n";
}

void Logger::PrintList(const char** list, U32 size)
{
	for (U32 i = 0; i < size; i++)
	{
		console << list[i] << "\n";
	}
}

Logger::Logger()
{
}
