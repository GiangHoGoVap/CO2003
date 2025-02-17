#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

template <class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node *pLeft, *pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node *walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }

    // STUDENT ANSWER BEGIN
    bool isValid(Node *root, long long top, long long bottom)
    {
        if (root == NULL)
            return true;
        if (root->value < bottom)
            return false;
        if (root->value >= top)
            return false;
        return isValid(root->pLeft, root->value, bottom) &&
               isValid(root->pRight, top, root->value);
    }

    bool isBST()
    {
        // TODO: return true if a tree is a BST; otherwise, return false.
        if (root == NULL)
            return true;
        if (root->pLeft == NULL && root->pRight == NULL)
            return true;
        return isValid(root, INT8_MAX, INT8_MIN);
    }
    // STUDENT ANSWER END
};

int main()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4);  // Add to root
    binaryTree.addNode("L", 3, 2); // Add to root's left node
    binaryTree.addNode("R", 5, 9); // Add to root's right node
    cout << binaryTree.isBST();
}