#include "DL_Debug.h"
#include "DL_StackWalker.h"
#include "Macros.h"
#include "assert.h"
#include <cstdarg>

#define GET_DATE_AND_TIME "_" __DATE__ "_" __TIME__

namespace DL_Debug
{
	Debug* Debug::ourInstance;
	std::ofstream Debug::ourDebugFile;

	Debug::Debug(std::string aFileName)
	{
		ourDebugFile.open(aFileName);
	}
	Debug::~Debug()
	{
	}

	bool Debug::Create(std::string aFileName)
	{
		assert((ourInstance == nullptr) && "Debugger already created");

		std::string dateAndTime = GET_DATE_AND_TIME;

		for (size_t i = 0; i < dateAndTime.length(); ++i)
		{
			if (dateAndTime[i] == ' ')
			{
				if (dateAndTime[i + 1] == ' ')
				{
					dateAndTime.replace(i, 2, "-");
				}
				else
				{
					dateAndTime.replace(i, 1, "-");
				}
			}
			else if (dateAndTime[i] == ':')
			{
				dateAndTime.replace(i, 1, "-");
			}
		}

		dateAndTime = dateAndTime.substr(0, dateAndTime.length() - 3);		

		aFileName += dateAndTime;
		aFileName += ".txt";

		ourInstance = new Debug(aFileName);
		if (ourInstance == nullptr)
		{
			return false;
		}
		return true;
	}

	bool Debug::Destroy()
	{
		ourDebugFile.close();
		SAFE_DELETE(ourInstance);
		return true;
	}

	Debug* Debug::GetInstance()
	{
		assert(ourInstance != nullptr && "Don't forget to use Create() on the Debugger");
		return ourInstance;
	}

	void Debug::AssertMessage(const char * aFileName, int aLine, const char * aFunctionName, const char * aMessage)
	{
		ourDebugFile << "-------------------------ASSERT-------------------------" << std::endl;
		ourDebugFile << "File: " << aFileName << std::endl;
		ourDebugFile << "Line: " << aLine << std::endl;
		ourDebugFile << "Function: " << aFunctionName << std::endl;
		ourDebugFile << "Message: " << aMessage << std::endl;
		ourDebugFile << std::endl;

		ourDebugFile << "\t>>>>>>>>>>---------------CALLSTACK---------------<<<<<<<<<<" << std::endl;
		StackWalker stackWalker;
		stackWalker.ShowCallstack();

		ourDebugFile.flush();

		/*Need to include windows.h for this
		std::string commandAndFolderToOpen = "explorer ";						

		char working_directory[MAX_PATH + 1];
		GetCurrentDirectoryA(sizeof(working_directory), working_directory);
		commandAndFolderToOpen += working_directory;

		system(commandAndFolderToOpen.c_str());*/
	}

	void Debug::DebugMessage(const char * aFile, const int aLine, const char * aFileName, const char * aFormattedMessage, ...)
	{
		ourDebugFile << "-------------------------DEBUG--------------------------" << std::endl;
		ourDebugFile << "File: " << aFileName << std::endl;
		ourDebugFile << "Line: " << aLine << std::endl;
		ourDebugFile << "Message: ";

		char buffer[256];
		va_list args;
		va_start(args, aFormattedMessage);
		vsprintf_s(buffer, aFormattedMessage, args);
		perror(buffer);
		va_end(args);

		ourDebugFile << buffer << std::endl;

		ourDebugFile << std::endl;
		ourDebugFile.flush();
	}

	void Debug::PrintMessage(const char * aMessage)
	{
		ourDebugFile << "-------------------------PRINT--------------------------" << std::endl;
		ourDebugFile << aMessage << std::endl;
		ourDebugFile << std::endl;
		ourDebugFile.flush();
	}

	void Debug::PrintCallstackMessage(const char * aMessage)
	{
		ourDebugFile << "\t" << aMessage;
		ourDebugFile.flush();
	}
}