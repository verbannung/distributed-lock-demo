//
// Created by vscode on 9/26/25.
//

#include "Protocol.h"

using namespace dls::server;

RequestDTO Protocol::parseRequest(const std::string& request) {
    auto parseJson = json::parse(request);
    RequestDTO dto;

    dto.action = parseJson.value("action","");
    dto.owner = parseJson.value("owner","");
    dto.key = parseJson.value("key","");
    dto.ttl = parseJson.value("ttl",0);
    return dto;
}

std::string Protocol::buildResponse(const std::string& status,
                                    const std::string& reason) {
    json res;
    res["status"] = status;
    if (!reason.empty()) {
        res["reason"] = reason;
    }
    return res.dump();
}

std::string HttpProtocol::extractBody(const std::string& request) {
    // 找到空行 \r\n\r\n，后面就是 body
    auto pos = request.find("\r\n\r\n");
    if (pos == std::string::npos) {
        return "";
    }
    return request.substr(pos + 4); // 返回 JSON 字符串
}

std::string HttpProtocol::buildHttpResponse(const std::string& jsonBody) {
    std::ostringstream oss;
    oss << "HTTP/1.1 200 OK\r\n";
    oss << "Content-Type: application/json\r\n";
    oss << "Content-Length: " << jsonBody.size() << "\r\n";
    oss << "Connection: close\r\n";
    oss << "\r\n";
    oss << jsonBody;
    return oss.str();
}