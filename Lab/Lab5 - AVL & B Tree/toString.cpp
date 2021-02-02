#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class K, class D, int M> // K: key, D: data, M: degree of BTree
class BTree
{
    /// Convention: Left sub-tree < Root's key <= Right sub-tree

public:
    class Entry;
    class Node;

private:
    Node *root;

public:
    BTree() : root(0){};
    ~BTree() {}

    ///////////////////////////////////////////////////
    ///             CLASS `Entry`                   ///
    ///////////////////////////////////////////////////
public:
    class Entry
    {
    private:
        K key;
        D data;
        Node *rightPtr;

        friend class BTree<K, D, M>;

    public:
        Entry(K key = K{}, D value = D{}) : key(key), data(value), rightPtr(0) {}
        ~Entry() {}

        string toString()
        {
            stringstream ss;
            ss << "<"
               << this->key << ","
               << this->data
               << ">";
            return ss.str();
        }
    };

    ///////////////////////////////////////////////////
    ///             CLASS `Node`                    ///
    ///////////////////////////////////////////////////
public:
    class Node
    {
    private:
        Node *firstPtr;
        int numEntries;
        Entry entries[M - 1];

        friend class BTree<K, D, M>;

    public:
        Node() : firstPtr(0), numEntries(0){};
        ~Node() {}

        bool isFull()
        {
            return (numEntries >= M - 1);
        }

        /// BEGIN STUDENT CODE
        string toString()
        {
            stringstream ss;
            // Fill your code here
            ss << "["
               << "(" << numEntries << ")";
            for (int idx = 0; idx < numEntries; idx++)
            {
                ss << entries[idx].toString();
            }
            ss << "]";
            return ss.str();
        }
        /// END STUDENT CODE
    };

    /////////////////////////////////////////////////////////////
    ///         CLASS `BTree`: method run sample test         ///
    /////////////////////////////////////////////////////////////
    void testPrintNode(K *keys, D *data, int size)
    {
        Node node;

        for (int idx = 0; idx < size; idx++)
        {
            node.entries[idx].key = keys[idx];
            node.entries[idx].data = data[idx];
        }
        node.numEntries = size;
        cout << node.toString() << endl;
    }
};

int main()
{
    int keys[] = {3, 5, 7};
    int data[] = {33, 55, 77};
    int size = sizeof(keys) / sizeof(int);
    BTree<int, int, 5>().testPrintNode(keys, data, size);
}