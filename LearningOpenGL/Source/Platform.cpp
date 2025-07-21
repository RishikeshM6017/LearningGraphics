#include "PCH.h"

#include "Platform.h"

String Platform::ReadFileToString(const char* filePath)
{
	InputFileStream file(filePath, IOS::binary);

	if (file)
	{
		String buffer;
		file.seekg(0, IOS::end);
		buffer.resize(file.tellg());
		file.seekg(0, IOS::beg);
		file.read(&buffer[0], buffer.size());
		file.close();
		return buffer;
	}

	throw(errno);
}
