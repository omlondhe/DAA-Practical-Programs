#include <iostream>
#include <vector>
using namespace std;

class MergeSort {
    private:
        int n;
        vector<int> arr;

    public:
        // constructor
        MergeSort(vector<int>& arr, int n) {
            this->n = n;
            this->arr = arr;
        }

        // merger function
        void merge(int start1, int end1, int start2, int end2) {
            // initial pointers
            int s1 = start1;
            int s2 = start2;
            vector<int> sorted;
            // looping till we do not traverse and merge all elements
            while (s1 <= end1 || s2 <= end2) {
                if (s1 <= end1 && s2 <= end2) {
                    if (arr[s1] <= arr[s2]) sorted.push_back(arr[s1++]);
                    else sorted.push_back(arr[s2++]);
                } else if (s1 <= end1) sorted.push_back(arr[s1++]);
                else if (s2 <= end2) sorted.push_back(arr[s2++]);
            }

            // assigning sorted elements to the array
            for (int i = start1, j = 0; i <= end2; i++, j++)
                arr[i] = sorted[j];
        }

        // function to sort the array
        void sort(int start, int end) {
            // return if start >= end
            if (start >= end) return;
            // find the mid
            int mid = start + ((end - start) >> 1);
            // calling sort for left half
            sort(start, mid);
            // calling sort for right half
            sort(mid + 1, end);
            // merge sorted arrays
            merge(start, mid, mid + 1, end);
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

    MergeSort *mergeSort = new MergeSort(arr, n);
    // calling merge sort
    mergeSort->sort(0, n - 1);
    // printing the array
    mergeSort->print();

    return 0;
}
