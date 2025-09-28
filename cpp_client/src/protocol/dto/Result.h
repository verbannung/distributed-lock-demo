//
// Created by Ko-chieh Yin on 9/27/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_RESULT_H
#define DISTRIBUTED_LOCK_DEMO_RESULT_H

struct Result {
    int code;
    std::string message;
    std::optional<std::string> data;

    static Result ok(const std::string& msg = "OK") {
        return {200, msg, std::nullopt};
    }

    static Result fail(int c, const std::string& msg) {
        return {c, msg, std::nullopt};
    }

    static Result withData(const std::string& data) {
        return {200, "OK", data};
    }
};



#endif //DISTRIBUTED_LOCK_DEMO_RESULT_H