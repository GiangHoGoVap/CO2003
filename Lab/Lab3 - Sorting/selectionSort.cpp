#include <iostream>
using namespace std;

template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void selectionSort(T *start, T *end);
};

template <class T>
void Sorting<T>::selectionSort(T *start, T *end)
{
    int size = end - start;
    int i, j, minIdx;
    for (i=0; i<size-1; i++){
        minIdx = i;
        for (j=i+1; j<size; j++){
            if (start[j] < start[minIdx]) minIdx = j;
        }
        T temp = start[i];
        start[i] = start[minIdx];
        start[minIdx] = temp;
        printArray(start, end);
    }
}

int main(){
	int arr[] = {9, 2, 8, 1, 0, -2};
	Sorting<int>::selectionSort(&arr[0], &arr[6]);
}
