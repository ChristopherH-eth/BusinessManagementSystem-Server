#pragma once

#include <string>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE (49152)		// Max buffer for receiving client requests

/**
 * @file TcpListener.h
 * @author 0xChristopher
 * @brief The TcpListener class takes care of client facing operations. This includes allowing client
 *		connections to the server, moderating those connections, disconnecting clients from the server,
 *		and cleaning up server resources upon server shutdown. This class also takes incoming requests from
 *		clients, sends them to the Handler class object if they require handling server side, and when
 *		necessary sends responses back to the client applications.
 */

// TcpListener class forward declaration
class TcpListener;

// Callback to data received
typedef void(*MessageReceivedHandler)(TcpListener* listener, int socketId, std::string msg);

class TcpListener
{

private:
	std::string m_ipAddress;				// The ip address of the server
	int m_port;								// The server port
	bool m_running;							// True if the server is running
	MessageReceivedHandler m_handler;		// The handler for incoming messages

	/**
	 * @brief The CreateSocket() function creates a socket
	 * @return Returns the newly created socket
	 */
	SOCKET CreateSocket();

	/**
	 * @brief The WaitForConnection() function waits for a client connection
	 * @param listening The socket for the server to listen on
	 * @return Returns the client socket
	 */
	SOCKET WaitForConnection(SOCKET& listening);

public:
	/**
	 * @brief TcpListener constructor and destructor
	 * @param ipAddress The ip address of the server
	 * @param port The server port
	 * @param handler The handler for incoming messages
	 */
	TcpListener(std::string ipAddress, int port, MessageReceivedHandler handler);

	~TcpListener();

	/**
	 * @brief The Send() function sends a message back to the client
	 * @param clientSocket The socket to send the message to
	 * @param msg The message to be sent
	 */
	void Send(int clientSocket, std::string& msg);

	/**
	 * @brief The Init() function initializes WinSock
	 * @return Returns true if WinSock is successfully initialized
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