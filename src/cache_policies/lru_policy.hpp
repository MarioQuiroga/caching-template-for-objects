#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include "../Cache_data.hpp"

namespace Policies{
template<typename Key, class Data, typename hash = std::hash<Key>>
class lru_cache {
public:
    std::list<Key> entries;

    lru_cache(){}

    void update_place(Key key){
        if(key != *entries.begin()){
            entries.remove(key);
            entries.push_front(key);
        }
    }   

    void insert(Key key, Data * data, std::unordered_map<Key, Data*, hash> * storage, int max_entries, int * cur_entries){
        if(max_entries == *cur_entries){
            Key old_key = entries.back();
            entries.remove(old_key); 
            storage->erase(old_key);
        }else{
            *cur_entries += 1;
        }
        entries.push_front(key);
        std::pair<Key,Data*> d(key,data);
        storage->insert(d);
    } 
};

}