#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

template <class K, class V>
class BKUTree
{
public:
    class AVLTree;
    class SplayTree;

    class Entry
    {
    public:
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {}
    };

private:
    AVLTree *avl;
    SplayTree *splay;
    queue<K> keys;
    int maxNumOfKeys;

public:
    BKUTree(int maxNumOfKeys = 5)
    {
        this->maxNumOfKeys = maxNumOfKeys;
        avl = new AVLTree;
        splay = new SplayTree;
    }
    ~BKUTree()
    {
        this->clear();
        delete avl;
        delete splay;
    }

    bool isFull()
    {
        return keys.size() == (unsigned int)maxNumOfKeys;
    }

    void add(K key, V value)
    {
        if (isFull())
        {
            keys.pop();
        }
        keys.push(key);
        Entry *entry = new Entry(key, value);
        typename AVLTree::Node *node1 = avl->addBKU(entry);
        typename SplayTree::Node *node2 = splay->addBKU(entry);
        node1->corr = node2;
        node2->corr = node1;
    }

    void remove(K key)
    {
        queue<K> tempor;
        while (!keys.empty())
        {
            if (key != keys.front())
            {
                tempor.push(keys.front());
            }
            keys.pop();
        }
        while (!tempor.empty())
        {
            keys.push(tempor.front());
            tempor.pop();
        }
        if (isFull())
        {
            keys.pop();
        }
        avl->remove(key);
        splay->remove(key);
        keys.push(splay->root->entry->key);
    }

    V search(K key, vector<K> &traversedList)
    {
        V result;
        if (splay->root->entry->key == key)
            return splay->root->entry->value;
        // check if key is in  the queue or not
        bool inQ = false;
        queue<K> list;
        while (keys.empty() == false)
        {
            if (keys.front() == key)
                inQ = true;
            list.push(keys.front());
            keys.pop();
        }
        while (list.empty() == false)
        {
            keys.push(list.front());
            list.pop();
        }
        if (inQ == true) //Keys in queue
        {
            result = splay->searchSplayforBKU(key, traversedList);
        }
        else //Keys not in queue
        {
            bool AVLSubSearch = false; // see if the node is in the AVL subtree
            bool AVLRootSearch = false;
            typename AVLTree::Node *returnAddress = NULL; // store the address of the node you need to find
            typename AVLTree::Node *checkPoint = NULL;    // store the address of the starting node
            //typename AVLTree::Node* alpha = NULL; // alpha = splay->root->corr
            if (splay->root->corr == avl->root)
            { // r = r' = avlroot means we are searching from the root of AVL
              //  cout << "2 roots are the same" << endl;
                result = avl->searchForBKU(key, traversedList, AVLRootSearch, avl->root, returnAddress, checkPoint); // no need to use checkpoint, so checkpoint = NULL
            }
            else
            { // splay->root != avl->root so we perform 2 searching , 1 on sub or 1 on sub and 1 on entrire AVL tree
              // cout<<"2 phases searching"<<endl;
                result = avl->searchForBKU(key, traversedList, AVLSubSearch, splay->root->corr, returnAddress, checkPoint);
                // checkpoint should be the splay->root->corr
                // if key has not been found , we perform search on the whole root
                if (AVLSubSearch == false)
                    result = avl->searchForBKU(key, traversedList, AVLRootSearch, avl->root, returnAddress, checkPoint);
            }
            splay->splayBKU(returnAddress->corr);
        }
        // if its in the keys , then it will be searched , therefore this key is push to the keys
        if (isFull())
            keys.pop();
        keys.push(key);
        return result;
    }

    void traverseNLROnAVL(void (*func)(K key, V value))
    {
        avl->traverseNLR(func);
    }

    void traverseNLROnSplay(void (*func)(K key, V value))
    {
        splay->traverseNLR(func);
    }

    void clear()
    {
        avl->clear();
        splay->clear();
        while (!keys.empty())
        {
            keys.pop();
        }
        delete avl;
        avl = NULL;
        delete splay;
        splay = NULL;
    }

    void checkCorAVL(typename AVLTree::Node *node)
    {
        if (node)
        {
            cout << "AVL node is " << node->entry->key << "      cor is " << node->corr->entry->key << endl;
            checkCorAVL(node->left);
            checkCorAVL(node->right);
        }
    }

    void checkCorAVL()
    {
        return checkCorAVL(avl->root);
    }

    void checkCorS(typename SplayTree::Node *node)
    {
        if (node)
        {
            cout << "Splay node is " << node->entry->key << "      cor is " << node->corr->corr->entry->key << endl;
            checkCorS(node->left);
            checkCorS(node->right);
        }
    }

    void checkCorS()
    {
        return checkCorS(splay->root);
    }

    void checkQ(queue<int> list)
    {

        while (list.empty() == false)
        {
            cout << list.front() << "   ";
            list.pop();
        }
        cout << endl;
    }
    void checkQ()
    {
        return checkQ(keys);
    }

    void printPretty()
    {
        cout << "AVL Tree:" << endl;
        avl->printPretty();
        cout << endl;
        cout << "Splay Tree:" << endl;
        splay->printPretty();
    }

    void printKeys()
    {
        queue<K> tmp = keys;
        while (!tmp.empty())
        {
            cout << '\t' << tmp.front();
            tmp.pop();
        }
        cout << '\n';
    }

    queue<K> copy_queue()
    {
        queue<int> Q2 = this->keys;
        return Q2;
    }

    class SplayTree
    {
    public:
        class Node
        {
        public:
            Entry *entry;
            Node *parent;
            Node *left;
            Node *right;
            typename AVLTree::Node *corr;

            Node(Entry *entry = NULL, Node *parent = NULL, Node *left = NULL, Node *right = NULL)
            {
                this->entry = entry;
                this->parent = parent;
                this->left = left;
                this->right = right;
                this->corr = NULL;
            }
        };

    public:
        void zig(Node *x)
        {
            Node *p = x->parent;
            if (p->left == x)
            {
                Node *xR = x->right;
                x->parent = NULL;
                x->right = p;
                p->parent = x;
                p->left = xR;
                if (xR != NULL)
                    xR->parent = p;
            }
            else
            {
                Node *xL = x->left;
                x->parent = NULL;
                x->left = p;
                p->parent = x;
                p->right = xL;
                if (xL != NULL)
                    xL->parent = p;
            }
        }

        void zig_zig(Node *x)
        {
            Node *p = x->parent;
            Node *g = p->parent;
            if (p->left == x)
            {
                Node *xR = x->right;
                Node *pR = p->right;
                x->parent = g->parent;
                x->right = p;
                p->parent = x;
                p->left = xR;
                p->right = g;
                g->parent = p;
                g->left = pR;
                if (x->parent != NULL)
                {
                    if (x->parent->left == g)
                        x->parent->left = x;
                    else
                        x->parent->right = x;
                }
                if (xR != NULL)
                    xR->parent = p;
                if (pR != NULL)
                    pR->parent = g;
            }
            else
            {
                Node *xL = x->left;
                Node *pL = p->left;
                x->parent = g->parent;
                x->left = p;
                p->parent = x;
                p->right = xL;
                p->left = g;
                g->parent = p;
                g->right = pL;
                if (x->parent != NULL)
                {
                    if (x->parent->left == g)
                        x->parent->left = x;
                    else
                        x->parent->right = x;
                }
                if (xL != NULL)
                    xL->parent = p;
                if (pL != NULL)
                    pL->parent = g;
            }
        }

        void zig_zag(Node *x)
        {
            Node *p = x->parent;
            Node *g = p->parent;
            if (p->left == x)
            {
                Node *xR = x->right;
                Node *xL = x->left;
                x->parent = g->parent;
                x->left = g;
                x->right = p;
                p->parent = x;
                p->left = xR;
                g->parent = x;
                g->right = xL;
                if (x->parent != NULL)
                {
                    if (x->parent->left == g)
                        x->parent->left = x;
                    else
                        x->parent->right = x;
                }
                if (xR != NULL)
                    xR->parent = p;
                if (xL != NULL)
                    xL->parent = g;
            }
            else
            {
                Node *xR = x->right;
                Node *xL = x->left;
                x->parent = g->parent;
                x->left = p;
                x->right = g;
                p->parent = x;
                p->right = xL;
                g->parent = x;
                g->left = xR;
                if (x->parent != NULL)
                {
                    if (x->parent->left == g)
                        x->parent->left = x;
                    else
                        x->parent->right = x;
                }
                if (xR != NULL)
                    xR->parent = g;
                if (xL != NULL)
                    xL->parent = p;
            }
        }
        /*
        void test()
        {
            splayBKU(root->left->left->left->left);
        }
        */
        void splayBKU(Node *&x)
        {
            if (x->parent != NULL)
            {
                Node *p = x->parent;
                Node *g = p->parent;
                if (g == NULL)
                {
                    zig(x);
                }
                else if (g->left == p && p->left == x)
                {
                    zig_zig(x);
                }
                else if (g->right == p && p->right == x)
                {
                    zig_zig(x);
                }
                else
                {
                    zig_zag(x);
                }
            }
            if (x->parent == NULL)
                root = x;
        }

        void splay(Node *&x)
        {
            while (x->parent != NULL)
            {
                Node *p = x->parent;
                Node *g = p->parent;
                if (g == NULL)
                {
                    zig(x);
                }
                else if (g->left == p && p->left == x)
                {
                    zig_zig(x);
                }
                else if (g->right == p && p->right == x)
                {
                    zig_zig(x);
                }
                else
                {
                    zig_zag(x);
                }
            }
            this->root = x;
        }

        void insertSplay(Node *&root, Node *temp)
        {
            if (root == NULL)
            {
                root = temp;
                temp = NULL;
                //root->parent = NULL;
                return;
            }
            Node *cur = this->root;
            while (cur != NULL)
            {
                if (temp->entry->key < cur->entry->key)
                {
                    if (cur->left == NULL)
                    {
                        cur->left = temp;
                        temp->parent = cur;
                        splay(temp);
                        return;
                    }
                    else
                        cur = cur->left;
                }
                else if (temp->entry->key > cur->entry->key)
                {
                    if (cur->right == NULL)
                    {
                        cur->right = temp;
                        temp->parent = cur;
                        splay(temp);
                        return;
                    }
                    else
                        cur = cur->right;
                }
                else
                {
                    splay(cur);
                    return;
                }
            }
        }

        Node *subtree_max(Node *subroot)
        {
            while (subroot->right != NULL)
            {
                subroot = subroot->right;
            }
            return subroot;
        }

        void removeSplay(Node *&root, K key)
        {
            Node *delPtr = searchSplay(root, key);
            if (delPtr == NULL)
            {
                throw "Not found";
                return;
            }
            while (delPtr->parent != NULL)
            {
                splay(delPtr);
            }
            Node *delPtrLeft = delPtr->left;
            Node *delPtrRight = delPtr->right;
            if (delPtrLeft == NULL && delPtrRight == NULL)
            {
                delete delPtr;
                this->root = NULL;
            }
            else if (delPtrLeft == NULL && delPtrRight)
            {
                delPtrRight->parent = delPtr->parent;
                root = delPtrRight;
                delete delPtr;
            }
            else if (delPtrRight == NULL && delPtrLeft)
            {
                delPtrLeft->parent = delPtr->parent;
                root = delPtrLeft;
                delete delPtr;
            }
            else
            {
                delete delPtr;
                delPtrLeft->parent = NULL;
                Node *ans = subtree_max(delPtrLeft);
                splay(ans);
                //ans->right = delPtrRight;
                root = ans;
                root->right = delPtrRight;
                delPtrRight->parent = root;
            }
            //delete delPtr;
        }

        Node *searchSplay(Node *root, K key)
        {
            if (root == NULL)
                return NULL;
            if (key == root->entry->key)
                return root;
            else if (key < root->entry->key)
                return searchSplay(root->left, key);
            else if (key > root->entry->key)
                return searchSplay(root->right, key);
            return root;
        }

        V searchSplayforBKU(K key, vector<K> &list){ // this search is for BKU tree only 
            // search value 
            Node* temp = this->root; 
            while(temp){     // search for the node 
                if(key < temp->entry->key) {
                    list.push_back(temp->entry->key);
               //     cout<<"You just push"<<temp->entry->key<<endl; 
                    temp = temp->left;
                }
                else if (key > temp->entry->key) {
                    list.push_back(temp->entry->key);
                  //  cout<<"You just push"<<temp->entry->key<<endl; 
                    temp = temp->right;
                }
                else break;   // key == temp->key
            }
            if(temp == NULL ) {
                // key not found//
                throw("Not found");

            }
            V result = temp->entry->value;
            /// splay 1 time ;
            splayBKU(temp);
            return result;
        }

        void preorder(Node *root, void (*func)(K key, V value))
        {
            if (root == NULL)
                return;
            else{
                func(root->entry->key, root->entry->value);
                preorder(root->left, func);
                preorder(root->right, func);
            }
        }

        void clearTree(Node *&root)
        {
            if (root == NULL)
                return;
            clearTree(root->left);
            clearTree(root->right);
            delete root;
            root = NULL;
        }

        void prettyPrintTree(Node *_root, string prefix = "", bool isLeft = true)
        {
            if (!_root)
            {
                cout << "Empty tree!\n";
                return;
            }

            if (_root->right)
            {
                prettyPrintTree(_root->right, prefix + (isLeft ? "|   " : "    "), false);
            }

            cout << prefix + (isLeft ? "+-- " : "+-- ") + "<" + to_string(_root->entry->key) + "," + to_string(_root->entry->value) + ">\n";

            if (_root->left)
            {
                prettyPrintTree(_root->left, prefix + (isLeft ? "    " : "|   "), true);
            }
        }

    public:
        Node *root;

        SplayTree() : root(NULL){};
        ~SplayTree() { this->clear(); };

        Node *find(K key)
        {
            Node *tempoo = root;
            while (tempoo != NULL)
            {
                if (tempoo->entry->key == key)
                    return tempoo;
                else if (tempoo->entry->key > key)
                    tempoo = tempoo->left;
                else
                    tempoo = tempoo->right;
            }
            return NULL;
        }

        void add(K key, V value)
        {
            Entry *tmp = new Entry(key, value);
            Node *temp = new Node(tmp);
            insertSplay(root, temp);
        }

        void add(Entry *entry)
        {
            Node *temp = new Node(entry);
            insertSplay(root, temp);
        }

        Node *addBKU(Entry *entry)
        {
            Node *temp = new Node(entry);
            insertSplay(root, temp);
            return temp;
        }

        void remove(K key)
        {
            removeSplay(root, key);
        }

        V search(K key)
        {
            Node *tmp = searchSplay(root, key);
            if (tmp == NULL)
                throw "Not found";
            while (tmp->parent != NULL)
            {
                splay(tmp);
            }
            return tmp->entry->value;
        }

        V searchBKU(Node *root, vector<K> &list, K key)
        {
            Node *temp = root;
            while (temp != NULL)
            {
                if (key < temp->entry->key)
                {
                    list.push_back(temp->entry->key);
                    temp = temp->left;
                }
                else if (key > temp->entry->key)
                {
                    list.push_back(temp->entry->key);
                    temp = temp->right;
                }
                else
                    break;
            }
            if (temp == NULL)
                throw "Not found";
            splayBKU(temp);
            V result = temp->entry->value;
            return result;
        }

        void traverseNLR(void (*func)(K key, V value))
        {
            preorder(this->root, func);
        }

        void clear()
        {
            clearTree(this->root);
        }

        void printPretty()
        {
            prettyPrintTree(this->root);
        }

        friend class BKUTree;
        friend class AVLTree;
    };

    class AVLTree
    {
    public:
        class Node
        {
        public:
            Entry *entry;
            Node *left;
            Node *right;
            int balance; //height
            typename SplayTree::Node *corr;

            Node(Entry *entry = NULL, Node *left = NULL, Node *right = NULL)
            {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->balance = 0;
                this->corr = NULL;
            }
        };

    private:
        Node *rightRotate(Node *&root)
        {
            Node *temp = root->left;
            root->left = temp->right;
            temp->right = root;
            return temp;
        }

        Node *leftRotate(Node *&root)
        {
            Node *temp = root->right;
            root->right = temp->left;
            temp->left = root;
            return temp;
        }

        //Left subtree is higher than right subtree
        Node *leftBalance(Node *&root, bool &taller)
        {
            Node *leftTree = root->left;
            //Case 1: Left of Left. Single rotation right
            if (leftTree->balance > 0)
            {
                root->balance = 0;
                leftTree->balance = 0;
                root = rightRotate(root);
                taller = false;
            }
            //Case 3: Right of Left. Rotate left first, rotate right later
            else
            {
                Node *rightTree = leftTree->right;
                if (rightTree->balance > 0)
                {
                    root->balance = -1;
                    leftTree->balance = 0;
                }
                else if (rightTree->balance == 0)
                {
                    root->balance = 0;
                    leftTree->balance = 0;
                }
                else
                {
                    root->balance = 0;
                    leftTree->balance = 1;
                }
                rightTree->balance = 0;
                root->left = leftRotate(leftTree);
                root = rightRotate(root);
                taller = false;
            }
            return root;
        }

        //Right subtree is higher than left subtree
        Node *rightBalance(Node *&root, bool &taller)
        {
            Node *rightTree = root->right;
            //Case 4: Right of Right. Single rotation left
            if (rightTree->balance < 0)
            {
                root->balance = 0;
                rightTree->balance = 0;
                root = leftRotate(root);
                taller = false;
            }
            //Case 2: Left of Right. Rotate right first, rotate left later
            else
            {
                Node *leftTree = rightTree->left;
                if (leftTree->balance < 0)
                {
                    root->balance = 1;
                    rightTree->balance = 0;
                }
                else if (leftTree->balance == 0)
                {
                    root->balance = 0;
                    rightTree->balance = 0;
                }
                else
                {
                    root->balance = 0;
                    rightTree->balance = -1;
                }
                leftTree->balance = 0;
                root->right = rightRotate(rightTree);
                root = leftRotate(root);
                taller = false;
            }
            return root;
        }

        Node *insertAVL(Node *&root, Node *&newNode, bool &taller)
        {
            if (root == NULL)
            {
                root = newNode;
                taller = true;
                return root;
            }
            if (newNode->entry->key == root->entry->key)
            {
                taller = false;
                throw "Duplicate Key";
                return NULL;
            }
            if (newNode->entry->key < root->entry->key)
            {
                root->left = insertAVL(root->left, newNode, taller);
                //left subtree is taller
                if (taller)
                {
                    if (root->balance > 0)
                    {
                        root = leftBalance(root, taller);
                    }
                    else if (root->balance == 0)
                    {
                        root->balance = 1; //LH = 1
                    }
                    else
                    {
                        root->balance = 0;
                        taller = false;
                    }
                }
            }
            if (newNode->entry->key > root->entry->key)
            {
                root->right = insertAVL(root->right, newNode, taller);
                //right subtree is taller
                if (taller)
                {
                    if (root->balance < 0)
                    {
                        root = rightBalance(root, taller);
                    }
                    else if (root->balance == 0)
                    {
                        root->balance = -1; //RH = -1
                    }
                    else
                    {
                        root->balance = 0;
                        taller = false;
                    }
                }
            }
            return root;
        }

        //The (sub)tree is shorter after a deletion on the left branch. Adjust the balance factors and if necessary balance the tree
        Node *removeRightBalance(Node *&root, bool &shorter)
        {
            if (root->balance > 0)
                root->balance = 0;
            else if (root->balance == 0)
            {
                root->balance = -1;
                shorter = false;
            }
            else
            {
                Node *rightTree = root->right;
                if (rightTree->balance > 0)
                {
                    Node *leftTree = rightTree->left;
                    if (leftTree->balance > 0)
                    {
                        rightTree->balance = -1;
                        root->balance = 0;
                    }
                    else if (leftTree->balance == 0)
                    {
                        root->balance = 1;
                        rightTree->balance = 0;
                    }
                    else
                    {
                        root->balance = 1;
                        rightTree->balance = 0;
                    }
                    leftTree->balance = 0;
                    root->right = rightRotate(rightTree);
                    root = leftRotate(root);
                }
                else
                {
                    if (rightTree->balance != 0)
                    {
                        root->balance = 0;
                        rightTree->balance = 0;
                    }
                    else
                    {
                        root->balance = -1;
                        rightTree->balance = 1;
                        shorter = false;
                    }
                    root = leftRotate(root);
                }
            }
            return root;
        }

        //The (sub)tree is shorter after a deletion on the right branch. Adjust the balance factors and if necessary balance the tree
        Node *removeLeftBalance(Node *&root, bool &shorter)
        {
            if (root->balance < 0)
                root->balance = 0;
            else if (root->balance == 0)
            {
                root->balance = 1;
                shorter = false;
            }
            else
            {
                Node *leftTree = root->left;
                if (leftTree->balance < 0)
                {
                    Node *rightTree = leftTree->right;
                    if (rightTree->balance < 0)
                    {
                        leftTree->balance = 1;
                        root->balance = 0;
                    }
                    else if (rightTree->balance == 0)
                    {
                        root->balance = -1;
                        leftTree->balance = 0;
                    }
                    else
                    {
                        root->balance = -1;
                        leftTree->balance = 0;
                    }
                    rightTree->balance = 0;
                    root->left = leftRotate(leftTree);
                    root = rightRotate(root);
                }
                else
                {
                    if (leftTree->balance != 0)
                    {
                        root->balance = 0;
                        leftTree->balance = 0;
                    }
                    else
                    {
                        root->balance = 1;
                        leftTree->balance = -1;
                        shorter = false;
                    }
                    root = rightRotate(root);
                }
            }
            return root;
        }

        Node *removeAVL(Node *&root, K deleteKey, bool &shorter, bool &success)
        {
            if (root == NULL)
            {
                success = false;
                shorter = false;
                throw "Not found";
                //return NULL;
            }
            if (deleteKey < root->entry->key)
            {
                root->left = removeAVL(root->left, deleteKey, shorter, success);
                if (shorter)
                {
                    root = removeRightBalance(root, shorter);
                }
            }
            else if (deleteKey > root->entry->key)
            {
                root->right = removeAVL(root->right, deleteKey, shorter, success);
                if (shorter)
                {
                    root = removeLeftBalance(root, shorter);
                }
            }
            else
            {
                if (root->right == NULL)
                {
                    Node *newRoot = root->left;
                    success = true;
                    shorter = true;
                    delete root;
                    root = newRoot;
                    return root;
                }
                else if (root->left == NULL)
                {
                    Node *newRoot = root->right;
                    success = true;
                    shorter = true;
                    delete root;
                    root = newRoot;
                    return root;
                }
                else
                {
                    Node *tempPtr = root->left;
                    while (tempPtr->right != NULL)
                    {
                        tempPtr = tempPtr->right;
                    }
                    if (root->corr != NULL)
                        root->corr->corr = NULL;
                    Entry *TempEntry = tempPtr->entry;
                    typename SplayTree::Node *TempCorr = tempPtr->corr;
                    tempPtr->corr = root->corr;
                    tempPtr->entry = root->entry;
                    root->entry = TempEntry;
                    root->corr = TempCorr;
                    if (root->corr != NULL)
                        root->corr->corr = root;
                    //root->entry->key = tempPtr->entry->key;
                    root->left = removeAVL(root->left, tempPtr->entry->key, shorter, success);
                    if (shorter)
                    {
                        root = removeRightBalance(root, shorter);
                    }
                    //root->corr = tempPtr->corr;
                }
            }
            return root;
        }

        Node *searchAVL(Node *root, K key)
        {
            if (root == NULL)
                return NULL;
            if (key == root->entry->key)
                return root;
            else if (key < root->entry->key)
                return searchAVL(root->left, key);
            else if (key > root->entry->key)
                return searchAVL(root->right, key);
        }
        /*
        Node *searchBKU(Node *start, Node *checkPoint, vector<K> &list, K key)
        {
            if (start != this->root) checkPoint = start;
            Node* temp = start;
            while (temp != NULL){
                if (start == this->root && temp == checkPoint) throw "Not found";
                if (key < temp->entry->key){
                    list.push_back(temp->entry->key);
                    temp = temp->left;
                }
                else if (key > temp->entry->key){
                    list.push_back(temp->entry->key);
                    temp = temp->right;
                }
                else{
                    return temp;
                }
            }
            if (temp == NULL && start == this->root) throw "Not found";
            return temp;
        }
        */
        V searchForBKU(K key, vector<K> &traversedList, bool &found, Node *start, Node *&KeyAddress, Node *&checkPoint)
        {
            V result;
            if (start != this->root)
                checkPoint = start;
            //else checkPoint = NULL;
            Node *temp = start;
            while (temp)
            {
                if (start == root && temp == checkPoint)
                    throw("Not found"); /// traverse from root and reach the checkpoint
                if (key < temp->entry->key)
                {
                    traversedList.push_back(temp->entry->key);
                    //cout<<"You just push"<<temp->entry->key<<endl;
                    temp = temp->left;
                }
                else if (key > temp->entry->key)
                {
                    traversedList.push_back(temp->entry->key);
                    // cout<<"You just push"<<temp->entry->key<<endl;
                    temp = temp->right;
                }
                else
                { // key === temp->entry->key
                    // cout<<"key has been found "<<endl;
                    found = true;
                    KeyAddress = temp;
                    result = temp->entry->value;
                    return result;
                }
            }
            if (temp == NULL && start == this->root)
                throw("Not found"); /// has performed search on root
            return result;
        }

        void preorder(Node *root, void (*func)(K key, V value))
        {
            if (root == NULL)
                return;
            else{
                func(root->entry->key, root->entry->value);
                preorder(root->left, func);
                preorder(root->right, func);
            }
        }

        void clearTree(Node *&root)
        {
            if (root == NULL)
                return;
            clearTree(root->left);
            clearTree(root->right);
            delete root;
            root = NULL;
        }

        void prettyPrintTree(Node *_root, string prefix = "", bool isLeft = true)
        {
            if (!_root)
            {
                cout << "Empty tree!\n";
                return;
            }

            if (_root->right)
            {
                prettyPrintTree(_root->right, prefix + (isLeft ? "|   " : "    "), false);
            }

            cout << prefix + (isLeft ? "+-- " : "+-- ") + "<" + to_string(_root->entry->key) + "," + to_string(_root->entry->value) + ">\n";

            if (_root->left)
            {
                prettyPrintTree(_root->left, prefix + (isLeft ? "    " : "|   "), true);
            }
        }

    public:
        Node *root;

        AVLTree() : root(NULL){};
        ~AVLTree() { this->clear(); };

        Node *find(K key)
        {
            Node *tempoo = root;
            while (tempoo != NULL)
            {
                if (tempoo->entry->key == key)
                    return tempoo;
                else if (tempoo->entry->key > key)
                    tempoo = tempoo->left;
                else
                    tempoo = tempoo->right;
            }
            return NULL;
        }

        void add(K key, V value)
        {
            Entry *tmp = new Entry(key, value);
            Node *temp = new Node(tmp);
            bool taller = true;
            insertAVL(root, temp, taller);
        }

        void add(Entry *entry)
        {
            Node *temp = new Node(entry);
            bool taller = true;
            insertAVL(root, temp, taller);
        }

        Node *addBKU(Entry *entry)
        {
            Node *temp = new Node(entry);
            bool taller = true;
            insertAVL(root, temp, taller);
            return temp;
        }

        void remove(K key)
        {
            bool success = false;
            bool shorter = false;
            removeAVL(root, key, shorter, success);
        }

        V search(K key)
        {
            Node *tmp = searchAVL(root, key);
            if (tmp == NULL)
                throw "Not found";
            return tmp->entry->value;
        }

        void traverseNLR(void (*func)(K key, V value))
        {
            preorder(this->root, func);
        }

        void clear()
        {
            clearTree(this->root);
        }

        void printPretty()
        {
            prettyPrintTree(this->root);
        }

        friend class BKUTree;
        friend class SplayTree;
    };
};

template <class K, class V>
void printKey(K key, V value)
{
    cout << key << " ";
}

void checkV(vector<int> list)
{
    cout << "\nLIST CHECK" << endl;
    while (list.empty() == false)
    {
        cout << list.back() << "  ";
        list.pop_back();
    }
    cout << endl;
}
int main()
{
    BKUTree<int, int> *tree = new BKUTree<int, int>(3);
    tree->add(5, 10);
    tree->add(4, 16);
    tree->add(3, 16);
    tree->add(2, 16);
    tree->add(1, 16);
    tree->add(50, 50);
    tree->add(110, 110);
    tree->add(150, 150);
    tree->add(200, 220);
    tree->add(7, 220);
    tree->traverseNLROnSplay(printKey);
    cout << endl;
    tree->traverseNLROnAVL(printKey);
    tree->remove(110);
    cout << endl;
    tree->traverseNLROnSplay(printKey);
    cout << endl;
    tree->traverseNLROnAVL(printKey);
    cout << endl;
    queue<int> Q1 = tree->copy_queue();
    cout << "\nThe queue at the moment is : \n";
    while (!Q1.empty())
    {
        cout << Q1.front() << "\t";
        Q1.pop();
    }
    cout << endl;
    cout << endl;
    vector<int> result;
    tree->search(150, result);
    tree->traverseNLROnAVL(printKey);
    // //tree->remove(3);
    // cout << endl;
    cout << endl;
    tree->traverseNLROnSplay(printKey);
    cout << "\n The vector is : \n";
    for (auto i = result.begin(); i != result.end(); i++)
    {
        cout << *i << "\t";
    }
    Q1 = tree->copy_queue();
    cout << "\nThe queue at the moment is : \n";
    while (!Q1.empty())
    {
        cout << Q1.front() << "\t";
        Q1.pop();
    }
    cout << "\nThe Search vector is : \n";
    vector<int> result2;
    tree->search(2, result2);
    for (auto i = result2.begin(); i != result2.end(); i++)
    {
        cout << *i << "\t";
    }
    cout << endl;
    tree->traverseNLROnSplay(printKey);
    cout << endl;
    tree->traverseNLROnAVL(printKey);
    tree->add(205, 110);
    tree->add(204, 150);
    tree->add(203, 220);
    tree->add(202, 220);
    result2.clear();
    cout << endl;
    tree->traverseNLROnSplay(printKey);
    cout << endl;
    tree->traverseNLROnAVL(printKey);
    tree->search(205, result2);
    cout << "\n The vector is : \n";
    for (auto i = result2.begin(); i != result2.end(); i++)
    {
        cout << *i << "\t";
    }
    cout << endl;
    cout << endl;
    tree->traverseNLROnSplay(printKey);
    cout << endl;
    tree->traverseNLROnAVL(printKey);
    delete tree;
}
