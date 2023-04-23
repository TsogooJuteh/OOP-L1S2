#include<iostream>
#include<typeinfo>
#include<cstring>

using namespace std;

template<class T>
class Element{
protected:
    Element* next;
    Element* prev;
    T info;
public:
    Element(T data){
        next = prev = NULL;
        info = data;
    }
    Element(Element* Next, Element* Prev, T data){
        next = Next;
        prev = Prev;
        info = data;
    }
    Element(const Element& e1){
        next = e1.next;
        prev = e1.prev;
        info = e1.info;
    }
    template<class T1>
    friend ostream& operator << (ostream& s, Element<T1>& e1);
};

template<class T1>
ostream& operator << (ostream& s, Element<T1>& e1){
    s << e1.info;
    return s;
}

template<class T>
class LinkedList{
protected:
    int count;
public:
    LinkeList(){
        head = tail = NULL;
        count = 0;
    }
};