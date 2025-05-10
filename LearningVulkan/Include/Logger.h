#pragma once

class Logger
{
public:
	//Logger();
	//~Logger();

public:
	static Logger*	GetLogger();

	void SetDebug(bool flag);
	bool IsActive();

	void Print(std::string msg);
	void Print(const char* msg);

private:
	bool enabled = false;

public:
	static Logger* logger;
};

