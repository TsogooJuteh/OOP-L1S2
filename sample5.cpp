#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
void gnomeSort(T arr[], int n) {
    int pos = 0;
    while (pos < n) {
        if (pos == 0 || arr[pos] >= arr[pos-1]) {
            pos++;
        } else {
            swap(arr[pos], arr[pos-1]);
            pos--;
        }
    }
}

template <typename T>
void mergeSort(T arr[], int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid+1, right);
    T tmp[right-left+1];
    int i = left, j = mid+1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = arr[i++];
    }
    while (j <= right) {
        tmp[k++] = arr[j++];
    }
    for (int p = 0; p < k; p++) {
        arr[left+p] = tmp[p];
    }
}

template <typename T>
void printArray(T arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T>
void printToFile(T arr[], int n, string filename) {
    ofstream file(filename);
    for (int i = 0; i < n; i++) {
        file << arr[i] << " ";
    }
    file.close();
}

template <typename T>
void readFromFile(T arr[], int n, string filename) {
    ifstream file(filename);
    for (int i = 0; i < n; i++) {
        file >> arr[i];
    }
    file.close();
}

int main() {
    int arr[] = {3, 7, 1, 9, 2, 8, 5, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printArray(arr, n);
    
    gnomeSort(arr, n);
    
    printArray(arr, n);
    
    mergeSort(arr, 0, n-1);
    
    printArray(arr, n);
    
    printToFile(arr, n, "sorted_array.txt");
    
    int arr2[n];
    readFromFile(arr2, n, "sorted_array.txt");
    
    printArray(arr2, n);
    
    return 0;
}
