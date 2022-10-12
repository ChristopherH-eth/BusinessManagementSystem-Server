#pragma once

#include <string>

/**
 * @file Handler.h
 * @author 0xChristopher
 * @brief
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