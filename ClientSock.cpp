#include "StdAfx.h"
#include "ClientSock.h"
#include <winsock.h>


#define PRINTERROR(s)	\
		fprintf(stderr,"\n%s: %d\n", s, WSAGetLastError())

CClientSock::CClientSock(void)
{
	WORD wVersionRequested = MAKEWORD(1,1);
	WSADATA wsaData;
	int nRet;

	//
	// Initialize WinSock.dll
	//
	nRet = WSAStartup(wVersionRequested, &wsaData);
	if (nRet)
	{
		fprintf(stderr,"\nWSAStartup(): %d\n", nRet);
		WSACleanup();
		return;
	}
	
	//
	// Check WinSock version
	//
	if (wsaData.wVersion != wVersionRequested)
	{
		fprintf(stderr,"\nWinSock version not supported\n");
		WSACleanup();
		return;
	}
}

CClientSock::~CClientSock(void)
{
	WSACleanup();
}

int CClientSock::Open(const CString& sServer, int iPort)
{
	//
	// Use inet_addr() to determine if we're dealing with a name
	// or an address
	//
	IN_ADDR		iaHost;
	LPHOSTENT	lpHostEntry;

	iaHost.s_addr = inet_addr(sServer);
	if (iaHost.s_addr == INADDR_NONE)
	{
		// Wasn't an IP address string, assume it is a name
		lpHostEntry = gethostbyname(sServer);
	}
	else
	{
		// It was a valid IP address string
		lpHostEntry = gethostbyaddr((const char *)&iaHost, 
						sizeof(struct in_addr), AF_INET);
	}
	if (lpHostEntry == NULL)
	{
		PRINTERROR("gethostbyname()");
		return -1;
	}


	//	
	// Create a TCP/IP stream socket
	//

	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_Socket == INVALID_SOCKET)
	{
		PRINTERROR("socket()"); 
		return -1;
	}


	//
	// Find the port number for the HTTP service on TCP
	//
	LPSERVENT lpServEnt;
	SOCKADDR_IN saServer;

	saServer.sin_port = htons(iPort);

	//
	// Fill in the rest of the server address structure
	//
	saServer.sin_family = AF_INET;
	saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);


	//
	// Connect the socket
	//
	int nRet;

	nRet = connect(m_Socket, (LPSOCKADDR)&saServer, sizeof(SOCKADDR_IN));
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("connect()");
		closesocket(m_Socket);
		return -1;
	}

	return 0;
}


int CClientSock::Send(void* pcData, int iLength)
{
	int nRet;
	
	//
	// Format the HTTP request
	//
	char szBuffer[1024];

	sprintf(szBuffer, "GET %s\n", "test.html");
	nRet = send(m_Socket, (char*)pcData, iLength, 0);
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("send()");
		closesocket(m_Socket);	
		return -1;
	}

	return iLength;
}

int CClientSock::Recv(void* pcData, int iLength)
{
	u_long val=1;
	ioctlsocket(m_Socket, FIONBIO, &val);
	//
	// Receive the file contents and print to stdout
	//
	int recvStat = 0;
	int iStart = 0;
	char* pcRecv = (char*)pcData;
	while(1)
	{
		int nRet;
		// Wait to receive, nRet = NumberOfBytesReceived
		nRet = recv(m_Socket, pcRecv + iStart, iLength, 0);

		
		if (nRet > 0)
		{
			recvStat = 1;
			iStart += nRet;
			Sleep(1000);
		}

		if (nRet < 0)
		{
			if (recvStat == 0)
				continue;
		
			if (recvStat == 1)
				break;
		}
		
		if (nRet == SOCKET_ERROR)
		{
			PRINTERROR("recv()");
//			break;
		}
		
		fprintf(stderr,"\nrecv() returned %d bytes", nRet);

		// Did the server close the connection?
		if (nRet == 0)
			break;
		// Write to stdout
//        fwrite(szBuffer, nRet, 1, stdout);
	}

	return iStart;	
}


int CClientSock::Close(void)
{
	closesocket(m_Socket);	

	return 0;
}
