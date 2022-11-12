#include "bmspch.h"

#include "Handler.h"
#include "HR/Employee.h"
#include "Log/Log.h"

/**
 * @file Handler.cpp
 * @author 0xChristopher
 * @brief Source file for the Handler class
 */

namespace BMS
{

	/**
	 * @brief Handler constructor and destructor
	 */
	Handler::Handler()
	{

	}

	Handler::~Handler()
	{

	}

	/**
	* @brief The DirectInput() function directs client input to the appropriate part of the
	* application for interaction based on the function id.
	*/
	std::string Handler::DirectInput(std::string& msg)
	{
		bool success = false;						// True upon successful database interaction
		std::string response;						// Response to client side application
		nlohmann::json newJson;						// JSON object derived from getJson substring

		// Enum of function ids received from client side application
		enum inputFunction
		{
			login = 100,							// User login
			logout = 101,							// User logout
			addEmployee = 102,						// Add a new employee to database
			removeEmployee = 103,					// Remove employee from database
			updateEmployee = 104,					// Update a current employee
			searchEmployees = 105					// Search through current employees
		};

		std::string inputStr = msg.substr(0, 3);	// Substring containing the function id
		std::string getJson = msg.substr(4);		// Substring containing the JSON object

		int input = stoi(inputStr);					// Convert the function id to an int
		newJson = nlohmann::json::parse(getJson);	// Parse JSON object from JSON string

		BMS_TRACE("Function Id: {0}", input);

		switch (input)
		{
		case login:
			BMS_INFO("Logged in");

			// TODO: Log users in

			response = "Login successful";
			break;

		case logout:
			BMS_INFO("Logged out");

			// TODO: Log users out

			response = "Logout successful";
			break;

		case addEmployee:
			BMS_TRACE("Called addEmployee() function");
			BMS_TRACE("Generated JSON object: {0}", getJson);

			success = Employee::AddEmployee(newJson);
			
			// Check if employee was added successfully
			if (success)
				response = "addEmployee function successfully called";
			else
				response = "Failed to add employee";
			break;

		case removeEmployee:
			BMS_TRACE("Called removeEmployee() function");
			BMS_TRACE("Generated JSON object: {0}", getJson);

			success = Employee::RemoveEmployee(newJson);

			// Check if employee was removed successfully
			if (success)
				BMS_INFO("Employee removed!");
			else
				BMS_ERROR("Failed to remove employee");

			response = "removeEmployee function successfully called";
			break;

		case updateEmployee:
			BMS_TRACE("Called updateEmployee() function");
			BMS_TRACE("Generated JSON object: {0}", getJson);

			success = Employee::UpdateEmployee(newJson);

			// Check if employee was updated successfully
			if (success)
				BMS_INFO("Employee updated!");
			else
				BMS_ERROR("Failed to update employee");

			response = "updateEmployee function successfully called";
			break;

		case searchEmployees:
			BMS_TRACE("Called searchEmployees() function");

			success = Employee::SearchEmployees(newJson);

			// Check if employee was found successfully
			if (success)
				response = newJson.dump();
			else
				response = "Employee not found";
			break;

		default:
			BMS_TRACE("No function called");
			response = "No function called";
			break;
		}

		return response;
	}

}