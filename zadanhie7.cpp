#include <iostream>
#include <vector>
#include <fstream>


void read_from_file(std::vector<int> &arr, std::string namefile)
{
    std::ifstream myfile; 
    myfile.open(namefile);
    int num;
    //std::string line;
    while(myfile >> num)
    {
        
        arr.push_back(num);
        
    }
}
void bubble_sort(std::vector<int> &arr)
{
    for(int i = 0; i < arr.size(); i++)
    {
        bool flag_swap = false;      
        for(int j = i; j < arr.size(); j++)
        {
            if (arr[i] < arr[j])
            {
                flag_swap = true;
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
        if (!flag_swap)
        {
            return;
        }
    }
}

void merge( std::vector<int> &a, int left, int mid, int right) {
    int subArrayOne = mid - left + 1;
    int subArrayTwo = right - mid;
    
    std::vector<int> leftArray(subArrayOne);
    std::vector<int> rightArray(subArrayTwo);
    for (int i = 0; i < subArrayOne; i++) {
        leftArray[i] = a[left + i];
    }

    for (int j = 0; j < subArrayTwo; j++) {
        rightArray[j] = a[mid + j + 1];
    }
    int indexOfSubArrOne = 0;
    int indexOfSubArrTwo = 0;
    
    int indexOfMergeArr = left;
    while (indexOfSubArrOne < subArrayOne && indexOfSubArrTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrOne] <= rightArray[indexOfSubArrTwo]) {
            a[indexOfMergeArr] = leftArray[indexOfSubArrOne];
            indexOfSubArrOne++;
        } else {
            a[indexOfMergeArr] = rightArray[indexOfSubArrTwo];
            indexOfSubArrTwo++;
        }
        indexOfMergeArr++;
    }
    while (indexOfSubArrOne < subArrayOne) {
        a[indexOfMergeArr] = leftArray[indexOfSubArrOne];
        indexOfMergeArr++;
        indexOfSubArrOne++;
    }
    while (indexOfSubArrTwo < subArrayTwo) {
        a[indexOfMergeArr] = rightArray[indexOfSubArrTwo];
        indexOfMergeArr++;
        indexOfSubArrTwo++;
    }

    leftArray.clear();
    rightArray.clear();
}

void merge_sort(std::vector<int> &arr, int begin, int end) {
    
    if (begin >= end) {
        return;
    }
    int mid = begin + (end - begin) / 2;
    
    merge_sort(arr, begin, mid);
    
    merge_sort(arr, mid+1, end);
    
    merge(arr, begin, mid, end);
    
}

void print_to_file(std::vector<int>& arr, std::string namefile)
{
    std::ofstream m_file;
    m_file.open(namefile);
    for(int i = 0; i < arr.size(); i++)
    {
        m_file << arr[i] << " ";
    }
    m_file.close();
}
int main()
{
    std::vector<int> arr;
    std::string namefile1 = "text-list0.txt";
    std::string namefile2 = "text-list1.txt";

    read_from_file(arr, namefile1);
    merge_sort(arr, 0, arr.size() - 1);
    bubble_sort(arr);
    print_to_file(arr, namefile2);
    return 0;
}
