#include <iostream>
#include "Employee.h"
#include "../Networking/Database.h"
#include "../Log/Log.h"

/**
 * @file Employee.cpp
 * @author 0xChristopher
 * @brief Source file for the Employee class
 */

namespace BMS
{

	/**
	* @brief Employee constructor and destructor
	*/
	Employee::Employee(std::string& firstName, std::string& lastName, std::string& birthDate, std::string& position,
		float salary, int age, int id)
		: m_firstName(firstName), m_lastName(lastName), m_birthDate(birthDate), m_position(position),
		m_salary(salary), m_age(age), m_id(id)
	{

	}

	Employee::~Employee()
	{

	}

	/**
	* @brief The AddEmployee() function adds an employee to the database
	*/
	bool Employee::AddEmployee(nlohmann::json employee)
	{
		Database db;
		sql::Connection* con = db.ConnectDB();

		// Make sure we have a valid database connection
		if (db.ConnectDB())
			BMS_INFO("Successfully connected to the database!");
		else
			BMS_ERROR("Couldn't connect to the database");

		// TODO: process employee details

		return true;
	}

	/**
	* @brief The RemoveEmployee() function removes an employee from the database
	*/
	bool Employee::RemoveEmployee(int id) 
	{
		// TODO: process employee removal

		return true;
	}

	/**
	* @brief The UpdateEmployee() function removes an employee from the database
	*/
	bool Employee::UpdateEmployee(nlohmann::json employee)
	{
		// TODO: process employee update

		return true;
	}
}