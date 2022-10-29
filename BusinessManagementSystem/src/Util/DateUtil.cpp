#include "bmspch.h"

#include "DateUtil.h"
#include "Log/Log.h"

/**
 * @file DateUtil.cpp
 * @author 0xChristopher
 * @brief Source file for the DateUtil class
 */

namespace BMS
{

	/**
	 * @brief DateUtil constructor and destructor
	 */
	DateUtil::DateUtil()
	{

	}

	DateUtil::~DateUtil()
	{

	}

	/**
	 * @brief The GetAge() function calculates an employee or user's age.
	 */
	int DateUtil::GetAge(std::string& strDate) {

		struct std::tm dt = { 0 };					// Struct for birth date/time
		std::tm currentDate = GetCurrentDate();		// Current date in UTC time zone

		// Get substrings for day, month, and year
		std::size_t lenMonth = strDate.find("/");
		std::string month = strDate.substr(1, lenMonth);
		std::string postMonth = strDate.substr(lenMonth + 1);
		std::size_t lenDay = postMonth.find("/");
		std::string day = postMonth.substr(0, lenDay);
		std::string year = postMonth.substr(lenDay + 1);

		// Convert day, month, and year substrings to ints to calculate age
		int intYear = stoi(year);
		int intMonth = stoi(month);
		int intDay = stoi(day);

		// Get birth date in date format
		dt.tm_year = (intYear - 1900);
		dt.tm_mon = (intMonth - 1);
		dt.tm_mday = intDay;

		// Calculate age
		int age = (currentDate.tm_year - dt.tm_year);

		// Check whether the birthday has passed this year or not
		if (dt.tm_mon < currentDate.tm_mon)
			return age;
		else if (dt.tm_mon == currentDate.tm_mon)
			if (dt.tm_mday <= currentDate.tm_mday)
				return age;
			else
				return age - 1;
		else
			return age - 1;
	}

	/**
	 * @brief The GetDate() function calculates and returns the current date (using UTC time zone).
	 */
	std::tm DateUtil::GetCurrentDate()
	{
		struct std::tm current;				// Struct for current date/time
		std::time_t currentTime;			// Used to get current UTC time

		// Get current date
		time(&currentTime);
		current = *gmtime(&currentTime);

		return current;
	}

}