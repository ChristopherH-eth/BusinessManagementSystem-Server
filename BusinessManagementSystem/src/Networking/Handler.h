#pragma once

#include <string>

/**
 * @file Handler.h
 * @author 0xChristopher
 * @brief The Handler class is responsible for taking incoming requests from clients via the TcpListener,
 *		and directs those requests to the appropriate module for processing. An example of this would be
 *		employee salary changes provided by the HR manager that need to be updated in the employee database
 *		table, so that payroll and compensation lookups return accurate data.
 */

class Handler
{

public:
	/**
	 * @brief Handler constructor and destructor
	 */
	Handler();

	~Handler();

	/**
	 * @brief The DirectInput() function directs client input to the appropriate part of the
	 * application for interaction based on the function id.
	 * @param msg The client input to be directed
	 */
	std::string DirectInput(std::string msg);

};