//
// Created by Ko-chieh Yin on 9/25/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_TCPSERVER_H
#define DISTRIBUTED_LOCK_DEMO_TCPSERVER_H
#include <unordered_map>

#if defined(__linux__)
    #define USE_EPOLL
    #include <sys/epoll.h>
#elif defined(__APPLE__)
    #define USE_KQUEUE
    #include <sys/event.h>
    #include <sys/time.h>
#endif

#include "./RequestHandler.h"
namespace dls::server {

    class TcpServer {
    public:
        TcpServer( int port,dls::server::RequestHandler& handler);
        void start();
    private:
        int port;  //服务器监听端口号
        int listenFd;   //进程唯一标识符(OS分配) 套接字
        int loopFd;   // 事件循环驱动句柄
        RequestHandler& handler;

        void setupServerSocket();
        void handleNewConnection() const;

         void handleClientMessage(int clientFd) const;


        std::unordered_map<int,std::string> readBuffer;     //每个fd的缓存

    };

}



#endif //DISTRIBUTED_LOCK_DEMO_TCPSERVER_H