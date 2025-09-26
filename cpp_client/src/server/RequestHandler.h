//
// Created by Ko-chieh Yin on 9/26/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_REQUESTHANDLER_H
#define DISTRIBUTED_LOCK_DEMO_REQUESTHANDLER_H
#include <sstream>

#include "../core/LockManager.h"
#include "./Protocol.h"

using namespace dls::core;
using namespace dls::server;


namespace dls::server {
    class RequestHandler {
    private:
        LockManager& lockManager;

    public:
        explicit RequestHandler(LockManager& manager) : lockManager(manager) {}

        [[nodiscard]] LockManager& getLockManager() const{
            return lockManager;
        }


        [[nodiscard]] std::string handleAcquire(const std::string& key, const std::string& ownerId, uint64_t ttlMs) const {
            bool ok = lockManager.acquire(key, ownerId, ttlMs);

            return Protocol::buildResponse(ok ? "OK" : "FAIL");

        }

        [[nodiscard]] std::string handleRenew(const std::string& key, const std::string& ownerId, uint64_t ttlMs) const {
            bool ok = lockManager.renew(key, ownerId, ttlMs);

            return Protocol::buildResponse(ok ? "OK" : "FAIL");

        }




        [[nodiscard]] std::string handleRelease(const std::string& key, const std::string& ownerId) const {
            bool ok = lockManager.release(key, ownerId);
            return Protocol::buildResponse(ok?"RELEASED" : "NOT_OWNER");
        }

        [[nodiscard]] std::string handleRequest(const std::string& request) const {

            std::string body = HttpProtocol::extractBody(request);

            auto requestDto = Protocol::parseRequest(body);

            std::string response;

            if (requestDto.action == "ACQUIRE") {
                response= handleAcquire(requestDto.key, requestDto.owner, requestDto.ttl);
            } else if (requestDto.action  == "RELEASE") {
                response= handleRelease(requestDto.key, requestDto.owner);
            } else if (requestDto.action  == "RENEW") {
                response= handleRenew(requestDto.key, requestDto.owner, requestDto.ttl);
            }
            else{
                response= Protocol::buildResponse("FAIL","请求失败");
            }

            return HttpProtocol::buildHttpResponse(response);
        }
    };
}

#endif //DISTRIBUTED_LOCK_DEMO_REQUESTHANDLER_H