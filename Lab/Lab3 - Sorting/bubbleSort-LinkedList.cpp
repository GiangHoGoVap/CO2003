#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class SLinkedList
{
public:
    class Node; // Forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    SLinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }
    ~SLinkedList(){};
    void add(T e)
    {
        Node *pNew = new Node(e);

        if (this->count == 0)
        {
            this->head = this->tail = pNew;
        }
        else
        {
            this->tail->next = pNew;
            this->tail = pNew;
        }

        this->count++;
    }
    int size()
    {
        return this->count;
    }
    void printList()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }

        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        cout << ss.str() << endl;
    }

public:
    class Node
    {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;

    public:
        Node()
        {
            next = 0;
        }
        Node(T data)
        {
            this->data = data;
            this->next = nullptr;
        }
    };

    void bubbleSort();
};

template <class T>
void SLinkedList<T>::bubbleSort()
{
    int swapped;
    Node *lPtr;
    Node *rPtr = NULL;
    do
    {
        swapped = 0;
        lPtr = head;
        while (lPtr->next != rPtr)
        {
            if (lPtr->data > lPtr->next->data)
            {
                T temp = lPtr->data;
                lPtr->data = lPtr->next->data;
                lPtr->next->data = temp;
                swapped = 1;
            }
            lPtr = lPtr->next;
        }
        rPtr = lPtr;
        if (swapped == 0)
            break;
        printList();
    } while (swapped);
}

int main()
{
    int arr[] = {9, 2, 8, 4, 1};
    SLinkedList<int> list;
    for (int i = 0; i < int(sizeof(arr)) / 4; i++)
        list.add(arr[i]);
    list.bubbleSort();
}