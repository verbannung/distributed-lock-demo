//
// Created by Ko-chieh Yin on 9/25/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_LOCKINFO_H
#define DISTRIBUTED_LOCK_DEMO_LOCKINFO_H
#include <string>
#include <utility>


    namespace dls::core {
        class LockInfo {
        public:
            std::string ownerId;
            uint64_t expireTime{};

            LockInfo() = default;
            LockInfo( std::string ownerId, const uint64_t expireTime) : ownerId(std::move(ownerId)), expireTime(expireTime) {}
        };
    }




#endif //DISTRIBUTED_LOCK_DEMO_LOCKINFO_H