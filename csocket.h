#pragma once

#include <string>
#include <variant>
#include <tuple>

#include <winsock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define CS_NONBLOCK 1;
#define CS_REUSEADDR 2;


using std::string;
using std::variant;
using std::tuple;

class csocket {
private:
	static WSADATA data;
	static bool is_init;

	string ip;
	unsigned short port;
	addrinfo hint;
	fd_set socks = {};

public:
	SOCKET sock = INVALID_SOCKET;

	csocket(string ip, unsigned short port, addrinfo hint);
	~csocket();
	template<typename ...Args>
	bool client(Args ...args);
	template<typename ...Args>
	bool server(Args ...args);
	template<typename ...Args>
	bool setopt(Args ...args);
	bool start();

	static csocket create(string ip, unsigned short port, int type);
};