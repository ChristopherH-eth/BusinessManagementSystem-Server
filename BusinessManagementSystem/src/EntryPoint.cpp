#include <iostream>
#include <WS2tcpip.h>

#include "./Networking/TcpListener.h"

#pragma comment (lib, "ws2_32.lib")

/**
 * @file EntryPoint.cpp
 * @author 0xChristopher
 */

/**
 * @brief The ListenerMessageReceived function echos the client's message
 */
void ListenerMessageReceived(TcpListener* listener, int client, std::string msg)
{
	std::cout << "\nClient message: " << msg << std::endl;

	enum input
	{
		addEployee = 100,
		removeEmployee = 101
	};

	std::string inputStr = msg.substr(0, 3);
	int input = stoi(inputStr);

	std::cout << "Function: " << input << "\n" << std::endl;

	switch (input)
	{
	case 100:
		std::cout << "Called addEmployee() function" << std::endl;
		listener->Send(client, "addEmployee function called");
		break;
	case 101:
		std::cout << "Called removeEmployee() function" << std::endl;
		listener->Send(client, "removeEmployee function called");
		break;
	default:
		std::cout << "No function called" << std::endl;
		listener->Send(client, "No function called");
		break;
	}

	listener->Send(client, msg);
}

void main()
{
	std::cout << "Welcome to Business Management System v1.0.0\n" << std::endl;

	TcpListener server("127.0.0.1", 54000, ListenerMessageReceived);

	if (server.Init())
		server.Run();
}