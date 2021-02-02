#include <iostream>
#include <math.h>
using namespace std;

int jumpSearch(int arr[], int x, int n)
{
    // TODO: print the traversed indexes and return the index of value x in array if x is found, otherwise, return -1.
    int m = sqrt(n);
    int i;
    for (i = 0; i < n && arr[i] < x; i += m)
    {
        cout << i << " ";
    }
    if (arr[i] == x)
    {
        cout << i << " ";
        return i;
    }
    else
    {
        if (i < n)
            cout << i << " ";
        int j = i - (m - 1);
        for (; j <= n && j < i; j += 1)
        {
            cout << j << " ";
            if (arr[j] == x)
            {

                return j;
            }
        }
        return -1;
    }
}

int main()
{
    int arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610};
    int x = 55;
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = jumpSearch(arr, x, n);

    if (index != -1)
    {
        cout << "\nNumber " << x << " is at index " << index;
    }
    else
    {
        cout << "\n"
             << x << " is not in array!";
    }
}