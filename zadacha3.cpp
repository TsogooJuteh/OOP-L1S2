#include<iostream>

using namespace std;

class A1
{
protected:
	int a1;
public:
	A1() {
		a1 = -1;
	}
	A1(int v1) {
		a1 = v1;
	}
	virtual void print() {
		cout << "A1" << endl;
	}
	virtual void show() {
		cout << a1 << endl;
	}
};
class B1 : virtual public A1
{
protected:
	int b1;
public:
	B1() {
		b1 = -1;
	}
	B1(int v1, int v2) : A1(v1) {
		b1 = v2;
	}
	virtual void print() {
		cout << "B1" << endl;
	}
	virtual void show() {
		cout << "b1 = " << b1 << "\na1 = " << a1 << endl;
	}
};
class B2 : virtual public A1
{
protected:
	int b2;
public:
	B2() {
		b2 = -1;
	}
	B2(int v1, int v2) : A1(v1) {
		b2 = v2;
	}
	virtual void print() {
		cout << "B2";
	}
	virtual void show() {
		cout << "b2 = " << b2 << "\na1 = " << a1 << endl;
	}
};
class C1 : virtual public B1, virtual public B2
{
protected:
	int c1;
public:
	C1(int v1, int v2, int v3, int v4, int v5) : A1(v1), B1(v1, v2), B2(v3, v4) {
		c1 = v5;
	}
	virtual void print() {
		cout << "C1";
	}
	virtual void show() {
		cout << "c1 = " << c1 << "\nb1 = " << b1 << "\nb2 = " << b2 << "\na1 = " << a1 << endl;
	}
};
class C2 : virtual public B1, virtual public B2
{
protected:
	int c2;
public:
	C2(int v1, int v2, int v3, int v4, int v5) : A1(v1), B1(v1, v2), B2(v3, v4) {
		c2 = v5;
	}
	virtual void print() {
		cout << "C2";
	}
	virtual void show() {
		cout << "c2 = " << c2 << "\nb1 = " << b1 << "\nb2 = " << b2 << "\na1 = " << a1 << endl;
	}
};
class C3 : virtual public B1, virtual public B2
{
protected:
	int c3;
public:
	C3(int v1, int v2, int v3, int v4, int v5) : A1(v1), B1(v1, v2), B2(v3, v4) {
		c3 = v5;
	}
	virtual void print() {
		cout << "C3";
	}
	virtual void show() {
		cout << "c3 = " << c3 << "\nb1 = " << b1 << "\nb2 = " << b2 << "\na1 = " << a1 << endl;
	}
};
int main()
{
	//B1 test(1, 2);
	//test.show();
	//test.print();
	//C1 test(8, 9, 69, 57, 7);
	//A1* ptr = &test; 
	//ptr->show(); 
	//ptr->print();
	return 0;
}