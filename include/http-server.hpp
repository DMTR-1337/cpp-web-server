#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <string>
#include <map>
#include <functional>

/* Cross platform socket type */
#ifdef _WIN32
#include <winsock2.h>
typedef SOCKET sockettype;
#else
typedef int sockettype;
#endif

class WebServer
{
public:
    /* Constructor */
    WebServer(int port);

    /* Socket cleanup destructor */
    ~WebServer();

    /* Register a route */
    void get(const std::string& path, std::function<std::string()> handler);

    /* Start main server loop */
    void runserver();

private:
    int port;
    sockettype server_fd;
    std::map<std::string, std::function<std::string()>> routes;

    /* Handle individual requests */
    void handle_request(sockettype client);
};

#endif