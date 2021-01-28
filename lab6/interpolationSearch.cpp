int interpolationSearch(int arr[], int left, int right, int x)
{
    int pos;
    if (left <= right && x >= arr[left] && x <= arr[right])
    {
        pos = left + (((double)(right - left) / (arr[right] - arr[left])) * (x - arr[left]));
        if (arr[pos] == x)
        {
            cout << "We traverse on index: " << pos << endl;
            return pos;
        }
        if (arr[pos] < x)
        {
            cout << "We traverse on index: " << pos << endl;
            return interpolationSearch(arr, pos + 1, right, x);
        }
        if (arr[pos] > x)
        {
            cout << "We traverse on index: " << pos << endl;
            return interpolationSearch(arr, left, pos - 1, x);
        }
    }
    return -1;
}