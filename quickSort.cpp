#include <iostream>
#include <vector>
using namespace std;

void print(int n, int arr[]) { for (int i = 0; i < n; i++) cout << arr[i] << " "; cout << "\n"; }

int getPivot(int start, int end, int arr[]) {
    int pivot = start;
    int i = start + 1;
    int j = end;

    while (i <= j) {
        if (arr[i] < arr[pivot]) i++;
        else if (arr[j] >= arr[pivot]) j--;
        else swap(arr[i], arr[j]);
    }

    swap(arr[pivot], arr[j]);
    return j;
}
void quickSort(int start, int end, int arr[]) {
    if (start >= end) return;
    int pivot = getPivot(start, end, arr);
    quickSort(start, pivot - 1, arr);
    quickSort(pivot + 1, end, arr);
}

int main() {
    int n = 10;
    int arr[] = { 3, 6, 2, 8, 9, 5, 4, 7, 2, 8 };
    quickSort(0, n - 1, arr);
    print(n, arr);
    return 0;
}