#include <iostream>
#include <vector>
using namespace std;

void print(int n, int arr[]) { for (int i = 0; i < n; i++) cout << arr[i] << " "; cout << "\n"; }

// Merge Sort
void merge(int start1, int end1, int end2, int arr[]) {
    const int n = end1 - start1 + end2 - end1 + 3;
    int temp[n];
    int k = 0;
    int i = start1;
    int j = end1 + 1;

    while (i <= end1 || j <= end2) {
        if (i <= end1 && j <= end2) {
            if (arr[i] <= arr[j]) temp[k++] = arr[i++];
            else temp[k++] = arr[j++];
        } else if (i <= end1) temp[k++] = arr[i++];
        else if (j <= end2) temp[k++] = arr[j++];
    }

    for (int i = start1, j = 0; i <= end2; i++, j++) arr[i] = temp[j];
}

void mergeSort(int start, int end, int arr[]) {
    if (start >= end) return;
    int mid = start + ((end - start) >> 1);
    mergeSort(start, mid, arr);
    mergeSort(mid + 1, end, arr);
    merge(start, mid, end, arr);
}

int main() {
    int n = 10;
    int arr[] = { 3, 6, 2, 8, 9, 5, 4, 7, 2, 8 };
    mergeSort(0, n - 1, arr);
    print(n, arr);
    return 0;
}