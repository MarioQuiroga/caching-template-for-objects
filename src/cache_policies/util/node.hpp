#pragma once

template<class Key>
class Node{
public:
    Key key;
    int fre;
    int timeStamp; // the latest time stamp when this element is accessed.
    Node(Key k, int ts){
        key = k;
        fre = 1;
        timeStamp = ts;
    }
    Node(){}
};