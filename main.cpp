#include "csocket.h"

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <string>
#include <vector>
#include <filesystem>

#include <winsock2.h>
#include <Ws2tcpip.h>
#include "ansi.h"

#pragma comment(lib, "Ws2_32.lib")

using std::atomic;
using std::thread;
using std::string;
using std::vector;

namespace fs = std::filesystem;

template<typename ...Str>
void write(Str ...str)
{
  vector<string> a = {static_cast<string>(str)...};

  for(string v : a)
  {
    std::cout << v;
  }
}

void filethread()
{

}

int main()
{
  string host;
  unsigned short port;
  string error;

  write(ansi::graphic::reset(), "Hostinger FTP\n", "IP: ");
  std::cin >> host;
  write(ansi::cursor::up(1), "\n", "Port: ");
  std::cin >> port;
  write("App is attempting to connect to hostinger FTP\n\n");

  csocket conn = csocket::create(host, port, SOCK_STREAM);

  if(!conn.client(CS_NONBLOCK | CS_REUSEADDR, error))
    write(error + "e\n");
  else
    write("Connected to Hostinger FTP server");

}

// int ui(atomic<bool> &flag)
// {
//   return 1;
// }

// int main()
// {
//   for(int i = 0; i < 256; i++)
//   {
//     // printf("\033[48;5;%dmExcellence\n", i);
//     printf("\033[48;2;%d;0;0mExcellence", i);
//   }
//   // std::cout << a <<std::endl;
//   // printf("\033[48;2;250;50;0mhithere");
//   // printf("Hey");
//   // csocket socket = csocket::create("::1", 9000, 1);
//   // atomic<bool> flag(true);
//   // timeval time{};

//   // thread ui_thread(ui, std::ref(flag));

//   // time.tv_sec = 1;

//   // socket.server(CS_NONBLOCK | CS_REUSEADDR);
//   // socket.start(flag, 1024, time);
// }