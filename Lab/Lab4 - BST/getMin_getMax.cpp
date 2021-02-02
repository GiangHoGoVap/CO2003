#include <iostream>
#include <string>
#include <sstream>

using namespace std;

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

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
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
    Node *addRec(Node *root, T value);
    void add(T value)
    {
        insert(root, value);
    }
    // STUDENT ANSWER BEGIN
    T getMin()
    {
        //TODO: return the minimum values of nodes in the tree.
        if (root == NULL)
            return 0;
        Node *temp = root;
        while (temp->pLeft != NULL)
        {
            temp = temp->pLeft;
        }
        return temp->value;
    }

    T getMax()
    {
        //TODO: return the maximum values of nodes in the tree.
        if (root == NULL)
            return 0;
        Node *temp = root;
        while (temp->pRight != NULL)
        {
            temp = temp->pRight;
        }
        return temp->value;
    }
    // STUDENT ANSWER END
};

int main()
{
    BinarySearchTree<int> bst;
    for (int i = 0; i < 10; ++i)
    {
        bst.add(i);
    }
    cout << bst.getMin() << endl;
    cout << bst.getMax() << endl;
}