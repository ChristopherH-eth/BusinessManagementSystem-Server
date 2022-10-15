#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "Log.h"

/**
 * @file Log.cpp
 * @author 0xChristopher
 * @brief Source file for the Log class
 */

namespace BMS
{

	std::shared_ptr<spdlog::logger> Log::s_Logger;			// Main logger
	std::shared_ptr<spdlog::logger> Log::s_DailyLogger;		// File logger

	/**
	 * @brief The Init() function initializes the loggers
	 */
	void Log::Init()
	{
		try
		{
			spdlog::set_pattern("%^[%c] %n:%v%$");
			spdlog::flush_every(std::chrono::seconds(3));

			s_Logger = spdlog::stdout_color_mt("BMS_MAIN");
			s_Logger->set_level(spdlog::level::trace);

			s_DailyLogger = spdlog::basic_logger_mt("BMS_FILE", "./logs/log.txt");
			s_DailyLogger->set_level(spdlog::level::trace);
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log initialization failed: " << ex.what() << std::endl;
		}
	}

}