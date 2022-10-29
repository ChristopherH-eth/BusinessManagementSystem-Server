#pragma once

#include "bmspch.h"

/**
 * @file Employee.h
 * @author 0xChristopher
 * @brief The Employee class allows the creation of employee objects and calls to related functions. It is
 *		part of the BMS_API.
 */

namespace BMS 
{

	class BMS_API Employee 
	{

	private:
		std::string m_firstName;		// Employee first name
		std::string m_lastName;			// Employee last name
		std::string m_birthDate;		// Employee DOB
		std::string m_position;			// Current employee position
		int m_age;						// Employee age
		int m_id;						// Unique employee id
		float m_salary;					// Employee salary

	public:
		/**
		 * @brief Employee constructor and destructor
		 * @param firstName The employee's first name
		 * @param lastName The employee's last name
		 * @param birthDate The employee's DOB
		 * @param position The employee's current position
		 * @param salary The employee's salary
		 * @param age The employee's age
		 * @param id The employee's unique id
		 */
		Employee(std::string& firstName, std::string& lastName, std::string& birthDate, 
			std::string& position, float salary, int age, int id);

		~Employee();

		/**
		 * @brief The AddEmployee() function adds an employee to the database
		 * @param employee The JSON object representing an employee
		 * @return Returns true upon successfully adding the employee
		 */
		bool static AddEmployee(nlohmann::json& employee);

		/**
		 * @brief The RemoveEmployee() function removes an employee from the database
		 * @param id The employee's id number
		 * @return Returns true upon successfully removing the employee
		 */
		bool static RemoveEmployee(nlohmann::json& employee);

		/**
		 * @brief The UpdateEmployee() function adds an employee to the database
		 * @param employee The JSON object representing an employee
		 * @return Returns true upon successfully adding the employee
		 */
		bool static UpdateEmployee(nlohmann::json& employee);

	};

}