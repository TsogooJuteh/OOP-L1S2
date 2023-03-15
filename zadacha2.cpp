#include <iostream>

using namespace std;

class MyArrayParent {
protected:
	int capacity;
	int count;
	double* arr;
public:
	MyArrayParent(int cap) {
		capacity = cap;
		count = 0;
		arr = new double[cap];
	}
	MyArrayParent(MyArrayParent& v) {
		capacity = v.capacity;
		count = v.count;
		arr = new double[v.capacity];
		for (int i = 0; i < count; i++) {
			arr[i] = v.arr[i];
		}
	}
	MyArrayParent(int cap, int co, double* ptr) {
		capacity = cap;
		count = co;
		arr = new double[cap];
		for (int i = 0; i < co; i++) {
			arr[i] = ptr[i];
		}
	}
	~MyArrayParent() {
		if (arr != 0) {
			delete[] arr;
			arr = 0;
		}
	}
	virtual void push(double value) {
		if (count < capacity) {
			arr[count] = value;
			count++;
		}
	}
	double& operator[](int index) {
		if (index < 0 || index >= count) {
			;
		}
		return arr[index];
	}
	void operator=(MyArrayParent& v) {
		capacity = v.capacity;
		count = v.count;
		for (int i = 0; i < count; i++) {
			arr[i] = v[i];
		}
	}
	void RemoveLastValue() {
		if (count >= 0) {
			for (int i = 0; i < count; i++) {
				if (arr[i] == arr[count - 1]) {
					for (int j = i; j < count; j++) {
						arr[j] = arr[j + 1];
					}
					break;
				}
			}
			count--;
		}
	}
	double IndexOf(double n) {
		for (int i = 0; i < count; i++) {
			if (arr[i] == n) {
				return i;
			}
		}
		return -1;
	}
	void display() {
		for (int i = 0; i < count; i++)
		{
			cout << arr[i] << " ";
		}
	}

};

class MyArrayChild : public MyArrayParent {
public:
	MyArrayChild(int capacity) : MyArrayParent(capacity) {
	}
	MyArrayChild(int capacity, int count, double* arr) : MyArrayParent(capacity, count, arr) {
	}
	~MyArrayChild() {

	}
	void RemoveAt(int index) {
		for (int i = index + 1; i < count; i++) {
			arr[i - 1] = arr[i];
		}
		count--;
	}
	void InsertAt(int index, double value) {
		count++;
		for (int i = count - 1; i >= index; i--) {
			arr[i + 1] = arr[i];
		}
		arr[index] = value;
	}
	void display() {
		for (int i = 0; i < count; i++)
		{
			cout << arr[i] << " ";
		}
	}
	void operator+(int n) {
		int oldCount = count;
		count++;
		if (count > capacity) {
			capacity = count;
			double* temp = new double[capacity];
			for (int i = 0; i < oldCount; i++) {
				temp[i] = arr[i];
			}
			delete[] arr;
			arr = temp;
		}
		arr[oldCount] = n;
	}
	void moveNegative() {
		int numNegatives = 0;
		for (int i = 0; i < count; i++) {
			if (arr[i] < 0) {
				numNegatives++;
			}
		}
		if (numNegatives > 0) {
			int oldCount = count;
			count += numNegatives;
			if (count > capacity) {
				capacity = count;
				double* temp = new double[capacity];
				for (int i = 0; i < oldCount; i++) {
					temp[numNegatives + i] = arr[i];
				}
				delete[] arr;
				arr = temp;
			}
			else {
				for (int i = oldCount - 1; i >= 0; i--) {
					arr[i + numNegatives] = arr[i];
				}
			}
			for (int i = 0; i < numNegatives; i++) {
				arr[i] = 0;
			}
		}
	}
	/*MyArrayChild MoveNeg() {
		int negCount = 0;
		for (int i = 0; i < count; i++) {
			if (arr[i] < 0) {
				negCount++;
			}
		}
		MyArrayChild newArr(count + negCount);
		int newPos = negCount;
		for (int i = 0; i < count; i++) {
			if (arr[i] < 0) {
				newArr[newPos++] = 0;
			}
			else {
				newArr[newPos++] = arr[i];
			}
		}
		return newArr;
	}*/
};

class MySortedArray : public MyArrayChild {
public:
	MySortedArray(int capacity, int count, double* arr) : MyArrayChild(capacity, count, arr) {

	}
	MySortedArray(int capacity) : MyArrayChild(capacity) {

	}
	~MySortedArray() {

	}
	void push(double value) {
		if (count >= capacity) {
			cout << "full\n";
			return;
		}
		int index = count;
		while (index > 0 && arr[index - 1] > value) {
			arr[index] = arr[index - 1];
			index--;
		}
		arr[index] = value;
		count++;
	}
	void display() {
		for (int i = 0; i < count; i++)
		{
			cout << arr[i] << " ";
		}
	}
	double IndexOf(double n) {
		for (int i = 0; i < count; i++) {
			if (arr[i] == n) {
				return i;
			}
		}
		return -1;
	}
};

int main() {
	double arr[] = { 10, -10,9,-5,5 };
	double* ptr;
	ptr = arr;
	MyArrayParent a2(100, 5, ptr);
	//a2.display();
	MyArrayParent a1(a2);
	//a1.RemoveLastValue();
	//a1.display();

	MyArrayChild mac(100, 5, ptr);
	//mac.operator+(55);
	//mac.display();

	MyArrayChild a3(100, 5, ptr);
	//a3.display();
	//a3.RemoveAt(2);
	//a3.display();
	//a3.InsertAt(6, 10);
	//a3.display();

	MyArrayChild a4(100, 5, ptr);
	//a4.moveNegative();
	//a4.display();
	MySortedArray a5(100, 5, ptr);
	//a5.push(10000);
	//a5.display();

	return 0;
}