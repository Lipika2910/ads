#include <iostream>
#include <cstdlib>
using namespace std;

int randomizedPartition(int arr[], int low, int high) {
    int randomPivot = low + rand() % (high - low + 1);
    swap(arr[randomPivot], arr[high]);
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int randomizedSelect(int arr[], int low, int high, int i) {
    if (low == high) {
        return arr[low];
    }
    int pivotIndex = randomizedPartition(arr, low, high);
    int k = pivotIndex - low + 1;
    if (i == k) {
        return arr[pivotIndex];
    } else if (i < k) {
        return randomizedSelect(arr, low, pivotIndex - 1, i);
    } else {
        return randomizedSelect(arr, pivotIndex + 1, high, i - k);
    }
}

int main() {
    int arr[] = {3, 2, 9, 4, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 4; // 4th smallest element
    cout << "The " << i << "th smallest element is " << randomizedSelect(arr, 0, n - 1, i) << endl;
    return 0;
}








/*

#include <iostream>
using namespace std;
#include <vector>
#include <algorithm> // For std::nth_element

int main() {
    vector<int> nums = {0, 10, 4, 3, 20, 15};
    int k;
    cout<<"enter number " ;
    cin>>k;

    // Find the k-th smallest element
    nth_element(nums.begin(), nums.begin() + k - 1, nums.end());

    // Output the k-th smallest element
    cout << "The " << k << "-th smallest element is: " << nums[k-1 ] << std::endl;

    return 0;
}














*/