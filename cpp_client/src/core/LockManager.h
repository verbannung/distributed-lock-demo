//
// Created by Ko-chieh Yin on 9/25/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_LOCKMANAGER_H
#define DISTRIBUTED_LOCK_DEMO_LOCKMANAGER_H
#include <atomic>
#include <string>
#include <unordered_map>
#include "LockInfo.h"
#include <chrono>
#include <mutex>


namespace dls::core {

        class LockInfo;

        class LockManager {
        public:
            //尝试获取锁
            bool acquire(const std::string &key ,const std::string& ownerId , uint64_t ttlMs);
            //释放锁
            bool release(const std::string &key ,const std::string& ownerId);

            bool renew(const std::string& key, const std::string& ownerId, uint64_t ttlMs);
            //清理过期的锁
            void clear();

            // void startCleaner() ;

            //开启清理线程


            unsigned long getLockCount() {
                return lockTable.size();
            }

            LockManager() = default;

        private:
            //TODO 后续改成跳表
            std::unordered_map<std::string, LockInfo> lockTable;

            //当前时间戳
            static uint64_t nowMs() {
                return std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
            }


            std::mutex mutex;
            std::atomic<bool> running{true};
        };
    }


#endif //DISTRIBUTED_LOCK_DEMO_LOCKMANAGER_H