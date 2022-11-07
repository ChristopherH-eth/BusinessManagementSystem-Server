#pragma once

#include "bmspch.h"

/**
 * @file EmployeeSQL.h
 * @author 0xChristopher
 * @brief The EmployeeSQL class handles the addition, removal, and manipulation of employee data within
 *		the MySQL database employees table.
 */

namespace BMS
{

	class BMS_API EmployeeSQL
	{

	public:
		bool CheckEmployeeTable(sql::Connection*& con);

		/**
		 * @brief The DBEMPSearch() function search the database for employees based on their first name.
		 * @param con The current database connection
		 * @param firstName The first name of the employee being searched for
		 */
		bool DBEmpSearch(sql::Connection*& con, nlohmann::json& employee, std::string& firstName);

		/**
		 * @brief The DBAddEmployee() function adds an employee to the MySQL database employees table.
		 * @param con The current database connection
		 * @param empId Unique employee ID
		 * @param firstName The employee's first name
		 * @param lastName The employee's last name
		 * @param birthDate The employee's birth date
		 * @param age The age of the employee
		 * @param position The employee's position
		 * @param salary The employee's yearly salary
		 */
		bool DBAddEmployee(sql::Connection*& con, int empId, std::string& firstName, std::string& lastName, 
			std::string& birthDate, int age, std::string& position, float salary);

	};

}