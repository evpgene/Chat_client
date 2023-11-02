#pragma once
//
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class TCP_client
{
public:
	TCP_client();
	~TCP_client();
    int configureConnection(/*int argc, char** argv*/);
    int openConnection();
    int closeConnection();
    bool send_data(const std::string& str);
    bool receive_data(std::string& str);

private:
	WSADATA wsaData;

	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo* result{ NULL };
	struct addrinfo* ptr{ NULL };
	struct addrinfo    hints;

	int iResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	char sendbuf[DEFAULT_BUFLEN];
	int sendbuflen = DEFAULT_BUFLEN;
	bool connection_closed{ false };
};



