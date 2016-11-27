/**
 * Jack server class testing
 *
 */
#include <Server/JackServer.h>

int main() {

    JackServer * server = new JackServer();

    server->start();

    return 0;

};
