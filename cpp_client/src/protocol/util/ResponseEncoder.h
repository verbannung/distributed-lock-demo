//
// Created by Ko-chieh Yin on 9/27/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_RESPONSEENCODER_H
#define DISTRIBUTED_LOCK_DEMO_RESPONSEENCODER_H
#include <string>

#include "protocol/dto/Result.h"

struct Result;

class ResponseEncoder {
public:
    static std::string encode(const Result& res) {
        if (res.code != 200)
            return "ERR " + std::to_string(res.code) + " " + res.message;
        if (res.data.has_value())
            return "OK " + res.data.value();
        return "OK " + res.message;
    }
};

#endif //DISTRIBUTED_LOCK_DEMO_RESPONSEENCODER_H