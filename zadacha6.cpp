#include<iostream>
#include<typeinfo>
#include<cstring>
#include<string>
#include<fstream>

using namespace std;

class Exception : public std::exception {
protected:
	char* str;
public:
	Exception(const char* s) {
		str = new char[strlen(s) + 1];
        if (str != NULL) {
            strcpy_s(str, strlen(s) + 1, s);
        }
	}
	Exception(const Exception& e) {
		str = new char[strlen(e.str) + 1];
        if (str != NULL) {
            strcpy_s(str, strlen(e.str) + 1, e.str);
        }
	}
	~Exception() {
        if(str != NULL) {
		    delete[] str;
        }
	}
	virtual void print() const {
		cout << "Exception: " << str << endl;
	}
};

class Programmer {
protected:
    string lastname;
    string firstname;
    string email;
    string skype;
    string telegram;
    string mainprogramminglang;
    string placeofwork;
    int level;
public:
    Programmer() : lastname(""), firstname(""), email(""), skype(""), telegram(""), mainprogramminglang(""), placeofwork(""), level(0) {}

    friend ostream& operator <<(ostream& os, const Programmer& p);
    friend istream& operator >> (istream& os, Programmer& p);
};

ostream& operator << (ostream& os, const Programmer& p) {
    os << p.lastname << ", " << p.firstname << endl;
    os << p.email << endl;
    os << p.skype << endl;
    os << p.telegram << endl;
    os << p.mainprogramminglang << endl;
    os << p.placeofwork << endl;
    os << p.level << endl;
    return s;
}

istream& operator >> (istream& os, Programmer& p) {
    getline(os, p.lastname);
    getline(os, p.firstname);
    getline(os, p.email);
    getline(os, p.skype);
    getline(os, p.telegram);
    getline(os, p.mainprogramminglang);
    getline(os, p.placeofwork);
    os >> p.level;
    return os;
}

template<class T>
class Element {
public:
    Element* next;
    Element* prev;
    T info;

    Element(T data) {
        next = prev = nullptr;
        info = data;
    }

    T getInfo() { return info; }
    void setInfo(T value) { info = value; }
    Element<T>* getNext() { return next; }
    void setNext(Element<T>* value) { next = value; }
};

template<class T>
class LinkedList {
protected:
    Element<T>* head;
    int count;
public:
    LinkedList() {
        head = nullptr;
        count = 0;
    }

    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T find(string email) = 0;

    bool isEmpty() { return (count == 0); }
    virtual ~LinkedList() {
        while (!isEmpty()) {
            pop();
        }
    }
};

template<class T>
class SinglyLinkedList : public LinkedList<T> {
public:
    SinglyLinkedList() : LinkedList<T>() {}

    void push(T value) override {
        Element<T>* newElem = new Element<T>(value);
        newElem->setNext(this->head);
        this->head = newElem;
        this->count++;
    }

    T pop() override {
        if (this->isEmpty()) {
            cout << "List is empty\n";
            return nullptr;
        }

        Element<T>* toDelete = this->head;
        T info = toDelete->getInfo();
        this->head = this->head->getNext();
        delete toDelete;
        this->count--;
        return info;
    }

    void insert(int index, T value) override {
        if (index < 0 || index > this->count) {
            throw Exception("Invalid Index");
        }

        if (index == 0) {
            push(value);
            return;
        }

        Element<T>* newElem = new Element<T>(value);
        Element<T>* prev = this->head;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->getNext();
        }
        newElem->setNext(prev->getNext());
        prev->setNext(newElem);
        this->count++;
    }

    void remove(int index) override {
        if (index < 0 || index >= this->count) {
            throw Exception("Invalid Index");
        }

        if (index == 0) {
            pop();
            return;
        }

        Element<T>* prev = this->head;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->getNext();
        }

        Element<T>* toDelete = prev->getNext();
        prev->setNext(toDelete->getNext());
        delete toDelete;
        this->count--;
    }

    T find(string email) override {
        Element<T>* temp = this->head;
        while (temp != nullptr) {
            if (temp->getInfo()->email == email) {
                return temp->getInfo();
            }
            temp = temp->getNext();
        }
        cout << "No programmer found with this email\n";
        return nullptr;
    }
    SinglyLinkedList<T>* filter(int(*condition)(T)) {
        SinglyLinkedList<T>* newList = new SinglyLinkedList<T>();
        Element<T>* temp = this->head;
        while (temp != nullptr) {
            if (condition(temp->getInfo())) {
                newList->push(temp->getInfo());
            }
            temp = temp->getNext();
        }
        return newList;
    }

    ~SinglyLinkedList() override {
        while (!this->isEmpty()) {
            this->pop();
        }
    }
};

int main() {
    SinglyLinkedList<Programmer*> programmers;
    Programmer* p1 = new Programmer("Smith", "John", "johnsmith@gmail.com", "johnsmith", "johnsmith", "Python", "Google", 7);
    Programmer* p2 = new Programmer("Doe", "Jane", "janedoe@gmail.com", "janedoe", "janedoe", "C++", "Facebook", 8);
    programmers.push(p1);
    programmers.push(p2);
    cout << *programmers.find("johnsmith@gmail.com") << "\n";
    cout << *programmers.find("janedoe@gmail.com") << "\n";
    programmers.pop();
    programmers.pop();
    return 0;
}