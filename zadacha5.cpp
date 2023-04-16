#include<iostream>
#include<fstream>
#include<typeinfo>

using namespace std;

class Exception : public std::exception {
protected:
	char* str;
public:
	Exception(const char* s) {
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e) {
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception() {
		delete[] str;
	}
	virtual void print() {
		cout << "Exception: " << str << endl;
	}
};

class BaseMatrix {
protected:
	double** ptr;
	int height;
	int width;
public:
	BaseMatrix(int Height, int Width) {
		if (Height <= 0 || Width <= 0) {
			throw Exception("Non-positive size of matrix");
		}
		height = Height;
		width = Width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++) {
			ptr[i] = new double[width];
		}
	}
	BaseMatrix(const BaseMatrix& M) {
		height = M.height;
		width = M.width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++) {
			ptr[i] = new double [width];
			for (int j = 0; j < width; j++) {
				ptr[i][j] = M.ptr[i][j];
			}
		}
	}
	BaseMatrix(double** arr, int Height, int Width) {
		if (Height <= 0 || Width <= 0) {
			throw Exception("Non-Positive size of matrix");
		}
		height = Height;
		width = Width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++) {
			ptr[i] = new double[width];
			for (int j = 0; j < width; j++) {
				ptr[i][j] = arr[i][j];
			}
		}
	}
	BaseMatrix operator=(const BaseMatrix& M) {
		if (this != &M) {
			if (ptr != NULL) {
				for (int i = 0; i < M.height; i++) {
					delete[] ptr[i];
				}
				delete[] ptr;
				ptr = NULL;
			}
			height = M.height;
			width = M.width;
			ptr = new double* [height];
			for (int i = 0; i < height; i++) {
				ptr[i] = new double [width];
				for (int j = 0; j < width; j++) {
					ptr[i][j] = M.ptr[i][j];
				}
			}
		}
		return *this;
	}
	~BaseMatrix() {
		if (ptr != NULL) {
			for (int i = 0; i < height; i++) {
				delete[] ptr[i];
			}
			delete[] ptr;
			ptr = NULL;
		}
	}
	void input() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cin >> ptr[i][j];
			}
		}
	}
	void print() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << ptr[i][j] << " ";
			}
			cout << "\n";
		}
	}
	double& operator()(int row, int column) {
		if (row < 0 || column < 0 || row >= height || column >= width) throw Exception("Index is out of bounds");
		return ptr[row][column];
	}
	void removezerocolumns() {
		int numzerocols = 0;
		for (int j = 0; j < width; j++) {
			bool hasZero = false;
			for (int i = 0; i < height; i++) {
				if (ptr[i][j] == 0) {
					hasZero = true;
					break;
				}
			}
			if (hasZero) {
				numzerocols++;
			}
			else if (numzerocols > 0) {
				for (int i = 0; i < height; i++) {
					ptr[i][j - numzerocols] = ptr[i][j];
					ptr[i][j] = 0;
				}
			}
		}
		width -= numzerocols;
	}
//	void removezerocolumns() {
//		int newwidth = width;
//		for (int j = width - 1; j >= 0; j--) {
//			bool haszero = false;
//			for (int i = 0; i < height; i++) {
//				if (ptr[i][j] != 0) {
//					haszero = true;
//				}
//				if (!haszero) {
//					ptr[i][width] = ptr[i][j];
//				}
//			}
//			if (!haszero) {
//				for (int i = 0; i < height; i++) {
//					for (int k = width - 1; k >=0; k--) {
//						ptr[i][k] = ptr[i][k - 1];
//					}
//					ptr[i][0] = ptr[i][width];
//				}
//			}
//		}
//	}
	friend ostream& operator << (ostream& ustream, BaseMatrix obj);
	friend istream& operator >> (istream& ustream, BaseMatrix obj);
};

class DerClass : public BaseMatrix {
public:
	DerClass(int Height, int Width) : BaseMatrix(Height, Width) {};
	DerClass(const DerClass& M) : BaseMatrix(M) {};
	void fillArray() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				ptr[i][j] = i * j;
			}
		}
	}
	void print() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << ptr[i][j] << " ";
			}
			cout << '\n';
		}
	}
};

ostream& operator << (ostream& ustream, BaseMatrix obj) {
	if (typeid(ustream).name() == typeid(ofstream).name()) {
		ustream << obj.height << " " << obj.width << endl;
		for (int i = 0; i < obj.height; i++) {
			for (int j = 0; j < obj.width; j++) {
				ustream << obj.ptr[i][j] << " ";
			}
			ustream << '\n';
		}
	}
	for (int i = 0; i < obj.height; i++) {
		for (int j = 0; j < obj.width; j++) {
			ustream << obj.ptr[i][j] << " ";
		}
		ustream << endl;
	}
	return ustream;
}

istream& operator >> (istream& ustream, BaseMatrix obj) {
	if (typeid(ustream) == typeid(ifstream)) {
		ustream >> obj.height >> obj.width;
	}
	for (int i = 0; i < obj.height; i++) {
		for (int j = 0; j < obj.width; j++) {
			ustream >> obj.ptr[i][j];
		}
	}
	return ustream;
}

ostream& my_manip(ostream& s) {
	s.precision(4);
	s.fill('%');
	s.width(10);
	return s;
}

int main() {
	try {
		BaseMatrix matrix(-2, 3);
	}
	catch (Exception& e) {
		cout << "\nException has been caught: " << "\n"; e.print();
	}
	cout << "\n";
	DerClass Dm(4,3);
	Dm.fillArray();
	Dm.print();
	BaseMatrix BM(12,12);
	BM.input();
	BM.print();
	BM.removezerocolumns();
	BM.print();
	//BaseMatrix M;
	//cin >> M;
	//ofstream fout("out.txt");
	//if (fout.is_open()) {
	//	fout << M;
	//	fout.close();
	//}
	//ifstream fin("out.txt");
	//BaseMatrix M1;
	//if (fin) {
	//	fin >> M1;
	//	fin.close();
	//}
	//cout << M1;
	//char c1;
	//cin >> c1;
	return 0;
}