#include "nodecache.h"

using namespace std;

// Constructor
NodeCache::NodeCache(string data, string key){
    this->data = data;
    this->key = key;
    this->next = NULL;
    this->accessed = 0;
}

// Destructor
NodeCache::~NodeCache(){
}

// Getters y setters
int NodeCache::get_accessed(){
    return accessed;
}

string NodeCache::get_data(){
    return data;
}

string NodeCache::get_key(){
    return key;
}

NodeCache *NodeCache::get_next(){
    return next;
}

void NodeCache::set_data(string data){
    this->data = data;
}

void NodeCache::set_key(string key){
    this->key = key;
}

void NodeCache::set_next(NodeCache *next){
    this->next = next;
}

// Contar un acceso al nodo
void NodeCache::count_accessed(){
    accessed++;
}
