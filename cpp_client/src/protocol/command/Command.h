//
// Created by Ko-chieh Yin on 9/27/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_COMMAND_H
#define DISTRIBUTED_LOCK_DEMO_COMMAND_H

#include <sstream>
#include <utility>
#include "ICommand.h"

template<typename T>
class Command: public ICommand {
public:
    T payload;
    explicit Command(T payload): payload(std::move(payload)){}
    [[nodiscard]] std::string toString() const override {
        std::ostringstream oss;
        oss << "receive message:" << payload;
        return oss.str();
    }
};

#endif //DISTRIBUTED_LOCK_DEMO_COMMAND_H