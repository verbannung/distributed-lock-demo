//
// Created by vscode on 9/26/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_PROTOCOL_H
#define DISTRIBUTED_LOCK_DEMO_PROTOCOL_H

#include <string>
#include "../utils/json.hpp"

using json = nlohmann::json;

namespace dls::server {

    struct RequestDTO {
        std::string action;
        std::string owner;
        std::string key;
        int ttl;
    };


    class Protocol {
    public:
        static RequestDTO parseRequest(const std::string& request);
        static std::string buildResponse(const std::string& status,
                                         const std::string& reason = "请求成功");

    };

    class HttpProtocol {
    public:
        static std::string extractBody(const std::string& request);
        static std::string buildHttpResponse(const std::string& jsonBody);
    };

}



#endif //DISTRIBUTED_LOCK_DEMO_PROTOCOL_H