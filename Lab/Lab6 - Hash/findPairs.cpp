#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>
using namespace std;

bool findPairs(int arr[], int n, pair<int, int> &pair1, pair<int, int> &pair2)
{
    // TODO: If there are two pairs satisfy the condition, assign their values to pair1, pair2 and return true. Otherwise, return false.
    map<int, pair<int, int>> hash;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int sum = arr[i] + arr[j];
            if (hash.find(sum) == hash.end())
            {
                hash[sum] = make_pair(i, j);
            }
            else
            {
                std::pair<int, int> pp = hash[sum];
                pair1.first = arr[pp.first];
                pair1.second = arr[pp.second];
                pair2.first = arr[i];
                pair2.second = arr[j];
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int arr[] = {3, 4, 7, 1, 2, 9, 8};
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    if (findPairs(arr, n, pair1, pair2))
    {
        if (checkAnswer(arr, n, pair1, pair2))
        {
            printf("Your answer is correct.\n");
        }
        else
            printf("Your answer is incorrect.\n");
    }
    else
        printf("No pair found.\n");
}