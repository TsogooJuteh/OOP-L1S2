#include <iostream>
#include <fstream>

const int maxn = 1000; // Maximum number of elements in the array

void read_from_file(int arr[], int& size, std::string namefile)
{
    std::ifstream myfile; 
    myfile.open(namefile);
    int num;
    int i = 0;
    while(myfile >> num && i < maxn)
    {
        arr[i++] = num;
    }
    size = i;
    myfile.close();
}

void print_to_file(int arr[], int size, std::string namefile)
{
    std::ofstream m_file;
    m_file.open(namefile);
    for(int i = 0; i < size; i++)
    {
        m_file << arr[i] << " ";
    }
    m_file.close();
}

void gnomesort(int arr[], int size){
	int pos = 0;
	while (pos < size) {
		if (pos == 0 || arr[pos] >= arr[pos - 1]){
			pos++;
		}
		else {
			std::swap(arr[pos], arr[pos - 1]);
			pos--;
		}
	}
}

void merge(int arr[], int left, int mid, int right){
	int n1 = mid - left + 1;
	int n2 = right - mid;
	int L[n1], R[n2];
	for (int i = 0; i < n1; i++) L[i] = arr[left + i];
	for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if(L[i] <= R[j]){
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1){
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2){
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergesort(int arr[], int left, int right){
	if(left >= right){
		return;
	}
	int mid = left + (right - left)/2;
	mergesort(arr, left, mid);
	mergesort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

int main()
{
    int arr[maxn];
    int size;
    std::string namefile1 = "input.txt";
    std::string namefile2 = "output.txt";

    read_from_file(arr, size, namefile1);
	gnomesort(arr, size);
	mergesort(arr, 0, size - 1);
    print_to_file(arr, size, namefile2);

    return 0;
}
