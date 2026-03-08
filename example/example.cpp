#include "http-server.hpp"

int main()
{
    /* Initialize server on port 8080 */
    WebServer server(8080);

    /* Define endpoint/endpoints */
    server.get("/", []() {
        return "<h1>Hello World!</h1>";
    });

    /* Start server loop */
    server.runserver();

    return 0;
}