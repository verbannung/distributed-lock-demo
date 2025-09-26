#include <gtest/gtest.h>
#include "../src/core/LockManager.h"

using dls::core::LockManager;

TEST(LockManagerTest, AcquireAndRelease) {
    LockManager manager;

    EXPECT_TRUE(manager.acquire("key1", "owner1", 1000));

    EXPECT_FALSE(manager.acquire("key1", "owner2", 1000));

    EXPECT_TRUE(manager.release("key1", "owner1"));
    EXPECT_TRUE(manager.acquire("key1", "owner2", 1000));
}