#include <iostream>
#include <math.h>
using namespace std;

int foldShift(string num, int addressSize)
{
    int sum = 0;
    int tmp = 0;
    int i = 0;
    string str;
    for (auto it = num.begin(); it != num.end();)
    {
        i++;
        str = *it;
        tmp = tmp * 10 + stoi(str);
        if (++it == num.end() || i == addressSize)
        {
            sum += tmp;
            tmp = 0;
            i = 0;
        }
        str = "";
    }
    int res = 0;
    for (int i = 0; i < addressSize; i++)
    {
        res += sum % 10 * pow(10, i);
        sum /= 10;
    }
    return res;
}

int foldShift(long long key, int addressSize)
{
    return foldShift(to_string(key), addressSize);
}

int rotation(long long key, int addressSize)
{
    int last = key % 10;
    string tmp = to_string(last);
    tmp.append(to_string(key / 10));
    //cout << key << "\n";
    return foldShift(tmp, addressSize);
}

int main()
{
    cout << rotation(600101, 2);
}