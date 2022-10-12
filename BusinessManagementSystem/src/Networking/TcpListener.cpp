#include <iostream>
#include <string>
#include <WS2tcpip.h>

#include "TcpListener.h"

#pragma comment (lib, "ws2_32.lib")

/**
 * @file TcpListener.cpp
 * @author 0xChristopher
 * @brief Source file for the TcpListener class
 */

/**
* @brief TcpListener constructor and destructor
*/
TcpListener::TcpListener(std::string ipAddress, int port, MessageReceivedHandler handler) 
	: m_ipAddress(ipAddress), m_port(port), m_handler(handler)
{
	// m_running set to false until successful server startup
	this->m_running = false;
}

TcpListener::~TcpListener()
{
	Cleanup();
}

/**
 * @brief The Send() function sends a message back to the client
 */
void TcpListener::Send(int clientSocket, std::string msg)
{
	send(clientSocket, msg.c_str(), msg.size() + 1, 0);
}

/**
 * @brief The Init() function initializes Winsock
 */
bool TcpListener::Init() 
{
	std::cout << "Initializing WinSock... ";

	WSAData data;
	WORD ver = MAKEWORD(2, 2);

	int wsInit = WSAStartup(ver, &data);

	// Check if WinSock was successfully initialized
	if (wsInit != 0)
	{
		std::cerr << "\nCan't initialize winsock. Exiting program..." << std::endl;

		return false;
	}

	std::cout << "WinSock initialized" << std::endl;

	return true;
}

/**
 * @brief The Run() function represents the main loop
 */
void TcpListener::Run()
{
	// Create listening socket
	SOCKET listening = CreateSocket();

	// Check if listening socket was created successfully
	if (listening == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket. Exitting program..." << std::endl;
		return;
	}

	std::cout << "\nServer startup successful!\n" << std::endl;

	// Set running to 'true' on successful startup
	m_running = true;

	// Initialize our master file descriptor set
	fd_set master;
	FD_ZERO(&master);
	FD_SET(listening, &master);

	// Max buffer for messages
	char buf[MAX_BUFFER_SIZE];

	// Main running loop
	while (m_running)
	{
		// Copy our master file descriptor set to work with
		fd_set copy = master;
		
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		// Iterate through available sockets
		for (int i = 0; i < socketCount; i++)
		{
			SOCKET s = copy.fd_array[i];

			// Make sure we're using a valid socket
			if (s != INVALID_SOCKET)
			{
				// Check if the current socket is listening
				if (s == listening)
				{
					// Listen for client connection and add connection to list of connected clients
					SOCKET client = WaitForConnection(listening);
					FD_SET(client, &master);

					std::cout << "Client connected" << std::endl;

					// Send welcome message to connected client
					std::string welcomeMsg = "Connected to Business Management Server!";
					Send(client, welcomeMsg);
				}
				else
				{
					int bytesReceived = 0;

					ZeroMemory(buf, MAX_BUFFER_SIZE);

					// Wait for client to send data
					bytesReceived = recv(s, buf, MAX_BUFFER_SIZE, 0);

					// Check if we've received a command
					if (buf[0] == 'e')
					{
						std::string input = std::string(buf, bytesReceived);

						// Check if client is disconnecting
						if (input == "exit")
						{
							// Disconnect from client and remove from list of connected clients
							closesocket(s);
							FD_CLR(s, &master);

							std::cout << "Client disconnected" << std::endl;
						}
					}
					else if (bytesReceived > 0)
					{
						// Handle incoming message
						if (m_handler != nullptr)
							m_handler(this, s, std::string(buf, 0, bytesReceived));
					}
				}
			}
		}
	}
	
	// Remove listening socket to prevent further connections
	FD_CLR(listening, &master);	
	closesocket(listening);	

	// Close sockets and shutdown the server
	while (master.fd_count > 0)
	{
		SOCKET s = master.fd_array[0];
		FD_CLR(s, &master);
		closesocket(s);
	}

	Cleanup();
	system("pause");
}

/**
 * @brief The Cleanup() function cleans up the program upon exit
 */
void TcpListener::Cleanup()
{
	std::cout << "Cleaning up server instance..." << std::endl;

	WSACleanup();
}

/**
* @brief The CreateSocket() function creates a socket
*/
SOCKET TcpListener::CreateSocket()
{
	std::cout << "Creating listening socket..." << std::endl;

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

	// Make sure our listening socket is valid
	if (listening != INVALID_SOCKET)
	{
		// Bind ip address and port to socket
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(m_port);
		inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);

		std::cout << "Binding ip address and port... ";

		int bindOk = bind(listening, (sockaddr*)&hint, sizeof(hint));

		if (bindOk != SOCKET_ERROR)
		{
			// Listen with the newly created socket
			int listenOk = listen(listening, SOMAXCONN);

			if (listenOk == SOCKET_ERROR)
				return -1;
		}
		else
		{
			return -1;
		}
	}

	std::cout << "Socket creation and binding successful" << std::endl;

	return listening;
}

/**
 * @brief The WaitForConnection() function waits for a client connection
 */
SOCKET TcpListener::WaitForConnection(SOCKET listening)
{
	std::cout << "\nWaiting for client connection...\n" << std::endl;

	SOCKET client = accept(listening, nullptr, nullptr);

	return client;
}