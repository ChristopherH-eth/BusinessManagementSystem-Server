#pragma once

#include "bmspch.h"

/**
 * @file Log.h
 * @author 0xChristopher
 * @brief 
 */

namespace BMS
{

	class BMS_API Log
	{
		
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;			// Main logger
		static std::shared_ptr<spdlog::logger> s_DailyLogger;		// File logger

	public:
		/**
		 * @brief The GetLogger() function returns the current logger instance
		 */
		inline static std::shared_ptr<spdlog::logger>& GetLogger() 
		{ 
			return s_Logger; 
		}

		/**
		 * @brief The GetFileLogger() function returns the current file logger instance
		 */
		inline static std::shared_ptr<spdlog::logger>& GetFileLogger()
		{
			return s_DailyLogger;
		}

		/**
		 * @brief The Init() function initializes the loggers
		 */
		static void Init();

	};

}

// Main logger macros
#define BMS_TRACE(...)	::BMS::Log::GetLogger()->trace(__VA_ARGS__)
#define BMS_INFO(...)	::BMS::Log::GetLogger()->info(__VA_ARGS__)
#define BMS_WARN(...)	::BMS::Log::GetLogger()->warn(__VA_ARGS__)
#define BMS_ERROR(...)	::BMS::Log::GetLogger()->error(__VA_ARGS__)
#define BMS_FATAL(...)	::BMS::Log::GetLogger()->fatal(__VA_ARGS__)

// File logger macros
#define BMS_DAILY_TRACE(...)	::BMS::Log::GetFileLogger()->trace(__VA_ARGS__)
#define BMS_DAILY_INFO(...)		::BMS::Log::GetFileLogger()->info(__VA_ARGS__)
#define BMS_DAILY_WARN(...)		::BMS::Log::GetFileLogger()->warn(__VA_ARGS__)
#define BMS_DAILY_ERROR(...)	::BMS::Log::GetFileLogger()->error(__VA_ARGS__)
#define BMS_DAILY_FATAL(...)	::BMS::Log::GetFileLogger()->fatal(__VA_ARGS__)