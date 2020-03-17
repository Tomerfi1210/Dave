#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <mutex>
#include <time.h>
#include <unordered_map>
#include <iomanip>
#include <sstream>

#define DATE_TIME_FORMAT "%Y-%m-%d~%X"
#define LOG_FILENAME "log.txt"


std::string CurrentDateTime()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), DATE_TIME_FORMAT);
	return ss.str();
}
//make a strong type
enum class Loger_Levels :int
{
	DEBUG_, INFO, ERROR, WARNING, MAX
};


//helps convert enum to its underlying type(int)
template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e) {
	return static_cast<typename std::underlying_type<E>::type>(e);
}


class Logger
{
public:
	~Logger();
	static Logger& getInstance();
	template<class T>
	void addLog(const T& data, Loger_Levels level = Loger_Levels::DEBUG_)
	{
		//locking mutex for thread safe logging
		std::lock_guard<std::mutex> guard(m_mutex);

		auto index = to_underlying(level);
		if (index >= to_underlying(Loger_Levels::MAX)) {
			level = Loger_Levels::ERROR;
			m_logFile << "BAD LOG_EVEL GIVEN, auto changed to ERROR------\n";
		}
		auto level_string = m_levels[to_underlying(level)];

		m_logFile << CurrentDateTime() << "|\t[" << level_string << "] |";
		m_logFile << data << "\n";
		//writing to logger ASAP
		m_logFile.flush();
		//guard will unlock mutex when destroyed
	   // m_mutex.unlock();
	}

private:
	Logger();
	Logger(const Logger&) = delete;
	Logger operator= (const Logger&) = delete;
	std::ofstream m_logFile;
	std::mutex m_mutex;
	std::string m_levels[to_underlying(Loger_Levels::MAX)];
	//std::unordered_map<Loger_Levels,std::string> m_levels ;
};

//function returns a string of current time
//-------------------------------------------------------------------------
Logger::Logger()
{
	//TODO change the append to truncate if u wanna remove last log
	m_logFile.open(LOG_FILENAME, std::ofstream::out | std::ofstream::app);


	m_levels[to_underlying(Loger_Levels::DEBUG_)] = "DEBUG";
	m_levels[to_underlying(Loger_Levels::INFO)] = "INFO";
	m_levels[to_underlying(Loger_Levels::ERROR)] = "ERROR";
	m_levels[to_underlying(Loger_Levels::WARNING)] = "WARNING";
	this->addLog("\n------------------------------NEW RUN-------------------------------\n========================================================================");
}
//-------------------------------------------------------------------------
Logger& Logger::getInstance()
{
	static Logger instance;
	return instance;
}
//-------------------------------------------------------------------------
Logger::~Logger()
{
	this->addLog("\n------------------------------END RUN-------------------------------\n========================================================================");
	m_logFile.close();
}
