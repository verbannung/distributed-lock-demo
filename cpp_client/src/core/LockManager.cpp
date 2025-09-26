//
// Created by Ko-chieh Yin on 9/25/25.
//

#include "LockManager.h"

#include <thread>

#include "LockInfo.h"

//注意这多线程并不是线程安全的
namespace dls::core {
    bool LockManager::acquire(const std::string &key ,const std::string& ownerId , uint64_t ttlMs) {
        uint64_t expire = LockManager::nowMs() + ttlMs;

        auto it = lockTable.find(key);
        if (it == lockTable.end()) {
            lockTable[key] = LockInfo(ownerId, expire);
            return true;
        }

        if (it->second.expireTime <= nowMs()) {
            lockTable[key] =  LockInfo(ownerId, expire);
            return true;
        }

        return false;
    }

    bool LockManager::release(const std::string &key, const std::string& ownerId) {
        auto it = lockTable.find(key);
        if (it != lockTable.end() && it->second.ownerId == ownerId) {
            lockTable.erase(it);
            return true;
        }
        return false;
    }

    bool LockManager::renew(const std::string& key, const std::string& ownerId, uint64_t ttlMs) {
        auto it = lockTable.find(key);
        if (it != lockTable.end() && it->second.ownerId == ownerId) {
            it->second.expireTime = nowMs() + ttlMs;
            return true;
        }
        return false;
    }

    void LockManager::clear() {
        uint64_t now = LockManager::nowMs();
        for (auto it = lockTable.begin(); it != lockTable.end();) {
            if (it->second.expireTime <= now) {
                it = lockTable.erase(it);
            } else {
                ++it;
            }
        }
    }

    // void LockManager::startCleaner() {
    //     std::thread([this] {
    //         while (running) {
    //             std::this_thread::sleep_for(std::chrono::seconds(1));
    //             clear();
    //         }
    //     }).detach();
    // }
}
