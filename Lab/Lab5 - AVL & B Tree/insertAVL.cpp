#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template <class T>
class AVLTree
{
public:
    class Node;

private:
    Node *root;

protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

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
    for (int i = 0; i < 9; i++)
    {
        avl.insert(i);
    }
    avl.printTreeStructure();
}