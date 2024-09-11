#include "csocket.h"

int main()
{
	csocket sock = csocket::create("127.0.0.1", 9000, SOCK_STREAM);

	sock.client(1);
}

//#include <iostream>
//#include <filesystem>
//#include <string>
//#include <variant>
//#include <thread>
//#include <chrono>
//#include <atomic>
//
//#include <winsock2.h>
//#include <Ws2tcpip.h>
//
//#pragma comment(lib, "Ws2_32.lib")
//
//using namespace std;
//using sockresult = variant<SOCKET, string>;
//
//#define SOCK_REUSEADDR 1 << 0
//#define SOCK_NONBLOCK 1 << 1
//
//struct addr {
//    string ip;
//    unsigned short port;
//    int type;
//};
//
//bool is_ipv4(addr address) {
//    sockaddr_in input{};
//    return inet_pton(AF_INET, address.ip.c_str(), &input) == 1;
//}
//
//bool is_ipv6(addr address) {
//    sockaddr_in6 input;
//    return inet_pton(AF_INET6, address.ip.c_str(), &input) == 1;
//}
//
///**
// * Creates a socket as a client
// */
//sockresult client(addr address, int option) {
//    unsigned long ul_value = 1;
//    const char* char_value = "1";
//    static SOCKET sock = INVALID_SOCKET;
//    addrinfo hint{}, * res = nullptr;
//
//    hint.ai_protocol = address.type == SOCK_STREAM ? IPPROTO_TCP : IPPROTO_UDP;
//    hint.ai_socktype = address.type;
//
//    if (is_ipv4(address))
//        hint.ai_family = AF_INET;
//    else if (is_ipv6(address))
//        hint.ai_family = AF_INET6;
//    else
//        return sock;
//
//    if (option & SOCK_NONBLOCK && ioctlsocket(sock, FIONBIO, &ul_value))
//        return "Non-blocking failed for socket";
//
//    if (option & SOCK_REUSEADDR && setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, char_value, sizeof char_value))
//        return "Reuseaddr failed for socket";
//
//    if (getaddrinfo(address.ip.c_str(), to_string(address.port).c_str(), &hint, &res))
//        return "Unable to get address info";
//
//    if (connect(sock, res->ai_addr, res->ai_addrlen))
//        return "Unable to connect to ip/port";
//
//    return sock;
//};
//
//sockresult server(addr address, int option) {
//    unsigned long ul_value = 1;
//    char* char_value = "1";
//    static SOCKET sock = INVALID_SOCKET;
//    addrinfo hint{}, * res = nullptr;
//
//    hint.ai_protocol = address.type == SOCK_STREAM ? IPPROTO_TCP : IPPROTO_UDP;
//    hint.ai_socktype = address.type;
//
//    if (is_ipv4(address))
//        hint.ai_family = AF_INET;
//    else if (is_ipv6(address))
//        hint.ai_family = AF_INET6;
//    else
//        return sock;
//
//    if (option & SOCK_NONBLOCK && ioctlsocket(sock, FIONBIO, &ul_value))
//        return "Non-blocking failed for socket";
//
//    if (option & SOCK_REUSEADDR && setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, char_value, sizeof char_value))
//        return "Reuseaddr failed for socket";
//
//    if (getaddrinfo(address.ip.c_str(), to_string(address.port).c_str(), &hint, &res))
//        return "Unable to get address info";
//
//    if (bind(sock, res->ai_addr, res->ai_addrlen))
//        return "Unable to bind to ip/port";
//
//    if (listen(sock, SOMAXCONN))
//        return "Unable to listen to socket";
//
//    return sock;
//}
//
//atomic<bool> flag(false);
//
//int hostinger_thread() {
//    while (!flag) {
//
//        this_thread::sleep_for(chrono::seconds(60));
//    }
//}
//
//int main() {
//    addr address;
//
//    address.ip = "127.0.0.1";
//    address.port = 6969;
//    address.type = SOCK_STREAM;
//
//
//
//    for (const filesystem::directory_entry& file : filesystem::recursive_directory_iterator("./")) {
//        printf(file.path().string().c_str());
//        printf("\n");
//    }
//}