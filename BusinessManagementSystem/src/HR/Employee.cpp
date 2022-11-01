#include "bmspch.h"

#include "Employee.h"
#include "Networking/Database.h"
#include "Log/Log.h"
#include "Util/DateUtil.h"
#include "Queries/HR/EmployeeSQL.h"

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
	Employee::Employee(std::string& firstName, std::string& lastName, std::string& birthDate, 
		std::string& position, float salary, int age, int id)
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
	bool Employee::AddEmployee(nlohmann::json& employee)
	{
		Database db;
		DateUtil dateUtil;
		EmployeeSQL eSQL;
		sql::Connection* con = db.ConnectDB();

		// Make sure we have a valid database connection
		if (con->isValid())
			BMS_INFO("Successfully connected to the database!");
		else
			BMS_ERROR("Couldn't connect to the database");

		// Get values from employee JSON object
		std::string firstName = employee["firstName"].dump();
		std::string lastName = employee["lastName"].dump();
		std::string birthDate = employee["birthDate"].dump();
		std::string position = employee["position"].dump();
		std::string salary = employee["salary"].dump();
		std::string empId = employee["empId"].dump();

		// Calculate age
		int age = dateUtil.GetAge(birthDate);

		eSQL.DBAddEmployee(con, 0, firstName, lastName, birthDate, age, position, 0.0f);

		return true;
	}

	/**
	* @brief The RemoveEmployee() function removes an employee from the database
	*/
	bool Employee::RemoveEmployee(nlohmann::json& employee)
	{
		Database db;
		sql::Connection* con = db.ConnectDB();

		// Make sure we have a valid database connection
		if (con->isValid())
			BMS_INFO("Successfully connected to the database!");
		else
			BMS_ERROR("Couldn't connect to the database");

		// TODO: process employee removal

		return true;
	}

	/**
	* @brief The UpdateEmployee() function removes an employee from the database
	*/
	bool Employee::UpdateEmployee(nlohmann::json& employee)
	{
		Database db;
		sql::Connection* con = db.ConnectDB();

		// Make sure we have a valid database connection
		if (con->isValid())
			BMS_INFO("Successfully connected to the database!");
		else
			BMS_ERROR("Couldn't connect to the database");

		// TODO: process employee update

		return true;
	}

	/**
	* @brief The SearchEmployees() function removes an employee from the database
	*/
	bool Employee::SearchEmployees(nlohmann::json& employee)
	{
		Database db;
		EmployeeSQL eSQL;
		sql::Connection* con = db.ConnectDB();

		// Make sure we have a valid database connection
		if (con->isValid())
			BMS_INFO("Successfully connected to the database!");
		else
			BMS_ERROR("Couldn't connect to the database");

		// Get values from employee JSON object
		std::string firstName = employee["firstName"].dump();

		employee = eSQL.DBEmpSearch(con, firstName);

		return true;
	}
}