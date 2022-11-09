#include "bmspch.h"

#include "EmployeeSQL.h"
#include "Log/Log.h"

/**
 * @file EmployeeSQL.cpp
 * @author 0xChristopher
 * @brief Source file for the EmployeeSQL class
 */

namespace BMS
{

	bool EmployeeSQL::CheckEmployeeTable(sql::Connection*& con)
	{
		sql::Statement* stmt;				// MySQL statement to be executed
		sql::ResultSet* res;				// MySQL result set
		con->setSchema("bms");				// Set schema we want to interact with
		stmt = con->createStatement();		// Define our query statement

		// Query strings
		std::string selectLimit = "SELECT * FROM employees LIMIT 1";
		std::string createTable = "CREATE TABLE `employees` (\
			`empId` INT NOT NULL,\
			`firstName` VARCHAR(45) NOT NULL,\
			`lastName` VARCHAR(45) NOT NULL,\
			`birthDate` VARCHAR(45) NOT NULL,\
			`age` INT NOT NULL,\
			`position` VARCHAR(45) NOT NULL,\
			`salary` FLOAT NOT NULL,\
			`username` VARCHAR(45) DEFAULT NULL,\
			`password` VARCHAR(45) DEFAULT NULL,\
			PRIMARY KEY(`empId`))";

		BMS_TRACE("Checking for 'employees' table in database...");

		try
		{
			res = stmt->executeQuery(selectLimit);

			// If the result set is not a nullptr, the table exists
			if (res != nullptr)
			{
				BMS_TRACE("'employees' database table exists");

				delete res;
				delete stmt;

				return true;
			}
		}
		catch (sql::SQLException& e) {
			BMS_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
			BMS_FILE_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_FILE_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
		}

		BMS_TRACE("'employees' table does not exist; creating table...");

		// Couldn't find table; try to create it
		try
		{
			bool tableCreated = stmt->execute(createTable);

			// execute() returns false when creating the table, so return true
			if (!tableCreated)
			{
				BMS_INFO("'employees' table successfully created");

				delete res;
				delete stmt;

				return true;
			}
			else
			{
				BMS_WARN("Could not create 'employees' table");

				delete res;
				delete stmt;

				return false;
			}
		}
		catch (sql::SQLException& e) {
			BMS_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
			BMS_FILE_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_FILE_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
		}
	}

	/**
	 * @brief The DBAddEmployee() function adds an employee to the MySQL database employees table.
	 */
	bool EmployeeSQL::DBAddEmployee(sql::Connection*& con, int empId, std::string& firstName, 
		std::string& lastName, std::string& birthDate, int age, std::string& position, float salary)
	{
		// Query string
		std::string addEmployee = "INSERT INTO employees(empId, firstName, lastName, birthDate, \
			age, position, salary) VALUES (?, ?, ?, ?, ?, ?, ?)";

		try 
		{
			sql::PreparedStatement* pstmt;		// MySQL prepared statement
			con->setSchema("bms");				// Set schema we want to interact with
		
			// Define our prepared statement
			pstmt = con->prepareStatement(addEmployee);

			// Set values for prepared statement
			pstmt->setInt(1, empId);
			pstmt->setString(2, firstName);
			pstmt->setString(3, lastName);
			pstmt->setString(4, birthDate);
			pstmt->setInt(5, age);
			pstmt->setString(6, position);
			pstmt->setDouble(7, salary);

			// Execute our prepared statement
			pstmt->executeQuery();

			delete pstmt;

			return true;
		}
		catch (sql::SQLException& e) {
			BMS_ERROR("# ERR: SQLException in {0} ({1}) on line {2}", 
				__FILE__, __FUNCTION__, __LINE__);
			BMS_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )", 
				e.what(), e.getErrorCode(), e.getSQLState());
			BMS_FILE_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_FILE_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
		}
	}

	/**
	 * @brief The DBEMPSearch() function search the database for employees based on their first name.
	 */
	bool EmployeeSQL::DBEmpSearch(sql::Connection*& con, nlohmann::json& employee, std::string& firstName)
	{
		// Query string
		std::string empSearch = "SELECT * FROM employees WHERE firstName = ?";

		try
		{
			nlohmann::json result;				// JSON object for search results
			sql::PreparedStatement* pstmt;		// MySQL prepared statement
			sql::ResultSet* res;				// Result set from query
			con->setSchema("bms");				// Set schema we want to interact with

			// Define our prepared statement
			pstmt = con->prepareStatement(empSearch);

			// Set values for prepared statement
			pstmt->setString(1, firstName);

			// Execute our prepared statement
			res = pstmt->executeQuery();
			res->beforeFirst();

			// Check for results
			if (res->next())
			{
				res->previous();

				// Prepare result set to be sent back to client
				while (res->next())
				{
					std::string resultStr = "{ \"firstName\": " + res->getString("firstName") + " }";

					employee = nlohmann::json::parse(resultStr);
				}
			}
			else
			{
				BMS_WARN("No results found for employee search");

				return false;
			}

			delete res;
			delete pstmt;

			return true;
		}
		catch (sql::SQLException& e) {
			BMS_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
			BMS_FILE_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_FILE_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
		}
	}

}