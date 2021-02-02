#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
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
        int l = (int)posFromRoot.length();
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

    //Helping functions
    int maxDepth(Node *root)
    {
        if (root == NULL)
            return 0;
        int l = maxDepth(root->pLeft);
        int r = maxDepth(root->pRight);
        return max(l, r) + 1;
    }

    int diameter(Node *root)
    {
        if (root == NULL)
            return 0;
        int ld = diameter(root->pLeft);
        int rd = diameter(root->pRight);
        return max(ld, rd);
    }

    int getDiameter()
    {
        //TODO
        if (root == NULL)
            return 0;
        int left_height = maxDepth(root->pLeft);
        int right_height = maxDepth(root->pRight);
        int ans = max(left_height + right_height + 1, diameter(root));
        return ans;
    }
};

int main()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 1, 4);
    binaryTree.addNode("L", 2, 6);
    binaryTree.addNode("R", 3, 9);
    binaryTree.addNode("LL", 4, 10);
    cout << binaryTree.getDiameter();
}