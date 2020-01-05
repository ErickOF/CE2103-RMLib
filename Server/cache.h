/**
 * @file cache.h
 * @brief Contains a set of methods for handling cache.
 * @author Erick Andres Obregon Fonseca.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/**
  * Maximun nodes in cache
  */
#define MAX 5

#include "nodecache.h"
#include <stdexcept>
#include <string>

using namespace std;

/**
 * @brief The Cache class.
 */
class Cache {
    private:
        //! @brief Header of the cache.
        NodeCache *head;
        //! @brief Number of nodes in cache.
        int size;
    public:
        /**
         * @brief Constructor.
         */
        Cache();
        /**
         * @brief Destructor.
         */
        ~Cache();
        /**
         * @brief Appends the specified node to the end of this cache.
         * @throw string - if the key already exists.
         * @param data - data to store.
         * @param key - key as identifier of node.
         */
        void add(string data, string key);
        /**
         * @brief Verify if the key is in cache.
         * @param key - key as identifier of node.
         * @return true or false
         */
        bool exist(string key);
        /**
         * @brief Returns the node at the specified position in this cache.
         * @throw out_of_range - if the index is out of range (index < 0 || index >= size()).
         * @param index - index of the node to return.
         * @return the node at the specified position in this cache.
         */
        NodeCache* get(int index);
        /**
         * @brief Returns the node with the specified key in this cache.
         * @throw exception - if the key is not found.
         * @param key - key of the node to search for.
         * @return the node with the specified key in this cache.
         */
        NodeCache* get(string key);
        /**
         * @brief Returns the number of nodes in this cache.
         * @return the number of nodes in this cache.
         */
        int get_size();
        /**
         * @brief Removes the node with the specified key in this cache.
         * @throw exception - if the key is not found.
         * @param key - key of the node to remove for.
         */
        void remove(string key);
        /**
         * @brief Remove the least referenced node.
         */
        void remove_unless();
        /**
         * @brief operator []
         * @throw out_of_range - if the index is out of range (index < 0 || index >= size()).
         * @param index - index of the node to return.
         * @return the node at the specified position in this cache.
         */
        NodeCache* operator[](int index){
            return get(index);
        }
        /**
         * @brief Overload of the subscript operator.
         * @throw exception - if the key is not found.
         * @param key - key of the node to search for.
         * @return the node with the specified key in this cache.
         */
        NodeCache* operator [](string key){
            return get(key);
        }
};

#endif // LINKEDLIST_H
