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
	std::cout << "\nClient message: " << msg << "\n" << std::endl;

	listener->Send(client, msg);
}

void main()
{
	std::cout << "Welcome to Business Management System v1.0.0\n" << std::endl;

	TcpListener server("127.0.0.1", 54000, ListenerMessageReceived);

	if (server.Init())
		server.Run();
}