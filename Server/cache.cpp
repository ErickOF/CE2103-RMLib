#include "cache.h"
#include <iostream>

// Constructor
Cache::Cache(){
    size = 0;
    head = NULL;
}

// Destructor
Cache::~Cache(){
}

// Agregar un elemento a la lista
void Cache::add(string data, string key){
    if (size == 5) {
        remove_unless();
    } // Si el esta vacio se agregar el nodo ahi
    if (head == NULL){
        head = new NodeCache(data, key);
    } else {
        NodeCache *temp = head;
        // Recorrer la lista hasta el ultimo elemento
        while (temp->get_next()){
            temp = temp->get_next();
        } // Agregar el nodo al ultimo
        temp->set_next(new NodeCache(data, key));
        temp = NULL;
        delete temp;
    } size++;
}

// Verificar si el elemento esta en el cache
bool Cache::exist(string key){
    if (size == 0) return false;
    else if (size == 1 && head->get_key() == key) return true;
    NodeCache *temp = head;
    // Recorrer la lista hasta que ya no hayan nodos
    while (temp->get_next() != NULL){
        // Si se encuentra el elemento se retorna true
        if (temp->get_key() == key) {
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
NodeCache* Cache::get(int index){
    // Si el indice esta fuera del rango devuelve una excepcion
    if (index < 0 || index >= size) throw out_of_range("index_out_of_range");
    NodeCache *temp = head;
    // Recorrer la lista hasta el indice indicado
    for (int i = 0; i < index; i++){
        temp = temp->get_next();
    } // Contar un acceso al nodo
    temp->count_accessed();
    return temp;
}

// Obtener un nodo por la llave
NodeCache *Cache::get(string key){
    if (size == 1 && head->get_key() == key) return head;
    NodeCache *temp = head;
    // Recorrer la lista hasta que ya no hayan nodos
    while (temp->get_next() != NULL){
        // Si se encuentra el elemento se retorna
        if (temp->get_key() == key) {
            temp->count_accessed();
            return temp;
        } temp = temp->get_next();
    } // Si no se encuentra el elemento se devuelve una exception
    temp = NULL;
    delete temp;
    throw string("key_doesnt_exist");
}

// Obtener el size de la lista
int Cache::get_size(){
   return size;
}

// Remover un nodo por la llave
void Cache::remove(string key){
    if (size == 0) throw string("key_doesnt_exist");
    NodeCache *temp = head;
    // Si el primer nodo es el que se quiere eliminar
    if (head->get_key() == key) {
        head = head->get_next();
    } else {
        bool finded = false;
        NodeCache *aux = NULL;
        // Recorrer la lista hasta que ya no hayan nodos
        while (temp != NULL) {
            // Si se encuentra el elemento se elimina
            if (temp->get_key() == key) {
                aux->set_next(temp->get_next());
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
    } delete temp;
    size--;
}

// Remover un nodo por la llave
void Cache::remove_unless() {
    string key = head->get_key();
    int minor = head->get_accessed();
    NodeCache *temp = NULL;
    for (int i = 1; i < MAX; ++i) {
        NodeCache *temp = get(i);
        if (temp->get_accessed() < minor){
            key = temp->get_key();
            minor = temp->get_accessed();
        }
    } temp = head;
    // Si el primer nodo es el que se quiere eliminar
    if (head->get_key() == key) {
        head = head->get_next();
    } else {
        NodeCache *aux = NULL;
        // Recorrer la lista hasta que ya no hayan nodos
        while (temp != NULL) {
            // Si se encuentra el elemento se elimina
            if (temp->get_key() == key) {
                aux->set_next(temp->get_next());
                break;
            }
            aux = temp;
            temp = temp->get_next();
        }
        aux = NULL;
        delete aux;
    }
    delete temp;
    size--;
}
