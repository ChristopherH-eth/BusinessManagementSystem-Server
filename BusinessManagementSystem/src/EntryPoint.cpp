#include <iostream>
#include <WS2tcpip.h>

#include "./Networking/TcpListener.h"
#include "./Networking/Handler.h"

#pragma comment (lib, "ws2_32.lib")

/**
 * @file EntryPoint.cpp
 * @author 0xChristopher
 * @brief This is the entry point for the Business Management System server side application.
 */

/**
 * @brief The ListenerMessageReceived function handles the client's message
 */
void ListenerMessageReceived(TcpListener* listener, int client, std::string msg)
{
	Handler msgHandler;
	std::string response;

	std::cout << "\nClient message: " << msg << std::endl;

	response = msgHandler.DirectInput(msg);
	listener->Send(client, response);
}

void main()
{
	std::cout << "Welcome to Business Management System v1.0.0\n" << std::endl;

	TcpListener server("127.0.0.1", 54000, ListenerMessageReceived);

	if (server.Init())
		server.Run();
}