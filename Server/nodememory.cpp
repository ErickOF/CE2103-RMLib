#include "nodememory.h"

using namespace std;

// Constructor
NodeMemory::NodeMemory(string data, string key){
    count = 100;
    this->data = data;
    this->key = key;
    this->next = NULL;
}

// Destructor
NodeMemory::~NodeMemory(){
}

// Disminuye el conteo de referencia
void NodeMemory::decrease_count(){
    count--;
}

// Getters y setters
int NodeMemory::get_count(){
    return count;
}

string NodeMemory::get_data(){
    return data;
}

string NodeMemory::get_key(){
    return key;
}

NodeMemory *NodeMemory::get_next(){
    return next;
}

void NodeMemory::set_data(string data){
    this->data = data;
}

void NodeMemory::set_key(string key){
    this->key = key;
}

void NodeMemory::set_next(NodeMemory *next){
    this->next = next;
}
