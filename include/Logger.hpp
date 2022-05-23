#ifndef LOGGER_HPP
#define LOGGER_HPP 

#include <iostream>
#include <fstream>
#include "Macros.hpp"

//TODO: Add these to logs
//#define LogA(message) TempLog(__PRETTY_FUNCTION__,  message)

class Logger
{
	public:
		Logger();
		~Logger();
		void Log(std::string_view message);
	    void LogError(std::string_view message);

	    /*void TempLog(const char* caller, std::string message)
	    {
	    	Log(std::string(caller) + " " + message);
	    }*/

	private:

		std::ofstream logFile;
		void ClearLogFile();
		void WriteToLogFile(std::string_view message);

		void WriteToConsole(std::string_view message);
		void WriteToErrorConsole(std::string_view message);
	};

#endif