#include "csocket.h"

WSADATA csocket::data{};
bool csocket::is_init = false;

csocket::csocket(string ip, unsigned short port, addrinfo hint)
{
	this->hint = hint;
	this->ip = ip;
	this->port = port;

	FD_ZERO(&socks);
}

csocket::~csocket()
{
	if (is_init)
	{
		is_init = false;
		WSACleanup();
	}

	closesocket(sock);
}

template<typename ...Args>
bool csocket::client(Args ...args)
{
	printf("TEST");

	return false;
}

template<typename ...Args>
bool csocket::server(Args ...args)
{
	return false;
}

template<typename ...Args>
bool csocket::setopt(Args ...args)
{

	return false;
}

bool csocket::start()
{
	return false;
}

csocket csocket::create(string ip, unsigned short port, int type)
{
	addrinfo hint;

	hint.ai_socktype = type;
	hint.ai_protocol = type == SOCK_STREAM ? IPPROTO_TCP : IPPROTO_UDP;

	csocket sock(ip, port, hint);

	return sock;
}