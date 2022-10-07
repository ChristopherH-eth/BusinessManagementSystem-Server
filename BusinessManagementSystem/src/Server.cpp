#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

/**
 * @file Server.cpp
 * @author 0xChristopher
 */

void main()
{
	/// Initialize Winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);

	if (wsOk != 0)
	{
		std::cerr << "Can't initialize winsock. Exiting program..." << std::endl;
		return;
	}

	/// Create socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

	if (listening == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket. Exiting program..." << std::endl;
		return;
	}

	/// Bind ip address and port to socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	/// Tell Winsock the socket is for listening
	listen(listening, SOMAXCONN);

	/// Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];				/// Client's remote name
	char service[NI_MAXSERV];			/// Port client is connected on

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " connected on port " << service << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
	}

	/// Close listening socket
	closesocket(listening);

	/// Accept and echo message back to client
	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);

		/// Wait for client to send data
		int bytesreceived = recv(clientSocket, buf, 4096, 0);

		if (bytesreceived == SOCKET_ERROR)
		{
			std::cerr << "Error receiving client data. Exiting program..." << std::endl;
			return;
		}

		if (bytesreceived == 0)
			break;

		/// Echo back to client
		std::cout << "Received " << bytesreceived << " from client; replying..." << std::endl;
		send(clientSocket, buf, bytesreceived + 1, 0);
	}

	/// Close the socket
	closesocket(clientSocket);

	/// Cleanup Winsock
	WSACleanup();
}