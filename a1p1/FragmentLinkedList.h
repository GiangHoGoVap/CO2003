template <class T>
class FragmentLinkedList : IList<T>
{
public:
    class Node;
    class Iterator;

protected:
    Node **fragmentPointers;
    int fragmentMaxSize;
    int count;
    Node* dummyNode;
	
public:
    FragmentLinkedList(int fragmentMaxSize = 5)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
    }
    virtual ~FragmentLinkedList()
    {
        clear();
        delete[] fragmentPointers;
    }
    virtual void add(const T& element);
    virtual void add(int index, const T& element);
    virtual T removeAt(int index);
    virtual bool removeItem(const T& item);
    virtual bool empty();
    virtual int size();
    virtual void clear();
    virtual T get(int index);
    virtual void set(int index, const T& element);
    virtual int indexOf(const T& item);
    virtual bool contains(const T& item);
    virtual string toString();
    Iterator begin(int index = 0)
    {
        
        if (this->count == 0)
        {
            Iterator it(index, this, true);
            return it;
        }
        
        int numFrag;
        if (this->count % this->fragmentMaxSize == 0)
        {
            numFrag = count/fragmentMaxSize; 
        }
        else numFrag = count/fragmentMaxSize + 1;

        if (index > numFrag - 1 || index < 0) throw std::out_of_range("The index is out of range!");

        Iterator it(index, this, true);
        return it;
    }
    Iterator end(int index = -1)
    {
        if (this->count == 0)
        {
            Iterator it(this, false);
            return it;
        }

        int numFrag;
        if (this->count % this->fragmentMaxSize == 0)
        {
            numFrag = count/fragmentMaxSize; 
        }
        else numFrag = count/fragmentMaxSize + 1;

        if (index > numFrag - 1 || index < -1) throw std::out_of_range("The index is out of range!");

        if (index == -1) 
        {
            Iterator it(this, false);
            return it;
        }
        else
        {
            Iterator it(index, this, false);
            return it;
        }
    }
    void rearrange()
    {
        if (this->count == 0)
        {
            Node** tempFragmentPointers2 = new Node* [2];
            tempFragmentPointers2[0] = nullptr;
            tempFragmentPointers2[1] = nullptr;
            delete[] fragmentPointers;
            fragmentPointers = tempFragmentPointers2;
            delete dummyNode;
            dummyNode = nullptr;
            return;
        }
        else
        {
            int nP;
            if (count % fragmentMaxSize == 0)
            {
                nP = count/fragmentMaxSize + 1;
            }
            else nP = count/fragmentMaxSize + 2;
            Node** tempFragmentPointers = new Node* [nP];
            Node* temp = this->fragmentPointers[0];
            int counter = nP - 1;
            int i  = 0;
            int j = 0;
            
            while (i < counter)
            {
                tempFragmentPointers[i] = temp;
                while (temp->next)
                {
                    temp = temp->next;
                    j++;
                    if (j % fragmentMaxSize == 0) break;
                }
                i++;
            }
            tempFragmentPointers[counter] = temp;
            delete[] fragmentPointers;
            this->fragmentPointers = tempFragmentPointers;
        } 
    }

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
        friend class FragmentLinkedList<T>;

    public:
        Node()
        {
            next = 0;
            prev = 0;
        }
        Node(Node *next, Node *prev)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next, Node *prev)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    class Iterator
    {
    private:
        FragmentLinkedList<T> *pList;
        Node *pNode;
        int index;

    public:
        Iterator(FragmentLinkedList<T> *pList = 0, bool begin = true)
        {
            this->pList = pList;
            if (begin)
            {
                index = 0;
                this->pNode = pList->fragmentPointers[index];
            }
            else
            {
                index = pList->size();
                this->pNode = nullptr;
            }
        }
        Iterator(int fragmentIndex, FragmentLinkedList<T> *pList = 0, bool begin = true)
        {
            this->pList = pList;
            if (begin)
            {
                this->pNode = pList->fragmentPointers[fragmentIndex];
                index = fragmentIndex * pList->fragmentMaxSize;
            }
            else
            {
                int numFrag;
                if (pList->count % pList->fragmentMaxSize == 0)
                {
                    numFrag = pList->count/pList->fragmentMaxSize;
                }
                else numFrag = pList->count/pList->fragmentMaxSize + 1;
                
                if (fragmentIndex == numFrag - 1) 
                {
                    this->pNode = nullptr;
                }
                else 
                {
                    this->pNode = pList->fragmentPointers[fragmentIndex + 1];    
                    index = fragmentIndex * pList->fragmentMaxSize + pList->fragmentMaxSize;    
                }    
            }
        }
        Iterator &operator=(const Iterator &iterator)
        {
            this->pList = iterator.pList;
            this->pNode = iterator.pNode;
            this->index = iterator.index;
            return *this;
        }
        T &operator*()
        {
            if (pNode == nullptr) throw std::out_of_range("Segmentation fault!");
            else return pNode->data;
        }
        bool operator!=(const Iterator &iterator)
        {
            return (pNode != iterator.pNode);
        }
        
        void remove()
        {
            Node* temp;
            if (pList->count == 1)
            {
                delete pNode;
                pList->fragmentPointers[0] = nullptr;
                pList->fragmentPointers[1] = nullptr;
            }
            else
            {
                if (pNode->prev == nullptr)
                {
                    pList->dummyNode->next = pNode->next; 
                    pList->fragmentPointers[0] = pNode->next; 
                    delete pNode;
                    pList->fragmentPointers[0]->prev = nullptr;
                    pNode = pList->dummyNode;
                }
                else if (pNode->next == nullptr)
                {
                    temp = pNode->prev;
                    pNode->prev->next = nullptr;
                    delete pNode;
                    pNode = temp;
                }
                else
                {
                    temp = pNode->prev;
                    pNode->prev->next = pNode->next;
                    pNode->next->prev = pNode->prev;
                    delete pNode;
                    pNode = temp;
                }
            }
            pList->count--;
            pList->rearrange();
        }
        
        void set(const T& element)
        {
            if (pNode) pNode->data = element;
        }
        Iterator &operator++()
        {
            if (pNode) 
            {
                pNode = pNode->next;
                index++;
            }
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };
};

template<class T>
void FragmentLinkedList<T>::add(const T& value)
{
	Node* newPtr = new Node(value, nullptr, nullptr);
    int nP;
    if (this->count % this->fragmentMaxSize == 0)
    {
        nP = this->count/this->fragmentMaxSize;
    } 
    else nP = this->count/this->fragmentMaxSize + 1;
    if (empty()) 
    {
        dummyNode = new Node;
        dummyNode->prev = nullptr;
        dummyNode->next = newPtr;
        this->fragmentPointers[0] = newPtr;
        this->fragmentPointers[1] = newPtr;
        this->count++;
        return;
    }
	while(fragmentPointers[nP]->next != nullptr)
    {
		fragmentPointers[nP] = fragmentPointers[nP]->next;
	}
	newPtr->prev = fragmentPointers[nP];
	newPtr->next = fragmentPointers[nP]->next;
	fragmentPointers[nP]->next = newPtr;
	this->count++;
    rearrange();
}

template<class T>
void FragmentLinkedList<T>::add(int idx,const T& value)
{
	if (idx < 0 || idx > this->count) throw std::out_of_range("The index is out of range!");
	Node* newPtr = new Node(value, nullptr, nullptr);
	Node* pPre = this->fragmentPointers[0];
	if (empty())
    {
        dummyNode = new Node;
        dummyNode->prev = nullptr;
        dummyNode->next = newPtr;
		fragmentPointers[0] = newPtr;
        fragmentPointers[1] = newPtr;
	}
	else if (idx == 0)
    {
		newPtr->next = fragmentPointers[0];
		fragmentPointers[0]->prev = newPtr;
        fragmentPointers[0] = newPtr;
	}
    else if (idx == this->count)
    {
        for (int i=0; i<idx-1; i++)
        {
            pPre = pPre->next;
        }
        newPtr->next = pPre->next;
        newPtr->prev = pPre;
        pPre->next = newPtr;
    }
	else
    {
		for (int i=0; i<idx-1; i++)
        {
			pPre = pPre->next;
		}
		newPtr->next = pPre->next;
        newPtr->prev = pPre;
		pPre->next->prev = newPtr;
		pPre->next = newPtr;
	}
	this->count++;
    rearrange();
}

template<class T>
T FragmentLinkedList<T>::removeAt(int idx)
{
    T tmp = 0;
	if (idx < 0 || idx > this->count) throw std::out_of_range("The index is out of range!");	
	Node* pLoc = nullptr;
    Node* curIdx = this->fragmentPointers[0];
    if (idx == 0)
    {
        tmp = fragmentPointers[0]->data;
        fragmentPointers[0] = curIdx->next;
        if (count == 1)
        {
            delete fragmentPointers[0];
            fragmentPointers[0] = nullptr;
            count--;
            rearrange();
            return tmp;
        }
        delete (fragmentPointers[0]->prev);
        if (fragmentPointers[0]) fragmentPointers[0]->prev = nullptr;
        count--;
        rearrange();
        return tmp;
    }
    for (int i=0; i<idx; i++)
    {
        pLoc = curIdx;
        curIdx = curIdx->next;
    }
    tmp = curIdx->data;
    pLoc->next = curIdx->next;
    if (curIdx->next) curIdx->next->prev = curIdx->prev;
    this->count--;
    delete curIdx;
    rearrange();
    return tmp;
}

template<class T>
bool FragmentLinkedList<T>::removeItem(const T& item)
{
    Node* pLoc = this->fragmentPointers[0];
	Node* curIdx = this->fragmentPointers[0];
	while(curIdx != nullptr)
    {
        if (curIdx->data == item)
        {
            if (curIdx->prev == nullptr) fragmentPointers[0] = curIdx->next;
            pLoc->next = curIdx->next;
            if (curIdx->next) curIdx->next->prev = curIdx->prev;
            this->count--;
            delete curIdx;
            rearrange();
            return true;
        }
        pLoc = curIdx;
        curIdx = curIdx->next;
	}
	return false;
}

template<class T>
bool FragmentLinkedList<T>::empty()
{
	if (this->count == 0) return true;
	else return false;
}

template<class T>
int FragmentLinkedList<T>::size()
{
	return this->count;
}

template<class T>
void FragmentLinkedList<T>::clear()
{
	Node* temp = this->fragmentPointers[0];
    Node* tempo = this->fragmentPointers[0];
	while (tempo != nullptr)
    {
		temp = temp->next;
		delete tempo;
        tempo = temp;
	}
	this->count = 0;
    Node** tempFragmentPointers2 = new Node* [2];
    tempFragmentPointers2[0] = nullptr;
    tempFragmentPointers2[1] = nullptr;
    delete[] fragmentPointers;
    fragmentPointers = tempFragmentPointers2;
    delete dummyNode;
    dummyNode = nullptr;
}

template<class T>
T FragmentLinkedList<T>::get(int idx)
{
    T result = 0;
    if (idx < 0 || idx > this->count - 1) throw std::out_of_range("The index is out of range!");
    Node* newPtr = this->fragmentPointers[0];
    for (int i=0; i<idx; i++)
    {
        newPtr = newPtr->next;
    }
    result = newPtr->data;
    return result;
}

template<class T>
int FragmentLinkedList<T>::indexOf(const T& item)
{
    Node* pCur = this->fragmentPointers[0];
    int counter = 0;
    while(pCur != nullptr)
    {
        if (pCur->data == item)
        {
            return counter;
        }
        counter++;
        pCur = pCur->next;
    }
    return -1;
}

template<class T>
bool FragmentLinkedList<T>::contains(const T& item)
{
    Node* pCur = this->fragmentPointers[0];
    while (pCur != nullptr)
    {
        if (pCur->data == item)
        {
            return true;
        }
        pCur = pCur->next;
    }
    return false;
}

template<class T>
void FragmentLinkedList<T>::set(int idx, const T& element)
{
    if (idx < 0 || idx > this->count - 1) throw std::out_of_range("The index is out of range!");
    Node* pCur = this->fragmentPointers[0];
    for (int i=0; i<idx; i++)
    {
        pCur = pCur->next;
    }
    pCur->data = element;
}

template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node *ptr = this->fragmentPointers[0];
    if (this->count == 0)
        ss << "]";
    else
    {
        int counter = 0;
        while(ptr != nullptr)
        {
            if (counter == this->count - 1)
            {
                ss << ptr->data << "]";
            }
            else
            {
                ss << ptr->data << ", ";
            }
            counter++;
            ptr = ptr->next;
        }
    }
    return ss.str();
}