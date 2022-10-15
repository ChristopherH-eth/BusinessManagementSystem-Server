#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "../Core.h"

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
		static std::shared_ptr<spdlog::logger> s_Logger;

	public:
		/**
		 * @brief The GetLogger() function returns the current logger instance
		 */
		inline static std::shared_ptr<spdlog::logger>& GetLogger() 
		{ 
			return s_Logger; 
		}

		/**
		 * @brief The Init() function initializes the logger
		 */
		static void Init();

	};

}

// Logging macros
#define BMS_TRACE(...)	::BMS::Log::GetLogger()->trace(__VA_ARGS__)
#define BMS_INFO(...)	::BMS::Log::GetLogger()->info(__VA_ARGS__)
#define BMS_WARN(...)	::BMS::Log::GetLogger()->warn(__VA_ARGS__)
#define BMS_ERROR(...)	::BMS::Log::GetLogger()->error(__VA_ARGS__)
#define BMS_FATAL(...)	::BMS::Log::GetLogger()->fatal(__VA_ARGS__)