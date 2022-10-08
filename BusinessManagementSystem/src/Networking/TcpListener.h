#pragma once

#include <string>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE (49152)

/**
 * @file TcpListener.h
 * @author 0xChristopher
 */

/// TcpListener class forward declaration
class TcpListener;

/// Callback to data received
typedef void(*MessageReceivedHandler)(TcpListener* listener, int socketId, std::string msg);

class TcpListener
{

private:
	std::string m_ipAddress;
	int m_port;
	MessageReceivedHandler m_handler;

	/**
	 * @brief The CreateSocket() function creates a socket
	 */
	SOCKET CreateSocket();

	/**
	 * @brief The WaitForConnection() function waits for a client connection
	 */
	SOCKET WaitForConnection(SOCKET listening);

public:
	/**
	 * @brief TcpListener constructor and destructor
	 */
	TcpListener(std::string ipAddress, int port, MessageReceivedHandler handler);

	~TcpListener();

	/**
	 * @brief The Send() function sends a message back to the client
	 */
	void Send(int clientSocket, std::string msg);

	/**
	 * @brief The Init() function initializes Winsock
	 */
	bool Init();

	/**
	 * @brief The Run() function represents the main loop
	 */
	void Run();

	/**
	 * @brief The Cleanup() function cleans up the program upon exit
	 */
	void Cleanup();

};