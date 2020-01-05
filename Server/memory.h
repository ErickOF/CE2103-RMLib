/**
 * @file linkedlist.h
 * @brief Contains a set of methods for handling linked lists.
 * @author Erick Andres Obregon Fonseca.
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "nodememory.h"
#include <stdexcept>
#include <string>

using namespace std;

/**
 * @brief The Memory class
 */
class Memory {
    private:
        //! @brief Header of the linked list.
        NodeMemory *head;
        //! @brief Number of nodes in the linked list.
        int size;
    public:
        /**
         * @brief Constructor.
         */
        Memory();
        /**
         * @brief Destructor.
         */
        ~Memory();
        /**
         * @brief Appends the specified node to the end of this list.
         * @throw string - if the key already exists.
         * @param data - data to store.
         * @param key - key as identifier of node.
         */
        void add(string data, string key);
        /**
         * @brief Verify if the key is this list.
         * @param key - key as identifier of node.
         * @return true or false
         */
        bool exist(string key);
        /**
         * @brief Returns the node at the specified position in this list.
         * @throw out_of_range - if the index is out of range (index < 0 || index >= size()).
         * @param index - index of the node to return.
         * @return the node at the specified position in this list.
         */
        NodeMemory* get(int index);
        /**
         * @brief Returns the node with the specified key in this list.
         * @throw exception - if the key is not found.
         * @param key - key of the node to search for.
         * @return the node with the specified key in this list.
         */
        NodeMemory* get(string key);
        /**
         * @brief Returns the number of elements in this list.
         * @return the number of elements in this list.
         */
        int get_size();
        /**
         * @brief Removes the element at the specified position in this list.
         * @throw out_of_range - if the index is out of range (index < 0 || index >= size()).
         * @param index - the index of the element to be removed.
         */
        void remove(int index);
        /**
         * @brief Removes the element witht the specified key in this list.
         * @throw exception - if the key is not found.
         * @param key - key of the node to remove for.
         */
        void remove(string key);
        /**
         * @brief operator []
         * @throw out_of_range - if the index is out of range (index < 0 || index >= size()).
         * @param index - index of the node to return.
         * @return the node at the specified position in this cache.
         */
        NodeMemory* operator[](int index){
            return get(index);
        }
        /**
         * @brief Overload of the subscript operator.
         * @throw exception - if the key is not found.
         * @param key - key of the node to search for.
         * @return the node with the specified key in this cache.
         */
        NodeMemory* operator [](string key){
            return get(key);
        }
};

#endif // MEMORY_H
