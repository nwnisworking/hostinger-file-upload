#pragma once

#include <string>
#include <atomic>

#include <winsock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define CS_NONBLOCK 1 << 0
#define CS_REUSEADDR 1 << 1

using std::string;
using std::atomic;

class csocket
{
  private: 
  static bool is_init;
  static WSADATA data;

  SOCKET socket;
  fd_set master;

  bool setopt(int option, string &error);
  bool create_socket(addrinfo **res, string &error);
  public:
  string ip;
  unsigned short port;
  addrinfo hint;
  bool is_server = false;

  csocket(string ip, unsigned short port, addrinfo hint);
  ~csocket();
  bool client(int option, string &error);
  bool server(int option, string &error);
  bool is_ipv4();
  bool is_ipv6();
  void start(atomic<bool> &flag, int size, timeval time);
  static csocket create(string ip, unsigned short port, int type);
};