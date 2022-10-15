#include <spdlog/sinks/stdout_color_sinks.h>
#include "Log.h"

/**
 * @file Log.cpp
 * @author 0xChristopher
 * @brief Source file for the Log class
 */

namespace BMS
{

	std::shared_ptr<spdlog::logger> Log::s_Logger;

	/**
	 * @brief The Init() function initializes the logger
	 */
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n:%v%$");

		s_Logger = spdlog::stdout_color_mt("BMS");
		s_Logger->set_level(spdlog::level::trace);
	}

}