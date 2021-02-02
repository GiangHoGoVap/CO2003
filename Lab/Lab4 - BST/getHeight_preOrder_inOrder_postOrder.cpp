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
    int maxDepth(Node *root)
    {
        if (root == NULL)
            return 0;
        int l = maxDepth(root->pLeft);
        int r = maxDepth(root->pRight);
        return max(l, r) + 1;
    }

    int getHeight()
    {
        // TODO: return height of the binary tree.
        return maxDepth(root);
    }

    string printPreOrder(Node *root)
    {
        stringstream ss;
        if (root)
        {
            ss << root->value << " ";
            ss << printPreOrder(root->pLeft);
            ss << printPreOrder(root->pRight);
        }
        return ss.str();
    }

    string preOrder()
    {
        // TODO: return the sequence of values of nodes in pre-order.
        return printPreOrder(root);
    }

    string printInOrder(Node *root)
    {
        stringstream ss;
        if (root)
        {
            ss << printInOrder(root->pLeft);
            ss << root->value << " ";
            ss << printInOrder(root->pRight);
        }
        return ss.str();
    }

    string inOrder()
    {
        // TODO: return the sequence of values of nodes in in-order.
        return printInOrder(root);
    }

    string printPostOrder(Node *root)
    {
        stringstream ss;
        if (root)
        {
            ss << printPostOrder(root->pLeft);
            ss << printPostOrder(root->pRight);
            ss << root->value << " ";
        }
        return ss.str();
    }

    string postOrder()
    {
        // TODO: return the sequence of values of nodes in post-order.
        return printPostOrder(root);
    }
    // STUDENT ANSWER END
};

int main()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4);  // Add to root
    binaryTree.addNode("L", 3, 6); // Add to root's left node
    binaryTree.addNode("R", 5, 9); // Add to root's right node
    cout << binaryTree.getHeight() << endl;
    cout << binaryTree.preOrder() << endl;
    cout << binaryTree.inOrder() << endl;
    cout << binaryTree.postOrder() << endl;
}