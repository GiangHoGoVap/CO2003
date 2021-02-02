#include <iostream>
using namespace std;
template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start + 1;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T *left, T *middle, T *right)
    {
        /*TODO*/
        T *L = new T[middle - left + 1];
        T *R = new T[right - middle];
        int i, j, k;
        for (i = 0; i < (middle - left + 1); i++)
        {
            L[i] = left[i];
        }
        for (j = 0; j < (right - middle); j++)
        {
            R[j] = middle[j + 1];
        }
        i = 0;
        j = 0;
        k = 0;
        while ((i < (middle - left + 1) && j < (right - middle)) || (k <= right - left))
        {
            if (i >= (middle - left + 1))
            {
                left[k] = R[j];
                j++;
            }
            else if (j >= (right - middle))
            {
                left[k] = L[i];
                i++;
            }
            else if (L[i] <= R[j])
            {
                left[k] = L[i];
                i++;
            }
            else
            {
                left[k] = R[j];
                j++;
            }
            k++;
        }
        delete[] L;
        delete[] R;
        Sorting::printArray(left, right);
    }
    static void mergeSort(T *start, T *end)
    {
        /*TODO*/
        if (start < end)
        {
            T *m = (end - start) / 2 + start;
            mergeSort(start, m);
            mergeSort(m + 1, end);
            merge(start, m, end);
        }
    }
};

int main()
{
    int arr[] = {0, 2, 4, 3, 1, 4};
    Sorting<int>::mergeSort(&arr[0], &arr[5]);
}
