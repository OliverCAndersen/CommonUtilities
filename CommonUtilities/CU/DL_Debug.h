#pragma once

#include <string>
#include <iostream>
#include <fstream>

extern "C"
{
#include <corecrt.h>

	_ACRTIMP void __cdecl _wassert(
		_In_z_ wchar_t const* _Message,
		_In_z_ wchar_t const* _File,
		_In_   unsigned       _Line
	);

#define DL_ASSERT(aExpression) (void)(																										\
		(!!(aExpression)) ||																				/*If false, print and crash*/	\
			(DL_Debug::Debug::GetInstance()->AssertMessage(__FILE__,__LINE__,__FUNCTION__, #aExpression),	/*Assert Message*/				\
			_wassert(_CRT_WIDE(#aExpression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__))					/*Crash program*/				\
			,0)																								/*Evaluates this*/				\
	)

#define DL_CRASH(aMessage) (void)(																										\
		(DL_Debug::Debug::GetInstance()->AssertMessage(__FILE__,__LINE__,__FUNCTION__, #aMessage),		/*Assert Message*/				\
		_wassert(_CRT_WIDE(#aMessage), _CRT_WIDE(__FILE__), (unsigned)(__LINE__))						/*Crash program*/				\
		,0)																								/*Evaluates this*/				\
	)
};

#define DL_DEBUG( ... )  DL_Debug::Debug::GetInstance()->DebugMessage(__FILE__, __LINE__,__FUNCTION__,__VA_ARGS__);

#define DL_PRINT(aMessage)  DL_Debug::Debug::GetInstance()->PrintMessage(aMessage);

#define DL_PRINT_CALLSTACK(aMessage)  DL_Debug::Debug::GetInstance()->PrintCallstackMessage(aMessage);

namespace DL_Debug
{
	class Debug
	{
	public:
		static bool Create(std::string aFileName = "DebugLog");
		static bool Destroy();
		static Debug* GetInstance();

		void AssertMessage(const char *aFileName, int aLine, const char *aFunctionName, const char *aString);
		void DebugMessage(const char * aFile, const int aLine, const char *aFileName, const char *aFormattedString, ...);
		void PrintMessage(const char *aString);
		void PrintCallstackMessage(const char *aString);

	private:
		Debug(std::string aFileName);
		~Debug();

		static Debug* ourInstance;
		static std::ofstream ourDebugFile;
	};
}