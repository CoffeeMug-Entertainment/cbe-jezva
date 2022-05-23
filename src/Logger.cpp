#include "Logger.hpp"
#include "Game.hpp"

Logger::Logger()
{
	std::cout << "Logger constructed!" << std::endl;
	logFile.open(Game::config.title + ".log", std::ofstream::out | std::ofstream::trunc);
}

Logger::~Logger()
{
	logFile.close();
}

void Logger::Log(std::string_view message)
{
	WriteToConsole(message);
	WriteToLogFile(message);
}

void Logger::LogError(std::string_view message)
{
	std::string errorMsg = "[ERROR]: " + std::string(message);

	WriteToErrorConsole(errorMsg);
	WriteToLogFile(errorMsg);
}

void Logger::ClearLogFile()
{
	
}

void Logger::WriteToLogFile(std::string_view message)
{
	this->logFile << message << std::endl;
}

void Logger::WriteToConsole(std::string_view message)
{
	std::cout << message << std::endl;
}

void Logger::WriteToErrorConsole(std::string_view message)
{
	std::cerr << message << std::endl;
}