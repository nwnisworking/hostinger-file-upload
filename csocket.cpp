#include "csocket.h"

#include <string>
#include <iostream>

#include <winsock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

using std::string;

WSADATA csocket::data{};
bool csocket::is_init = false;

csocket::csocket(string ip, unsigned short port, addrinfo hint)
{
  this->ip = ip;
  this->port = port;
  this->hint = hint;
  FD_ZERO(&master);
  socket = INVALID_SOCKET;
}

csocket::~csocket()
{
  closesocket(socket);

  if(is_init)
  {
    is_init = false;
    WSACleanup();
  }
}

bool csocket::setopt(int option, string &error)
{
  union {
    unsigned long as_ulong;
    char as_char;
    bool as_bool;
  } value = {1};

  if(option & CS_NONBLOCK && ioctlsocket(socket, FIONBIO, &value.as_ulong))
  {
    error = "Unable to set to non-blocking mode";
    return false;
  }

  if(option & CS_REUSEADDR && setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &value.as_char, sizeof value.as_char))
  {
    error = "Unable to reuse address";
    return false;
  }

  return true;  
}

bool csocket::create_socket(addrinfo **res, string &error)
{
  if(is_ipv4())
  {
    hint.ai_family = AF_INET;
  }
  else if(is_ipv6())
  {
    hint.ai_family = AF_INET6;
  }
  else
  {
    error = "IP is invalid";
    return false;
  }

  if(getaddrinfo(ip.c_str(), std::to_string(port).c_str(), &hint, res))
  {
    error = "Unable to get address info";
    return false;
  }

  socket = ::socket(hint.ai_family, hint.ai_socktype, hint.ai_protocol);

  if(socket == INVALID_SOCKET)
  {
    error = "Socket returns invalid";
    return false;
  }

  return true;
}

bool csocket::client(int option, string &error)
{
  addrinfo *res = nullptr;

  if(
    !create_socket(&res, error) || 
    !setopt(option, error) || 
    connect(socket, res->ai_addr, res->ai_addrlen)
  )
    return false;

  return true;
}

bool csocket::server(int option, string &error)
{
  addrinfo *res = nullptr;

  if(
    !create_socket(&res, error) || 
    !setopt(option, error) ||
    bind(socket, res->ai_addr, res->ai_addrlen) ||
    listen(socket, SOMAXCONN)
  )
    return false;

  FD_SET(socket, &master);
  is_server = true;

  return true;
}

bool csocket::is_ipv4()
{
  sockaddr_in input{};

  return inet_pton(AF_INET, ip.c_str(), &input) == 1;
}

bool csocket::is_ipv6()
{
  sockaddr_in input{};

  return inet_pton(AF_INET6, ip.c_str(), &input) == 1;
}

csocket csocket::create(string ip, unsigned short port, int type)
{
  if(!is_init)
  {
    WSAStartup(MAKEWORD(2,2), &data);
    is_init = true;
  }

  addrinfo hint{};
  hint.ai_socktype = type;
  hint.ai_protocol = type == SOCK_STREAM ? IPPROTO_TCP : IPPROTO_UDP;

  return csocket(ip, port, hint);
}

void csocket::start(atomic<bool> &flag, int size, timeval time)
{
  fd_set read{};
  int nfds = socket;

  while(flag.load())
  {
    FD_ZERO(&read);
    read = master;
    int activity = select(nfds + 1, &read, NULL, NULL, &time);

    switch(activity)
    {
      case (0):
        // no message sent
      break;
      case (-1):
        flag.store(false);
      break;
      default:
        for(int i = 0; i < read.fd_count; i++)
        {
          if(!FD_ISSET(i, &read))
            continue;

          if(i == socket)
          {
            SOCKET conn = accept(socket, NULL, NULL);
            FD_SET(conn, &master);

            if(conn > nfds)
              nfds = conn;
          
            // Can include a event listener. Can hold off for now
          }
          else
          {
            // Set a max amount of total char here
            char buffer[size];
            int resize_size = recv(i, buffer, sizeof buffer, 0);

            if(resize_size == 0)
            {
              // Basically means user has closed connection 
              closesocket(i);
              FD_CLR(i, &master);
            }
            else if(resize_size < 0)
            {
              // Basically means receive failed
              closesocket(i);
              FD_CLR(i, &master);
            }
            else
            {
              std::cout << buffer << std::endl;
            }
          }
        }
      break;
    }
  }

  for(int i = 0; i < master.fd_count; i++)
  {
    closesocket(master.fd_array[i]);
  }
}