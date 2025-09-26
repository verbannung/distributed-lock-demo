#include <iostream>

#include "core/LockManager.h"
#include "server/TcpServer.h"

int main() {
    using namespace dls::core;
    using namespace dls::server;

    LockManager lockManager;
    RequestHandler handler(lockManager);

    int port =8081;
    TcpServer server(port,handler);

    std::cout << "分布式锁启动，监听端口"<<port << std::endl;

    server.start();

    return 0;
}
