#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template <class T>
class BinarySearchTree
{
public:
    class Node;

private:
    Node *root;

    Node *insert(Node *&root, T val)
    {
        if (root == NULL)
        {
            root = new Node(val);
            return root;
        }
        if (val <= root->value)
            root->pLeft = insert(root->pLeft, val);
        else
            root->pRight = insert(root->pRight, val);
        return root;
    }

    Node *remove(Node *&root, T val)
    {
        if (root == NULL)
            return root;
        else if (val < root->value)
            root->pLeft = remove(root->pLeft, val);
        else if (val > root->value)
            root->pRight = remove(root->pRight, val);
        else
        {
            if (root->pLeft == NULL)
                root = root->pRight;
            else if (root->pRight == NULL)
                root = root->pLeft;
            else
            {
                Node *dltPtr = root->pRight;
                while (dltPtr->pLeft != NULL)
                {
                    dltPtr = dltPtr->pLeft;
                }
                root->value = dltPtr->value;
                root->pRight = remove(root->pRight, dltPtr->value);
            }
        }
        return root;
    }

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping function

    void add(T value)
    {
        //TODO
        insert(root, value);
    }

    void deleteNode(T value)
    {
        //TODO
        remove(root, value);
    }
    string inOrderRec(Node *root)
    {
        stringstream ss;
        if (root != nullptr)
        {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }

    string inOrder()
    {
        return inOrderRec(this->root);
    }

    class Node
    {
    private:
        T value;
        Node *pLeft, *pRight;
        friend class BinarySearchTree<T>;

    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};

int main()
{
    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(10);
    bst.add(8);
    cout << bst.inOrder() << endl;
    bst.add(11);
    bst.deleteNode(9);
    cout << bst.inOrder();
}