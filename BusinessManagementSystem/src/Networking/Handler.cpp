#include <iostream>
#include <string>

#include "Handler.h"

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
	std::string response;

	enum inputFunction
	{
		addEployee = 100,
		removeEmployee = 101,
		updateEmployee = 102
	};

	std::string inputStr = msg.substr(0, 3);

	int input = stoi(inputStr);

	std::cout << "Function: " << input << "\n" << std::endl;

	switch (input)
	{
	case 100:
		std::cout << "Called addEmployee() function" << std::endl;
		response = "addEmployee function called";
		break;
	case 101:
		std::cout << "Called removeEmployee() function" << std::endl;
		response = "removeEmployee function called";
		break;
	case 102:
		std::cout << "Called updateEmployee() function" << std::endl;
		response = "updateEmployee function called";
		break;
	default:
		std::cout << "No function called" << std::endl;
		response = "No function called";
		break;
	}

	return response;
}