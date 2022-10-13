#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "../Core.h"

/**
 * @file Employee.h
 * @author 0xChristopher
 * @brief 
 */

namespace BMS 
{

	class BMS_API Employee 
	{

	private:
		std::string m_firstName, m_lastName, m_birthDate, m_position;
		int m_age, m_id;
		float m_salary;

	public:
		/**
		 * @brief Employee constructor and destructor
		 */
		Employee(std::string& firstName, std::string& lastName, std::string& birthDate, std::string& position,
			float salary, int age, int id);

		~Employee();

		/**
		 * @brief The AddEmployee() function adds an employee to the database
		 * @param employee The JSON object representing an employee
		 * @return Returns true upon successfully adding the employee
		 */
		bool static AddEmployee(nlohmann::json employee);

		/**
		 * @brief The RemoveEmployee() function removes an employee from the database
		 * @param id The employee's id number
		 * @return Returns true upon successfully removing the employee
		 */
		bool static RemoveEmployee(int id);

		/**
		 * @brief The UpdateEmployee() function adds an employee to the database
		 * @param employee The JSON object representing an employee
		 * @return Returns true upon successfully adding the employee
		 */
		bool static UpdateEmployee(nlohmann::json employee);

	};

}