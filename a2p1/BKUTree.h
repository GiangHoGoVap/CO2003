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
            bool AVLSubSearch = false;
            bool AVLRootSearch = false;
            typename AVLTree::Node *returnAddress = NULL;
            typename AVLTree::Node *checkPoint = NULL;
            //typename AVLTree::Node* alpha = NULL;
            if (splay->root->corr == avl->root)
            {
                result = avl->searchForBKU(key, traversedList, AVLRootSearch, avl->root, returnAddress, checkPoint);
            }
            else
            {
                result = avl->searchForBKU(key, traversedList, AVLSubSearch, splay->root->corr, returnAddress, checkPoint);
                if (AVLSubSearch == false)
                    result = avl->searchForBKU(key, traversedList, AVLRootSearch, avl->root, returnAddress, checkPoint);
            }
            splay->splayBKU(returnAddress->corr);
        }
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
                root = ans;
                root->right = delPtrRight;
                delPtrRight->parent = root;
            }
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
                //key not found//
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
        
        V searchForBKU(K key, vector<K> &traversedList, bool &found, Node *start, Node *&KeyAddress, Node *&checkPoint)
        {
            V result;
            if (start != this->root)
                checkPoint = start;
            Node *temp = start;
            while (temp)
            {
                if (start == root && temp == checkPoint)
                    throw("Not found");
                if (key < temp->entry->key)
                {
                    traversedList.push_back(temp->entry->key);
                    temp = temp->left;
                }
                else if (key > temp->entry->key)
                {
                    traversedList.push_back(temp->entry->key);
                    temp = temp->right;
                }
                else
                {
                    found = true;
                    KeyAddress = temp;
                    result = temp->entry->value;
                    return result;
                }
            }
            if (temp == NULL && start == this->root)
                throw("Not found");
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

        friend class BKUTree;
        friend class SplayTree;
    };
};
