#pragma once

#include "bmspch.h"

/**
 * @file DateUtil.h
 * @author 0xChristopher
 * @brief The DateUtil class provides functions by which dates can be manipulated for things such as
 *		calculating the age of employees.
 */

namespace BMS
{

	class BMS_API DateUtil
	{

	public:
		/**
		 * @brief DateUtil constructor and destructor
		 */
		DateUtil();

		~DateUtil();

		/**
		 * @brief The GetAge() function calculates an employee or user's age.
		 * @param strDate The string representation of an employee or user's birth date
		 * @return Returns the age of the employee or user
		 */
		int GetAge(std::string& strDate);

		/**
		 * @brief The GetDate() function calculates and returns the current date (using UTC time zone).
		 */
		std::tm GetCurrentDate();

	};

}