#include <iostream>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

template <class T>
class AVLTree
{
public:
    class Node;

private:
    Node *root;

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}

    Node *rotateRight(Node *&root)
    {
        Node *temp = root->pLeft;
        root->pLeft = temp->pRight;
        temp->pRight = root;
        return temp;
    }

    Node *rotateLeft(Node *&root)
    {
        Node *temp = root->pRight;
        root->pRight = temp->pLeft;
        temp->pLeft = root;
        return temp;
    }

    //Left subtree is higher than the right subtree
    Node *&leftBalance(Node *&root, bool &taller)
    {
        Node *leftTree = root->pLeft;
        //Left Left case
        if (leftTree->balance == LH)
        {
            //slide sai thu tu
            root->balance = EH;
            leftTree->balance = EH;
            root = rotateRight(root);
            taller = false;
        }
        else
        {
            //Left right case
            Node *rightTree = leftTree->pRight;
            if (rightTree->balance == LH)
            {
                root->balance = RH;
                leftTree->balance = EH;
            }
            else if (rightTree->balance == EH)
            {
                //slide thieu
                root->balance = EH;
                leftTree->balance = EH;
            }
            else
            {
                root->balance = EH;
                leftTree->balance = LH;
            }
            rightTree->balance = EH;
            root->pLeft = rotateLeft(leftTree);
            root = rotateRight(root);
            taller = false;
        }
        return root;
    }

    //Right subtree is higher than the left subtree
    Node *&rightBalance(Node *&root, bool &taller)
    {
        Node *rightTree = root->pRight;
        //right right case
        if (rightTree->balance == RH)
        {
            root->balance = EH;
            rightTree->balance = EH;
            root = rotateLeft(root);
            taller = false;
        }
        else
        {
            //right left case
            Node *leftTree = rightTree->pLeft;
            if (leftTree->balance == RH)
            {
                root->balance = LH;
                rightTree->balance = EH;
            }
            else if (leftTree->balance == EH)
            {
                //slide thieu
                root->balance = EH;
                rightTree->balance = EH;
            }
            else
            {
                root->balance = EH;
                rightTree->balance = RH;
            }
            leftTree->balance = EH;
            root->pRight = rotateRight(rightTree);
            root = rotateLeft(root);
            taller = false;
        }
        return root;
    }

    Node *insert(Node *&root, const T &insertValue, bool &taller)
    {
        if (root == NULL)
        {
            root = new Node(insertValue);
            taller = true;
            return root;
        }
        if (insertValue < root->data)
        {
            root->pLeft = insert(root->pLeft, insertValue, taller);
            //left subtree is taller
            if (taller)
            {
                if (root->balance == LH)
                    root = leftBalance(root, taller);
                else if (root->balance == EH)
                    root->balance = LH;
                else
                {
                    root->balance = EH;
                    taller = false;
                }
            }
        }
        else //slide sai
        {
            root->pRight = insert(root->pRight, insertValue, taller);
            //right subtree is taller
            if (taller)
            {
                if (root->balance == RH)
                    root = rightBalance(root, taller);
                else if (root->balance == EH)
                    root->balance = RH;
                else
                {
                    root->balance = EH;
                    taller = false;
                }
            }
        }
        return root;
    }

    void insert(const T &value)
    {
        bool taller = true;
        insert(this->root, value, taller);
    }

    Node *searchAVL(Node *root, const T &value)
    {
        if (root == NULL)
            return NULL;
        if (value == root->data)
            return root;
        else if (value < root->data)
            return searchAVL(root->pLeft, value);
        else
            return searchAVL(root->pRight, value);
    }

    bool search(const T &value)
    {
        Node *tmp = searchAVL(root, value);
        if (tmp)
            return true;
        else
            return false;
    }

    void inorder(Node *root)
    {
        if (root != NULL)
        {
            inorder(root->pLeft);
            cout << root->data << " ";
            inorder(root->pRight);
        }
    }

    void printInorder()
    {
        inorder(root);
    }

    void clearTree(Node *&root)
    {
        if (root == NULL)
            return;
        clearTree(root->pLeft);
        clearTree(root->pRight);
        delete root;
        root = NULL;
    }

    void clear()
    {
        clearTree(root);
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

int main()
{
    AVLTree<int> avl;
    int arr[] = {10, 52, 98, 32, 68, 92, 40, 13, 42, 63, 99, 100};
    for (int i = 0; i < 12; i++)
    {
        avl.insert(arr[i]);
    }
    avl.printInorder();
    cout << endl;
    cout << avl.search(10);
}