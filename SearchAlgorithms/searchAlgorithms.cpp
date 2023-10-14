#include <iostream>
// Return the position of x in arr
template<typename T>
int binarySearch(T arr[], int n, int l, int r, T x) {
    int mid = (l+r)/2;
    if (l > r) {
        if (x == arr[l])
            return l;
        else
            return -1;
    }
    if (x <= mid)
        return binarySearch(arr, n, l, mid, x);
    else
        return binarySearch(arr, n, mid+1, l, x);

}

template<typename T>
int gallopingSearch() {

}