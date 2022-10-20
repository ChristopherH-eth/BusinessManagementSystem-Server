#include "bmspch.h"

#include "Handler.h"
#include "HR/Employee.h"
#include "Log/Log.h"

/**
 * @file Handler.cpp
 * @author 0xChristopher
 * @brief Source file for the Handler class
 */

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
std::string Handler::DirectInput(std::string msg)
{
	bool success;
	std::string response;
	nlohmann::json newJson;

	enum inputFunction
	{
		addEployee = 100,
		removeEmployee = 101,
		updateEmployee = 102
	};

	std::string inputStr = msg.substr(0, 3);
	std::string getJson = msg.substr(4);

	int input = stoi(inputStr);
	newJson = nlohmann::json::parse(getJson);

	BMS_TRACE("Function: {0}\n", input);

	switch (input)
	{
	case 100:
		BMS_TRACE("Called addEmployee() function");
		BMS_TRACE("Generated JSON object: {0}", getJson);

		success = BMS::Employee::AddEmployee(newJson);

		// Check if employee was added successfully
		if (success)
			BMS_INFO("Employee added!");
		else
			BMS_ERROR("Failed to add employee");

		response = "addEmployee function called";
		break;
	case 101:
		BMS_TRACE("Called removeEmployee() function");
		BMS_TRACE("Generated JSON object: {0}", getJson);
		response = "removeEmployee function called";
		break;
	case 102:
		BMS_TRACE("Called updateEmployee() function");
		BMS_TRACE("Generated JSON object: {0}", getJson);

		success = BMS::Employee::UpdateEmployee(newJson);

		// Check if employee was updated successfully
		if (success)
			BMS_INFO("Employee added!");
		else
			BMS_ERROR("Failed to add employee");

		response = "updateEmployee function called";
		break;
	default:
		BMS_TRACE("No function called");
		response = "No function called";
		break;
	}

	return response;
}