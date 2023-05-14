#include <iostream>
#include <vector>
using namespace std;

class QuickSort {
    private:
        int n;
        vector<int> arr;

    public:
        // constructor
        QuickSort(vector<int>& arr, int n) {
            this->n = n;
            this->arr = arr;
        }

        // get pivot index
        int getPivotIndex(int start, int end) {
            int pivot = start, l = pivot + 1, r = end;
            while (l <= r)
                if (arr[l] < arr[pivot]) l++;
                else if (arr[r] >= arr[pivot]) r--;
                else swap(arr[l], arr[r]);
            swap(arr[pivot], arr[r]);
            return r;
        }

        // quick sort function
        void sort(int start, int end) {
            if (start >= end) return;
            int pivot = getPivotIndex(start, end);
            sort(start, pivot - 1);
            sort(pivot + 1, end);
        }

        // printing the code
        inline void print() {
            for (int n: arr) cout << n << " ";
            cout << "\n";
        }
};

int main() {
    // size of input
    int n;
    cin >> n;
    // creating array for input
    vector<int> arr(n);
    // taking array input
    for (int i = 0; i < n; i++) cin >> arr[i];

    QuickSort *quickSort = new QuickSort(arr, n);
    // calling merge sort
    quickSort->sort(0, n - 1);
    // printing the array
    quickSort->print();

    return 0;
}
