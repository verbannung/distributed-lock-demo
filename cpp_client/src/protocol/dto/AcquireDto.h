//
// Created by Ko-chieh Yin on 9/27/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_ACQUIREDTO_H
#define DISTRIBUTED_LOCK_DEMO_ACQUIREDTO_H
#include <string>


struct AcquireDTO {
    std::string key;
    std::string owner;
    uint64_t ttl;

    [[nodiscard]] std::string toString() const {
        std::ostringstream oss;
        oss << "[ACQUIRE] key="
        << key
        << ", owner="
        << owner
        << ", ttl="
        << ttl;
        return oss.str();
    }
};

template<>
std::string Command<AcquireDTO>::toString() const {
    return payload.toString();
}
#endif //DISTRIBUTED_LOCK_DEMO_ACQUIREDTO_H