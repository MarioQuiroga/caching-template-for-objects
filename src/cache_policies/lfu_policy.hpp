/*
    Inspired by solutions found in:
    https://leetcode.com/problems/lfu-cache/discuss/94673/c-solution-with-detailed-explanations-using-indexed-priority-queue-ie-hashmap-priority-queue
    https://algs4.cs.princeton.edu/24pq/
*/
#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "../Cache_data.hpp"

template<class Key>
class Node{
    Key key;
    int fre;
    Node(Key k){
        key = k;
        fre = 1;
    }
    Node(){
        key = -1;
        fre = 0;
    }
};

namespace Policies{
template<class Key, class Data, typename hash = std::hash<Key>>
class lfu_cache {
    std::vector<Node<Key>*> pq; // A priority queue, with the least usage frequency and least recently used element at the top.
	std::unordered_map<Key, int, hash> mp; // A mapping from the key of the element to its index in the priority queue.

public:
    lfu_cache(){
        Node<Key>* dummy = new Node<Key>();
        pq.push_back(dummy); // The pq start from pq[1].
    }
    void update_place(Key key){
        // ++ to frequency of key
        int index = mp[key];
        pq[index]->fre++;
        sink(index);
    }   

    void insert(Key key, Data * data, std::unordered_map<Key, Data*, hash> * storage, int max_entries, int * cur_entries){        
        if(max_entries == *cur_entries){
            // find to min freq to remove
            int oldKey = pq[1]->key;
            storage.erase(oldKey);
            mp.erase(oldKey);
            Node<Key>* newnode = new Node<Key>(key);
            pq[1] = newnode;
            mp[key] = 1;
            sink(1);
        }else{
            Node<Key>* newnode = new Node<Key>(key);
            pq.push_back(newnode);
            mp[key] = pq.size() - 1;
            swim(pq.size() - 1);
        }
        std::pair<Key,Data*> d(key,data);
        storage->insert(d);
    } 

    /*
     * Recursively sink a node in priority queue. A node will be sinked, when its frequency is larger than any of its
     * children nodes, or the node has the same frequency with a child, but it is recently updated. 
     */
	void sink(int index) {
	    int left = 2 * index, right = 2 * index + 1, target = index;
	    if(left < pq.size() && pq[left]->fre <= pq[target]->fre) // If the left child has the same frequency, we probably need to swap the parent node and the child node, because the parent node is recently accessed, and the left child node was accessed at an older time stamp.
               target = left;
            if(right < pq.size()) { 
                if(pq[right]->fre < pq[target]->fre || (pq[right]->fre == pq[target]->fre && pq[right]->timeStamp < pq[target]->timeStamp)) // If right child has the same frequency and an older time stamp, we must swap it.
                     target = right;
		}
		if(target != index) {
		    myswap(target, index);
	            sink(target);
		}
	}

    /*
     * Recursively swim a node in priority queue. A node will be swimmed, when its frequency is less than its
     * parent node. If the node has the same frequency with its parent, it is not needed to be swimmed, because
     * it is recently accessed.
     */
	void swim(int index) {
	    int par = index / 2;
	    while(par > 0 && pq[par]->fre > pq[index]->fre) {
	        myswap(par, index);
		index = par;
		par /= 2;
	    }
	}

	void myswap(int id1, int id2) {
	    swap(pq[id1], pq[id2]);
	    mp[pq[id1]->key] = id1;
	    mp[pq[id2]->key] = id2;
	}
};
}