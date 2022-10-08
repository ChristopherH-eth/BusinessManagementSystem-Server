#include <iostream>
#include <string>
#include <WS2tcpip.h>

#include "TcpListener.h"

#pragma comment (lib, "ws2_32.lib")

/**
 * @file TcpListener.cpp
 * @author 0xChristopher
 */

/**
* @brief TcpListener constructor and destructor
*/
TcpListener::TcpListener(std::string ipAddress, int port, MessageReceivedHandler handler) 
	: m_ipAddress(ipAddress), m_port(port), m_handler(handler)
{

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
	std::cout << "Initializing WinSock..." << std::endl;

	WSAData data;
	WORD ver = MAKEWORD(2, 2);

	int wsInit = WSAStartup(ver, &data);

	if (wsInit != 0)
	{
		std::cerr << "Can't initialize winsock. Exiting program..." << std::endl;
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
	std::cout << "\nServer startup successful!\n" << std::endl;

	char buf[MAX_BUFFER_SIZE];

	while (true)
	{
		/// Create listening socket
		SOCKET listening = CreateSocket();

		if (listening == INVALID_SOCKET)
			break;

		/// Listen for client connection
		SOCKET client = WaitForConnection(listening);

		if (client != INVALID_SOCKET)
		{
			/// Stop listening if we have a connection
			closesocket(listening);
			int bytesReceived = 0;

			do
			{
				ZeroMemory(buf, MAX_BUFFER_SIZE);
				/// Wait for client to send data
				bytesReceived = recv(client, buf, MAX_BUFFER_SIZE, 0);

				if (bytesReceived > 0)
				{
					/// Handle incoming message
					if (m_handler != nullptr)
					{
						std::cout << "Client connected" << std::endl;

						m_handler(this, client, std::string(buf, 0, bytesReceived));
					}
				}
			} 
			while (bytesReceived > 0);
		}

		/// Disconnect from client
		closesocket(client);
	}
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

	if (listening != INVALID_SOCKET)
	{
		/// Bind ip address and port to socket
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(m_port);
		inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);

		std::cout << "Binding ip address and port..." << std::endl;

		int bindOk = bind(listening, (sockaddr*)&hint, sizeof(hint));

		if (bindOk != SOCKET_ERROR)
		{
			/// Listen with the newly created socket
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
	std::cout << "\nWaiting for client connection..." << std::endl;

	SOCKET client = accept(listening, nullptr, nullptr);

	return client;
}