#pragma once

/**
 * @file Core.h
 * @author 0xChristopher
 */

#ifdef BMS_PLATFORM_WINDOWS
	#ifdef BMS_BUILD_DLL
		#define BMS_API __declspec(dllexport)
	#else
		#define BMS_API __declspec(dllimport)
#endif
#else
	#error BMS only supports Windows
#endif