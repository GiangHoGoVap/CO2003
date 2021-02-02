#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

class BusParking
{

public:
    class Node
    {
    public:
        Node *right;
        Node *left;
        Node *parent;
        int key;
        int sign;
        int sum;
        int res, lmax, rmax;
        bool isRed;
        int intervalID;

    public:
        Node(int key, int sign, int ID)
        {
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
            this->key = key;
            this->isRed = false;
            this->sign = sign;
            this->intervalID = ID;
            this->sum = 0;
            this->res = 1;
            this->lmax = 0;
            this->rmax = 0;
        }
    };

public:
    class RBTree
    {
    public:
        Node *root;
        Node *replacingNode;
        Node *siblingNode;

    private:
        void leftRotate(Node *x)
        {
            if (x->right)
            {
                Node *y = x->right;
                x->right = y->left;
                if (y->left != NULL)
                    y->left->parent = x;
                y->parent = x->parent;
                if (x->parent == NULL)
                    this->root = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    x->parent->right = y;
                y->left = x;
                x->parent = y;
                update(x);
                update(y);
            }
        }
        void rightRotate(Node *x)
        {
            if (x->left)
            {
                Node *y = x->left;
                x->left = y->right;
                if (y->right != NULL)
                    y->right->parent = x;
                y->parent = x->parent;
                if (x->parent == NULL)
                    this->root = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    x->parent->right = y;
                y->right = x;
                x->parent = y;
                update(x);
                update(y);
            }
        }
        void RBInsertFixup(Node *newNode)
        {
            while (newNode->parent && newNode->parent->isRed)
            {
                if (newNode->parent->parent && (newNode->parent == newNode->parent->parent->left))
                {
                    Node *y = newNode->parent->parent->right;
                    if (y && y->isRed)
                    {
                        newNode->parent->isRed = false;
                        y->isRed = false;
                        newNode->parent->parent->isRed = true;
                        newNode = newNode->parent->parent;
                    }
                    else
                    {
                        if (newNode == newNode->parent->right)
                        {
                            newNode = newNode->parent;
                            leftRotate(newNode);
                        }
                        newNode->parent->isRed = false;
                        newNode->parent->parent->isRed = true;
                        rightRotate(newNode->parent->parent);
                    }
                }
                else
                {
                    if (newNode->parent->parent == NULL)
                        break;
                    Node *y = newNode->parent->parent->left;
                    if (y && y->isRed)
                    {
                        newNode->parent->isRed = false;
                        y->isRed = false;
                        newNode->parent->parent->isRed = true;
                        newNode = newNode->parent->parent;
                    }
                    else
                    {
                        if (newNode == newNode->parent->left)
                        {
                            newNode = newNode->parent;
                            rightRotate(newNode);
                        }
                        newNode->parent->isRed = false;
                        newNode->parent->parent->isRed = true;
                        leftRotate(newNode->parent->parent);
                    }
                }
            }
            this->root->isRed = false;
        }
        void RBInsert(Node *newNode)
        {
            Node *y = NULL;
            Node *x = this->root;
            while (x)
            {
                y = x;
                if (newNode->key < x->key)
                    x = x->left;
                else
                    x = x->right;
            }
            newNode->parent = y;
            if (y == NULL)
                root = newNode;
            else if (newNode->key < y->key)
                y->left = newNode;
            else
                y->right = newNode;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->isRed = true;
            RBInsertFixup(newNode);
            update(newNode);
            Node *goingUp = y;
            percolateUp(goingUp);
        }
        int calculateSum(Node *x)
        {
            int res;
            if (x != NULL)
            {
                if (x->left == NULL && x->right == NULL)
                {
                    res = x->sign;
                }
                else if (x->left && !x->right)
                {
                    res = x->sign + x->left->sum;
                }
                else if (x->right && !x->left)
                {
                    res = x->sign + x->right->sum;
                }
                else
                    res = x->sign + x->left->sum + x->right->sum;
            }
            return res;
        }
        int calculateRes(Node *x)
        {
            int res;
            if (x != NULL)
            {
                if (x->left == NULL && x->right == NULL)
                {
                    res = max(0, x->sum);
                }
                else if (x->left && !x->right)
                {
                    res = max(x->left->res, x->rmax);
                }
                else if (x->right && !x->left)
                {
                    res = max(x->right->res, x->lmax);
                }
                else
                    res = max(max(x->left->res, x->right->res), x->left->rmax + x->right->lmax + x->sign);
            }
            return res;
        }
        void update(Node *x)
        {
            if (x != NULL)
            {
                if (x->left == NULL && x->right == NULL)
                {
                    x->sum = calculateSum(x);
                    x->lmax = x->rmax = max(0, x->sum);
                    x->res = calculateRes(x);
                }
                else if (x->left && !x->right)
                {
                    x->sum = calculateSum(x);
                    x->lmax = max(x->left->lmax, x->sum);
                    x->rmax = max(x->left->rmax + x->sign, 0);
                    x->res = calculateRes(x);
                }
                else if (x->right && !x->left)
                {
                    x->sum = calculateSum(x);
                    x->lmax = max(x->right->lmax + x->sign, 0);
                    x->rmax = max(x->right->rmax, x->sum);
                    x->res = calculateRes(x);
                }
                else
                {
                    x->sum = calculateSum(x);
                    x->lmax = max(x->left->lmax, x->left->sum + x->sign + x->right->lmax);
                    x->rmax = max(x->right->rmax, x->right->sum + x->sign + x->left->rmax);
                    x->res = calculateRes(x);
                }
            }
        }
        void percolateUp(Node *v)
        {
            while (v != NULL)
            {
                update(v);
                v = v->parent;
            }
        }
        void transplant(Node *oldNode, Node *newNode)
        {
            if (oldNode == root)
                root = newNode;
            else if (oldNode == oldNode->parent->left)
                oldNode->parent->left = newNode;
            else
                oldNode->parent->right = newNode;
            if (newNode != NULL)
                newNode->parent = oldNode->parent;
            update(newNode);
        }
        Node *TreeMinimum(Node *begin)
        {
            Node *retNode = begin;
            Node *traverse = begin;
            while (traverse)
            {
                retNode = traverse;
                traverse = traverse->left;
            }
            return retNode;
        }
        void RBDelete(Node *node)
        {
            Node *temp = node;
            Node *replace = NULL;
            bool originalIsRed = temp->isRed;
            bool rep = false;
            if (node->left == NULL)
            {
                replace = node->right;
                if (!replace)
                {
                    if (node == root)
                    {
                        root = NULL;
                        return;
                    }
                    rep = true;
                    replace = new Node(0, 0, 0);
                    this->replacingNode = replace;
                    replace->isRed = false;
                    replace->parent = node;
                    replace->parent->right = replace;
                }
                transplant(node, node->right);
            }
            else if (node->right == NULL)
            {
                replace = node->left;
                transplant(node, node->left);
            }
            else
            {
                temp = TreeMinimum(node->right);
                originalIsRed = temp->isRed;
                replace = temp->right;
                if (!replace)
                {
                    rep = true;
                    replace = new Node(0, 0, 0);
                    this->replacingNode = replace;
                    replace->isRed = false;
                    replace->parent = temp;
                    replace->parent->right = replace;
                }
                if (temp->parent == node)
                {
                    replace->parent = temp;
                }
                else
                {
                    transplant(temp, temp->right);
                    temp->right = node->right;
                    temp->right->parent = temp;
                }
                transplant(node, temp);
                temp->left = node->left;
                temp->left->parent = temp;
                temp->isRed = node->isRed;
            }
            if (originalIsRed == false)
                RBDeleteFixup(replace, rep);
            if (rep)
            {
                rep = false;
                if (!replacingNode->parent)
                    delete replacingNode;
                else if (replacingNode->parent->left == replacingNode)
                {
                    replacingNode->parent->left = NULL;
                    delete replacingNode;
                }
                else if (replacingNode->parent->right == replacingNode)
                {
                    replacingNode->parent->right = NULL;
                    delete replacingNode;
                }
            }
            Node *goingUp = replace;
            percolateUp(goingUp);
        }
        void RBDeleteFixup(Node *node, bool rep)
        {
            Node *sibling = NULL;
            bool siblingChange = false;
            bool replaceChange = rep;
            while (node != root && !node->isRed)
            {
                if (node == node->parent->left)
                {
                    sibling = node->parent->right;
                    if (!sibling)
                    {
                        siblingChange = true;
                        sibling = new Node(0, 0, 0);
                        this->siblingNode = sibling;
                        sibling->parent = node->parent;
                        sibling->isRed = false;
                        node->parent->right = sibling;
                    }
                    if (sibling->isRed)
                    {
                        sibling->isRed = false;
                        node->parent->isRed = true;
                        leftRotate(node->parent);
                        sibling = node->parent->right;
                    }
                    if ((!sibling->left || !sibling->left->isRed) && (!sibling->right || !sibling->right->isRed))
                    {
                        sibling->isRed = true;
                        node = node->parent;
                    }
                    else
                    {
                        if (!sibling->right || !sibling->right->isRed)
                        {
                            if (sibling->left)
                                sibling->left->isRed = false;
                            sibling->isRed = true;
                            rightRotate(sibling);
                            sibling = node->parent->right;
                        }
                        sibling->isRed = node->parent->isRed;
                        node->parent->isRed = false;
                        sibling->right->isRed = false;
                        leftRotate(node->parent);
                        node = root;
                    }
                }
                else
                {
                    sibling = node->parent->left;
                    if (!sibling)
                    {
                        siblingChange = true;
                        sibling = new Node(0, 0, 0);
                        this->siblingNode = sibling;
                        sibling->parent = node->parent;
                        sibling->isRed = false;
                        node->parent->left = sibling;
                    }
                    if (sibling->isRed)
                    {
                        sibling->isRed = false;
                        node->parent->isRed = true;
                        rightRotate(node->parent);
                        sibling = node->parent->left;
                    }
                    if ((!sibling->right || !sibling->right->isRed) && (!sibling->left || !sibling->left->isRed))
                    {
                        sibling->isRed = true;
                        node = node->parent;
                    }
                    else
                    {
                        if (!sibling->left || !sibling->left->isRed)
                        {
                            if (sibling->right)
                                sibling->right->isRed = false;
                            sibling->isRed = true;
                            leftRotate(sibling);
                            sibling = node->parent->left;
                        }
                        sibling->isRed = node->parent->isRed;
                        node->parent->isRed = false;
                        sibling->left->isRed = false;
                        rightRotate(node->parent);
                        node = root;
                    }
                }
                if (replaceChange)
                {
                    replaceChange = false;
                    if (!replacingNode->parent)
                        delete replacingNode;
                    else if (replacingNode->parent->left == replacingNode)
                    {
                        replacingNode->parent->left = NULL;
                        delete replacingNode;
                    }
                    else if (replacingNode->parent->right == replacingNode)
                    {
                        replacingNode->parent->right = NULL;
                        delete replacingNode;
                    }
                }
                if (siblingChange)
                {
                    siblingChange = false;
                    if (!siblingNode->parent)
                    {
                        delete siblingNode;
                    }
                    else if (siblingNode->parent->left == siblingNode)
                    {
                        siblingNode->parent->left = NULL;
                        delete siblingNode;
                    }
                    else if (siblingNode->parent->right == siblingNode)
                    {
                        siblingNode->parent->right = NULL;
                        delete siblingNode;
                    }
                }
            }
            update(node);
            if (node)
                node->isRed = false;
        }

    public:
        RBTree()
        {
            root = NULL;
        }
        void insert(Node *newNode)
        {
            RBInsert(newNode);
        }
        void removal(Node *deleteNode)
        {
            RBDelete(deleteNode);
        }
    };

private:
    RBTree *rbtree;
    int intervalID;
private:
    void findID(Node* node, int ID, queue<Node*>* toDelete){
        if (node == NULL) return;
        else {
            if (node->intervalID == ID){
                toDelete->push(node);
            } 
            findID(node->left, ID, toDelete);
            findID(node->right, ID, toDelete);
        }
    }

public:
    BusParking()
    {
        this->rbtree = new RBTree;
        this->intervalID = 1;
    }
    void add(int s, int t)
    {
        if (s >= t)
            return;
        this->intervalID = s*10 + t;
        Node *newNode1 = new Node(s, 1, this->intervalID);
        Node *newNode2 = new Node(t, -1, this->intervalID);
        rbtree->insert(newNode1);
        rbtree->insert(newNode2);
    }
    void remove(int s, int t)
    {
        if (s >= t)
            return;
        queue<Node*>* toDelete = new queue<Node*>;
        this->intervalID = s*10 + t;
        findID(rbtree->root, intervalID, toDelete);
        if (toDelete->size() == 0)
            return;
        else
        {
            rbtree->removal(toDelete->front());
            toDelete->pop();
            rbtree->removal(toDelete->front());
        }
    }
    int minPark()
    {
        return rbtree->root->res;
    }
};

int main()
{
    BusParking *b = new BusParking;
    b->add(1, 6);
    b->add(2, 5);
    //b->add(3, 5);
    //b->add(4, 6);
    //b->add(3, 6);
    b->remove(2, 6);
    cout << "MinPark is: " << b->minPark() << endl;
}
