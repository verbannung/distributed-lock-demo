#include <gtest/gtest.h>
#include "../src/core/LockManager.h"
#include "../src/server/TcpServer.h"
#include "../src/server/RequestHandler.h"

using dls::core::LockManager;
using dls::server::RequestHandler;
using dls::server::TcpServer;



TEST(RequestHandlerTest, AcquireAndRelease) {
    LockManager manager;
    RequestHandler handler(manager);

    std::string acquireReq = R"({
    "action": "ACQUIRE",
    "key": "key1",
    "owner": "owner1",
    "timeout": 1000
})";

    std::string releaseReq = R"({
    "action": "RELEASE",
    "key": "key1",
    "owner": "owner1"
})";

    std::string res1 = handler.handleRequest(acquireReq);
    EXPECT_EQ(res1, "OK");

    std::string res2 = handler.handleRequest(acquireReq);
    EXPECT_EQ(res2, "FAIL");

    std::string res3 = handler.handleRequest(releaseReq);
    EXPECT_EQ(res3, "RELEASED");

    std::string res4 = handler.handleRequest(acquireReq);
    EXPECT_EQ(res4, "OK");
}