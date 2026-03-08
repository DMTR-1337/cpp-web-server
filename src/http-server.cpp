#include "http-server.hpp"
#include <iostream>
#include <sstream>

/* Platform headers */
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

WebServer::WebServer(int port) : port(port)
{
#ifdef _WIN32
    /* Initialize Winsock */
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    server_fd = INVALID_SOCKET;
#else
    server_fd = -1;
#endif
}

WebServer::~WebServer()
{
#ifdef _WIN32
    /* Cleanup Winsock */
    WSACleanup();
#endif
}

void WebServer::get(const std::string& path, std::function<std::string()> handler)
{
    /* Register route handler */
    routes[path] = handler;
}

void WebServer::runserver()
{
    /* Create socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

#ifdef _WIN32
    if (server_fd == INVALID_SOCKET) return;
#else
    if (server_fd < 0) return;
#endif

    /* Allow port reuse */
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));

    /* Bind to port */
    struct sockaddr_in addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) return;
    if (listen(server_fd, 10) < 0) return;

    std::cout << "Listening on " << port << "...\n";

    /* Accept incoming connections */
    while (true)
    {
        socklen_t len = sizeof(addr);
        sockettype client = accept(server_fd, (struct sockaddr*)&addr, &len);

#ifdef _WIN32
        if (client != INVALID_SOCKET) handle_request(client);
#else
        if (client >= 0) handle_request(client);
#endif
    }
}

void WebServer::handle_request(sockettype client)
{
    char buf[1024] = { 0 };

    /* Read request */
#ifdef _WIN32
    recv(client, buf, 1024, 0);
#else
    read(client, buf, 1024);
#endif

    /* Parse request line */
    std::string method, path, ver;
    std::istringstream(buf) >> method >> path >> ver;

    /* Default to 404 */
    std::string body = "<h1>404 Not Found</h1>";
    std::string status = "HTTP/1.1 404 Not Found\r\n";

    /* Execute route if found */
    if (method == "GET" && routes.count(path))
    {
        body = routes[path]();
        status = "HTTP/1.1 200 OK\r\n";
    }

    /* Build and send response */
    std::string res = status +
        "Content-Type: text/html\r\n"
        "Content-Length: " + std::to_string(body.length()) + "\r\n"
        "Connection: close\r\n\r\n" + body;

    send(client, res.c_str(), res.length(), 0);

    /* Close connection */
#ifdef _WIN32
    closesocket(client);
#else
    close(client);
#endif
}