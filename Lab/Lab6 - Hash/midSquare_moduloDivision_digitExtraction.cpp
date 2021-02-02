#include <iostream>
#include <math.h>
using namespace std;

long int midSquare(long int seed)
{
    seed = seed * seed;
    seed = seed / 100;
    int result = seed % (int)pow(10, 4);
    return result;
}
long int moduloDivision(long int seed, long int mod)
{
    return seed % mod;
}
long int digitExtraction(long int seed, int *extractDigits, int size)
{
    int len = log10(seed) + 1;
    int flag = pow(10, size - 1);
    int a[len];
    for (int i = len - 1; i >= 0; i--)
    {
        a[i] = seed % 10;
        seed = seed / 10;
    }
    //print(a,len);
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        result += a[extractDigits[i]] * flag;
        flag /= 10;
    }
    return result;
}

int main()
{
    int a[] = {1, 2, 5};
    cout << digitExtraction(122443, a, 3) << endl;
    cout << midSquare(9452);
}