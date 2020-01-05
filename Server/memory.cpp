#include "memory.h"
#include <iostream>

// Constructor
Memory::Memory(){
    size = 0;
    head = NULL;
}

// Destructor
Memory::~Memory(){
}

// Agregar un elemento a la lista
void Memory::add(string data, string key){
    // Si el esta vacio se agregar el nodo ahi
    if (head == NULL){
        head = new NodeMemory(data, key);
    } else {
        NodeMemory *temp = head;
        // Recorrer la lista hasta el ultimo elemento
        while (temp->get_next()){
            temp = temp->get_next();
        } // Agregar el nodo al ultimo
        temp->set_next(new NodeMemory(data, key));
        temp = NULL;
        delete temp;
    } size++;
}

// Verificar si el elemento existe en la lista
bool Memory::exist(string key){
    if (size == 0) return false;
    else if (size == 1 && head->get_key() == key) return true;
    NodeMemory *temp = head;
    // Recorrer la lista hasta que ya no hayan nodos
    while (temp->get_next() != NULL){
        // Si se encuentra el elemento se retorna true
        if (temp->get_key() == key){
            temp = NULL;
            delete temp;
            return true;
        } temp = temp->get_next();
    }
    temp = NULL;
    delete temp;
    return false;
}

// Obtener un nodo por el indice
NodeMemory* Memory::get(int index){
    // Si el indice esta fuera del rango devuelve una excepcion
    if (index < 0 || index >= size) throw out_of_range("index_out_of_range");
    NodeMemory *temp = head;
    // Recorrer la lista hasta el indice indicado
    for (int i = 0; i < index; i++){
        temp = temp->get_next();
    } return temp;
}

// Obtener un nodo por la llave
NodeMemory* Memory::get(string key){
    if (size == 1 && head->get_key() == key) return head;
    NodeMemory *temp = head;
    // Recorrer la lista hasta que ya no hayan nodos
    while (temp->get_next() != NULL){
        // Si se encuentra el elemento se retorna
        if (temp->get_key() == key) return temp;
        temp = temp->get_next();
    } // Si no se encuentra el elemento se devuelve una exception
    throw string("key_doesnt_exist");
}

// Obtener el size de la lista
int Memory::get_size(){
   return size;
}

// Remover un nodo por el indice
void Memory::remove(int index){
    // Si el indice esta fuera del rango devuelve una excepcion
    if (index < 0 || index >= size) throw out_of_range("index_out_of_range");
    NodeMemory *temp = head;
    // Si el primer nodo es el que se quiere eliminar
    if (index == 0){
        head = head->get_next();
    } else {
        NodeMemory *aux = NULL;
        // Recorrer la lista hasta el indice indicado
        for (int i = 0; i < index; i++){
            aux = temp;
            temp = temp->get_next();
        } // Desenlazar el nodo de la lista
        aux->set_next(temp->get_next());
        aux = NULL;
        delete aux;
    }
    delete temp;
    size--;
}

// Remover un nodo por la llave
void Memory::remove(string key){
    NodeMemory *temp = head;
    // Si el primer nodo es el que se quiere eliminar
    if (head->get_key() == key) {
        head = head->get_next();
    } else {
        bool finded = false;
        NodeMemory *aux = NULL;
        // Recorrer la lista hasta que ya no hayan nodos
        while (temp != NULL) {
            // Si se encuentra el elemento se elimina
            if (temp->get_key() == key) {
                aux->set_next(temp->get_next());
                aux = NULL;
                delete aux;
                finded = true;
                break;
            }
            aux = temp;
            temp = temp->get_next();
        }
        aux = NULL;
        delete aux;
        // Si no se encuentra el elemento se devuelve una exception
        if (!finded) throw string("key_doesnt_exist");
    }
    delete temp;
    size--;
}
