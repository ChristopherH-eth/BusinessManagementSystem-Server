#include "bmspch.h"

#include "Networking/TcpListener.h"
#include "Networking/Handler.h"
#include "Log/Log.h"

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
	BMS::Handler msgHandler;
	std::string response;

	BMS_TRACE("Client message: {0}", msg);

	// Send response to the client application
	response = msgHandler.DirectInput(msg);
	listener->Send(client, response);
}

void main()
{
	// Create directory for log files
	const char* dirname = "./logs";
	std::filesystem::create_directory(dirname);

	std::string host = "127.0.0.1";			// Server ip address
	int port = 54000;						// Server port

	BMS::Log::Init();						// Initialize logger

	BMS_TRACE("Welcome to Business Management System v1.0.0\n");
	BMS_FILE_TRACE("Welcome to Business Management System v1.0.0\n");

	// Spin up a new server instance
	TcpListener server(host, port, ListenerMessageReceived);

	if (server.Init())
		server.Run();
}