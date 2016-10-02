#pragma once

class CClientSock
{
public:
	CClientSock(void);
	~CClientSock(void);
	int Send(void* pcData, int iLength);
	int Recv(void* pcData, int iLength);

private:
	SOCKET	m_Socket;	
	
public:
	int Open(const CString& sServer, int iPort);
	int Close(void);
};
