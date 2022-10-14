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

	// Send response to the client application
	response = msgHandler.DirectInput(msg);
	listener->Send(client, response);
}

void main()
{
	std::string host = "127.0.0.1";			// Server ip address
	int port = 54000;						// Server port

	std::cout << "Welcome to Business Management System v1.0.0\n" << std::endl;

	// Spin up a new server instance
	TcpListener server(host, port, ListenerMessageReceived);

	if (server.Init())
		server.Run();
}