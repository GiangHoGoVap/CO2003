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
    Node *search(Node *root, T val)
    {
        while (root != NULL && root->value != val)
        {
            if (val < root->value)
                return search(root->pLeft, val);
            else if (val > root->value)
                return search(root->pRight, val);
        }
        return root;
    }

    bool find(T i)
    {
        // TODO: return true if value i is in the tree; otherwise, return false.
        if (search(root, i) == NULL)
            return false;
        else
            return true;
    }

    T rangeSum(Node *root, T left, T right)
    {
        if (root == NULL)
            return 0;
        else if (root->value >= left && root->value <= right)
        {
            return root->value = root->value + rangeSum(root->pLeft, left, right) + rangeSum(root->pRight, left, right);
        }
        else
            return rangeSum(root->pLeft, left, right) + rangeSum(root->pRight, left, right);
    }

    T sum(T l, T r)
    {
        // TODO: return the sum of all element in the tree has value in range [l,r].
        T ans = rangeSum(root, l, r);
        return ans;
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
    cout << bst.find(7) << endl;
    cout << bst.sum(0, 4) << endl;
}