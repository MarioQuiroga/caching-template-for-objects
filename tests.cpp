#include <iostream>
#include <gtest/gtest.h>
#include <cstddef>
#include "src/cache_policies/lru_policy.hpp"
#include "src/cache_policies/lfu_policy.hpp"
//#include "cache_policies/lfuda_policy.hpp"
#include "src/Cache.hpp"


typedef std::pair<int, int> type_pair;
struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2> &pair) const
	{
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

using namespace Policies;

// Tests lru policies
TEST(CacheTest, get_lru){
    // Create vars
    Cache<type_pair, Cache_data, pair_hash, lru_cache> cache(10);
    type_pair key = type_pair(10, 11);
    Cache_data data(0);
    // get pointer to data
    Cache_data * d = cache.get(key);
    ASSERT_EQ(NULL, d);
}

TEST(CacheTest, insert_lru){    
    // Create vars
    Cache<type_pair, Cache_data, pair_hash, lru_cache> cache(10);
    type_pair key(10, 11);
    Cache_data data(10);
    // Insert data
    cache.insert(key, &data);
    // get pointer to data
    Cache_data * d = cache.get(key);
    ASSERT_EQ(data.count, d->count);
}

TEST(CacheTest, modify_lru){    
    // Create vars
    Cache<type_pair, Cache_data, pair_hash, lru_cache> cache(10);
    type_pair key(10, 11);
    Cache_data data(10);
    // Insert data
    cache.insert(key, &data);
    // get pointer to data
    Cache_data * d = cache.get(key);
     ASSERT_EQ(10, d->count);
    // modify data
    d->count = 3;
    // get data again
    d = cache.get(key);
    ASSERT_EQ(3, d->count);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
