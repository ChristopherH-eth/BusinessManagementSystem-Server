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
		bool success = false;

		// Make sure we have a valid database connection
		if (con->isValid())
			BMS_INFO("Successfully connected to the database!");
		else
		{
			BMS_ERROR("Couldn't connect to the database");

			return false;
		}

		// Make sure the employee table exists
		if (!eSQL.CheckEmployeeTable(con))
		{
			BMS_ERROR("Could not find or create 'employee' table in database.");

			return false;
		}

		// Get values from employee JSON object
		std::string firstName = employee["firstName"].dump();
		std::string lastName = employee["lastName"].dump();
		std::string birthDate = employee["birthDate"].dump();
		std::string position = employee["position"].dump();
		std::string salaryStr = employee["salary"].dump();
		std::string empIdStr = employee["empId"].dump();

		// Convert numeric values
		int empId = stoi(empIdStr);
		float salary = stof(salaryStr);

		// Calculate age
		int age = dateUtil.GetAge(birthDate);

		// Attempt to add employee to database
		success = eSQL.DBAddEmployee(con, empId, firstName, lastName, birthDate, age, position, salary);

		// Check if we successfully added an employee
		if (success)
		{
			BMS_INFO("Successfully added employee: {0} {1}", firstName, lastName);
			db.DisconnectDB(con);

			return true;
		}
		else
		{
			BMS_ERROR("Failed to add employee: {0} {1}", firstName, lastName);
			db.DisconnectDB(con);

			return false;
		}
	}

	/**
	* @brief The RemoveEmployee() function removes an employee from the database
	*/
	bool Employee::RemoveEmployee(nlohmann::json& employee)
	{
		Database db;
		EmployeeSQL eSQL;
		sql::Connection* con = db.ConnectDB();

		// Make sure we have a valid database connection
		if (con->isValid())
		{
			BMS_INFO("Successfully connected to the database!");
			db.DisconnectDB(con);
		}
		else
		{
			BMS_ERROR("Couldn't connect to the database");
			db.DisconnectDB(con);

			return false;
		}

		// Make sure the employee table exists
		if (!eSQL.CheckEmployeeTable(con))
		{
			BMS_ERROR("Could not find or create 'employee' table in database.");

			return false;
		}

		// TODO: process employee removal

		return true;
	}

	/**
	* @brief The UpdateEmployee() function removes an employee from the database
	*/
	bool Employee::UpdateEmployee(nlohmann::json& employee)
	{
		Database db;
		EmployeeSQL eSQL;
		sql::Connection* con = db.ConnectDB();

		// Make sure we have a valid database connection
		if (con->isValid())
		{
			BMS_INFO("Successfully connected to the database!");
			db.DisconnectDB(con);
		}
		else
		{
			BMS_ERROR("Couldn't connect to the database");
			db.DisconnectDB(con);

			return false;
		}

		// Make sure the employee table exists
		if (!eSQL.CheckEmployeeTable(con))
		{
			BMS_ERROR("Could not find or create 'employee' table in database.");

			return false;
		}

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
		bool success = false;

		// Make sure we have a valid database connection
		if (con->isValid())
		{
			BMS_INFO("Successfully connected to the database!");
			db.DisconnectDB(con);
		}
		else
		{
			BMS_ERROR("Couldn't connect to the database");
			db.DisconnectDB(con);

			return false;
		}

		// Make sure the employee table exists
		if (!eSQL.CheckEmployeeTable(con))
		{
			BMS_ERROR("Could not find or create 'employee' table in database.");

			return false;
		}

		// Get values from employee JSON object
		std::string firstName = employee["firstName"].dump();

		// Attempt to find employee in the database
		success = eSQL.DBEmpSearch(con, employee, firstName);

		// Check if we successfully found an employee
		if (success)
		{
			BMS_INFO("Successfully found employee: {0}", firstName);
			db.DisconnectDB(con);

			return true;
		}
		else
		{
			BMS_ERROR("Failed to find employee: {0}", firstName);
			db.DisconnectDB(con);

			return false;
		}
	}

}