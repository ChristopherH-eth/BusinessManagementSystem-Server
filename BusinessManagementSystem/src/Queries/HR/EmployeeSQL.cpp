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

	void EmployeeSQL::DBEmpSearch(sql::Connection*& con, std::string firstName)
	{
		try
		{
			sql::PreparedStatement* pstmt;		// MySQL prepared statement
			sql::ResultSet* res;				// Result set from query
			con->setSchema("bms");				// Set schema we want to interact with

			// Define our prepared statement
			pstmt = con->prepareStatement("SELECT * FROM employees WHERE firstName = ?");

			// Set values for prepared statement
			pstmt->setString(1, firstName);

			// Execute our prepared statement
			res = pstmt->executeQuery();
			res->beforeFirst();

			while (res->next())
			{
				// TODO: Set employees to JSON objects to send back to client
			}

			delete res;
			delete pstmt;
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
	void EmployeeSQL::DBAddEmployee(sql::Connection*& con, int empId, std::string& firstName, 
		std::string& lastName, std::string& birthDate, int age, std::string& position, float salary)
	{
		try 
		{
			sql::PreparedStatement* pstmt;		// MySQL prepared statement
			con->setSchema("bms");				// Set schema we want to interact with
		
			// Define our prepared statement
			pstmt = con->prepareStatement("INSERT INTO employees(empId, firstName, lastName, birthDate, \
											age, position, salary) VALUES (?, ?, ?, ?, ?, ?, ?)");

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

	// TODO: Check table exists
	//CREATE TABLE `bms`.`employees` (
	//	`empId` INT NOT NULL,
	//	`firstName` VARCHAR(45) NOT NULL,
	//	`lastName` VARCHAR(45) NOT NULL,
	//	`birthDate` VARCHAR(45) NOT NULL,
	//	`age` INT NOT NULL,
	//	`position` VARCHAR(45) NOT NULL,
	//	`salary` FLOAT NOT NULL,
	//	PRIMARY KEY(`empId`));

}