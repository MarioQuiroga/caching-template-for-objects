#pragma once
#include "cache_policies/lru_policy.hpp"
#include <cstddef>
#include <unordered_map>
#include "Cache_data.hpp"

using namespace Policies;

template<typename Key, 
         class Data, 
         typename hash, 
         template<typename, class, typename> class Policy>
class Cache {
    std::unordered_map<Key, Data*, hash> storage;
    Policy<Key, Data, hash> policy;
    int max_entries;
    int cur_entries;

public:
    Cache(int size){
        max_entries = size;
        cur_entries = 0;
    }

    Data * get(Key key){
        typename std::unordered_map<Key, Data*, hash>::iterator i = storage.find(key);
        if(i == storage.end()){
            return NULL;
        }
        // return value, but first update its placed in your policy
        policy.update_place(key);
        return i->second;
    }


    void insert(Key key, Data * data){
        typename std::unordered_map<Key, Data*, hash>::iterator i = storage.find(key);
        if(i == storage.end()){   
            policy.insert(key, data, &storage, max_entries, &cur_entries);
        }
    }

    bool empty(){
        return storage.empty();
    }

};
