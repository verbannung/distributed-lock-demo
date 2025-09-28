//
// Created by Ko-chieh Yin on 9/28/25.
//

#include "ParseLockACQ.h"



struct AcquireDTO;

std::string ParseLockACQ::getCommandType() const {
    return {"AQS"};
}

std::unique_ptr<ICommand> ParseLockACQ::parse(std::istringstream &iss) const {
    std::string key, owner;
    uint64_t ttl;
    iss >> key >> owner >> ttl;
    return std::make_unique<Command<AcquireDTO>>(AcquireDTO{key, owner, ttl});
}
