//
// Created by Ko-chieh Yin on 9/25/25.
//

#include "TcpServer.h"

#include <functional>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include "./RequestHandler.h"

using namespace dls::server;

TcpServer::TcpServer( int port, dls::server::RequestHandler& handler)
    : port(port), listenFd(0), loopFd(0), handler(handler) {
}

void TcpServer::setupServerSocket() {
    //使用socket，tcp连接
    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd < 0) {
        perror("错误的套接字");
        exit(1);
    }

    int opt = 1;
    //允许套接字复用
    setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET; // 地址族 (AF_INET 表示 IPv4)
    addr.sin_port = htons(port); // 端口号 (网络字节序)
    addr.sin_addr.s_addr = INADDR_ANY; //本机IP 地址

    if (bind(listenFd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("绑定进程失败");
        exit(1);
    }

    if (listen(listenFd, SOMAXCONN) < 0) {
        perror("监听失败");
        exit(1);
    }

#if defined(USE_EPOLL)
    loopFd = epoll_create1(0);
    if (loopFd < 0) {
        perror("epoll_create1 失败");
        exit(1);
    }

    struct epoll_event ev{};
    ev.events = EPOLLIN;
    ev.data.fd = listenFd;
    if (epoll_ctl(loopFd, EPOLL_CTL_ADD, listenFd, &ev) < 0) {
        perror("epoll_ctl 失败");
        exit(1);
    }

#elif defined(USE_KQUEUE)
    loopFd = kqueue();
    if (loopFd < 0) {
        perror("kqueue打开失败");
        exit(1);
    }
    struct kevent evSet{};
    //EVFILT_READ关心可读事件，EV_ADD事件注册到kqueue
    EV_SET(&evSet, listenFd, EVFILT_READ, EV_ADD, 0, 0, NULL);
    //事件注册到内核kqueue之中
    kevent(loopFd, &evSet, 1, NULL, 0, NULL);
#endif
}

void TcpServer::start() {
    setupServerSocket();
    std::cout << "开始监听端口:" << port << std::endl;
    auto lastClean = std::chrono::steady_clock::now();
#if defined(USE_EPOLL)
    std::vector<struct epoll_event> events(64);




    while (true) {
        int n = epoll_wait(loopFd, events.data(), (int)events.size(), -1);


#elif defined(USE_KQUEUE)
    //存放返回事件，最多64个事件
    std::vector<struct kevent> events(64);
    //事件循环
    while (true) {
        //创建事件队列
        int n = kevent(loopFd, NULL, 0, events.data(), events.size(), NULL);
#endif
        for (int i = 0; i < n; i++) {
            int fd = events[i].data.fd;
            if (fd == listenFd) {
                handleNewConnection();
            } else {
                handleClientMessage(fd);
            }
        }

        auto now = std::chrono::steady_clock::now();
        if (now - lastClean > std::chrono::seconds(1)) {
            handler.getLockManager().clear();
            lastClean = now;
        }
    }
}


//新的连接
void TcpServer::handleNewConnection() const {
    int clientFd = accept(listenFd, nullptr, nullptr);
    if (clientFd >= 0) {
#if defined(USE_EPOLL)
        struct epoll_event ev{};
        ev.events = EPOLLIN;  // 关心读事件
        ev.data.fd = clientFd;
        epoll_ctl(loopFd, EPOLL_CTL_ADD, clientFd, &ev);


#elif defined(USE_KQUEUE)
        // 把新连接的 clientFd 注册到 kqueue，监听它的读写事件
        struct kevent evSet{};
        EV_SET(&evSet, clientFd, EVFILT_READ, EV_ADD, 0, 0, NULL);
        kevent(loopFd, &evSet, 1, NULL, 0, NULL);

#endif
        std::cout << "新客户端连接 fd=" << clientFd << std::endl;
    }
}

//触发客户端套接字
//客户端发了数据，或者断开了连接
void TcpServer::handleClientMessage(int clientFd) const{
    char buf[1024];
    long n=recv(clientFd, buf, sizeof(buf)-1, 0);
    if (n>0) {
        buf[n] = '\0';
        std::string request(buf);
        std::string response = handler.handleRequest(request);

        send(clientFd, response.c_str(), response.size(), 0);
    }else if (n==0) {
        close(clientFd);
    }else {
        perror("接收消息错误");
        close(clientFd);
    }

}


