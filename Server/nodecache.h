/**
 * @file node.h
 * @brief Contains a set of methods for handling Nodes.
 * @author Erick Andres Obregon Fonseca.
 */

#ifndef NODECACHE_H
#define NODECACHE_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief The Node class.
 */
class NodeCache {
private:
    //! @brief Pointer to the next node.
    NodeCache *next;
    //! @brief Pointer to store datas.
    string data;
    //! @brief Key to indetify nodes.
    string key;
    //! @brief Count access.
    int accessed;

public:
    /**
     * @brief Count a new access to this node.
     */
    void count_accessed();
    /**
     * @brief Constuctor.
     * @param data - data to store.
     * @param key - key to identify this node.
     */
    NodeCache(string data, string key);
    /**
     * @brief Destructor.
     */
    ~NodeCache();
    /**
     * @brief Return how many accessed have had this node.
     * @return how many accessed have had this node.
     */
    int get_accessed();
    /**
     * @brief Returns the data stores in this node.
     * @return data in this node.
     */
    string get_data();
    /**
     * @brief Returns the key to identify this node.
     * @return key to identify this node.
     */
    string get_key();
    /**
     * @brief Returns a pointer to the next node.
     * @return pointer to the next node.
     */
    NodeCache* get_next();
    /**
     * @brief Set the new data to store in this node.
     * @param data - the new data to store.
     */
    void set_data(string data);
    /**
     * @brief Set the new key to identify this node.
     * @param key - the new key to identify this node.
     */
    void set_key(string key);
    /**
     * @brief Set the new next node to this node.
     * @param next - the new next node.
     */
    void set_next(NodeCache *next);
    /**
     * @brief Overload of the output operator.
     * @param output - pointer to the output.
     * @param node - the node to show.
     * @return the output of the contain of this node.
     */
    friend ostream &operator << (ostream &output, const NodeCache &node) {
        output << "{" << node.key << ":" << node.data << "}";
        return output;
    }
    /**
     * @brief Overload of the comparison operator.
     *        Compare if two nodes are equal.
     * @param node - node wich it is compared.
     * @return true or false.
     */
    bool operator == (const NodeCache &node) {
        if (data == node.data && key == node.key) return true;
        return false;
    }
    /**
     * @brief Overload of the different operator.
     *        Compare if two nodes are different.
     * @param node - node wich it is compared.
     * @return true or false.
     */
    bool operator != (const NodeCache &node) {
        if (data == node.data && key == node.key) return false;
        return true;
    }
    /**
     * @brief Copy the information from a node to other.
     * @param node - node with the information to copy.
     */
    void operator = (const NodeCache &node){
        data = node.data;
        key = node.key;
    }
};

#endif // NODECACHE_H
