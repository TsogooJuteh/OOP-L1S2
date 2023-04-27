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
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e) {
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception() {
        if(str != NULL) {
		    delete[] str;
        }
	}
	virtual void print() {
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

template<typename T>
class Node : public Programmer {
protected:
    Node* next;
    Node* prev;
    T data;
public:
    Node(T data) {
        next = prev = NULL;
        info = data;
    }
    Node(Node* Next, Node* Prev, T data) {
        next = Next;
        prev = Prev;
        info = data;
    }
    Node(const Node& n1) {
        next = n1.next;
        prev = n1.prev;
        info = n1.data;
    }
    T getInfo() { return info; }
    void setInfo(T value) { info = value; }
    Node<T>* getNext() { return next; }
    void setNext(Node<T>* value) { next = value; }
    Node<T>* getPrev() { return prev; }
    void setPrev(Node<T>* value) { prev = value; }
    template<class T1>
    friend ostream& operator << (ostream& s, Node<T1>& n1);
};

template<class T1>
ostream& operator << (ostream& s, const Node<T1>& n1){
    s << n1.info;
    return s;
}

template<class T>
class LinkedList{
protected:
    int count;
    Node<T>* head;
    Node<T>* tail;
public:
    LinkedList() {
        head = tail = NULL;
        count = 0;
    }
    LinkedList(T arr[], int size) {
        head = NULL;
        tail = NULL;
        for (int i = 0; i < size; i++) {
            push(arr[i]);
        }
    }
    virtual ~LinkedList() {
        while (head != NULL) {
            Node<T>* previous;
            for (Node<T>* current = head; current != NULL) {
                previous = current;
                current = current->getNext();
                delete previous;
            }
        }
    }
    virtual Node<T>* push(T item) {
        Node* newnode = new Node;
        newnode->data = item;
        newnode->next = NULL;
        if (head == NULL) {
            newnode->prev = NULL;
            head = newnode;
            tail = newnode;
        }
        else {
            newnode->prev = tail;
            tail->next = newnode;
            tail = newnode;
        }
    }
    T pop() {
        if (head == NULL) {
            throw Exception("List is empty");
        }
        Node* temp = head;
        T item = temp->data;
        if (head == tail) {
            head = NULL;
            tail = NULL;
        }
        else {
            head = head->next;
            head->prev = NULL;
        }
        delete temp;
        return item;
    }
    void insert(int index, T item) {
        if (index < 0) {
            throw Exception("Invalid index");
        }
        Node* newnode = new Node;
        newnode->data = item;
        if (head == NULL) {
            if (index == 0) {
                newnode->next = NULL;
                newnode->prev = NULL;
                head = newnode;
                tail = newnode;
            }
            else {
                throw Exception("Invalid index");
            }
        }
        else {
            Node* temp = head;
            int i = 0;
            while (i < index && temp != NULL) {
                temp = temp->next;
                i++;
            }
            if (temp == NULL && i == index) {
                newnode->prev = tail;
                newnode->next = NULL;
                tail->next = newnode;
                tail = newnode;
            }
            else if (temp != NULL) {
                newnode->prev = temp->prev;
                newnode->next = temp;
                temp->prev->next = newnode;
                temp->prev = newnode;
            }
            else {
                throw Exception("Invalid index");
            }
        }
    }
    void remove(int index){
        if (head == NULL) {
            throw Exception("List is empty");
        }
        if (index < 0) {
            throw Exception("Invalid index");
        }
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            if (head != NULL) {
                head->prev = NULL;
            }
            else {
                tail = NULL;
            }
        }
    }
    Node<T>* find(T value) {
        Node* temp = head;
        while (temp != NULL) {
            if (temp->data == value) {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }
    LinkedList<T>* filter(int level) {
        LinkedList<T>* newlist = new LinkedList<T>;
        Node* temp = head;
        while (temp != NULL) {
            if (temp->data.level == level) {
                newlist->push(temp->data);
            }
            temp = temp->next;
        }
        return newlist;
    }
    Node<T>& operator[](int index) {
        if(index < 0 || index >= count) throw Exception("Index is out of bound.");
        Node<T>* current = head;
        for (int i = 0; current != NULL && i < index; current = current -> getNext(); i++);
        return *current;
    }
    virtual bool isEmpty() { return (LinkedList<T>::count = 0); }

    template<class T1>
    friend ostream& operator << (ostream& s, LinkedList<T1>& e1);
    virtual void filter(LinkedList<T>* ptr) {
        for (Element<T>* current = head; current != NULL; current = current->getNext()) {
            if () {
                ptr->push(*current);
            }
        }
    }
};

template<class T1>
ostream& operator << (ostream& s, LinkedList<T1>& e1) {
    Element<T1>* current;
    for (current = e1.head; current != NULL; current = current->getNext()) {
        s << *current << "; ";
    }
    return s
}

template<typename T>
class SinglyLinkedList : public LinkedList<T> {
public:
    SinglyLinkedList() : LinkedList<T>() {}
    void push(T item) {
        typename LinkedList<T>::Node* newNode = new typename LinkedList<T>::Node;
        newNode->data = item;
        newNode->next = NULL;
        if (LinkedList<T>::head == NULL) {
            LinkedList<T>::tail = newNode;
        }
        else {
            newNode->next = LinkedList<T>::head;
        }
        LinkedList<T>::head = newNode;
    }
    T pop() {
        if (LinkedList<T>::head == NULL) {
            throw "List is empty";
        }
        typename LinkedList<T>::Node* temp = LinkedList<T>::head;
        T item = temp->data;
        if (LinkedList<T>::head == LinkedList<T>::tail) {
            LinkedList<T>::head = NULL;
            LinkedList<T>::tail = NULL;
        }
        else {
            LinkedList<T>::head = LinkedList<T>::head->next;
        }
        delete temp;
        return item;
    }
    void insert(int index, T item) {
        if (index != 0) {
            throw "Invalid index";
        }
        typename LinkedList<T>::Node* newNode = new typename LinkedList<T>::Node;
        newNode->data = item;
        if (LinkedList<T>::head == nullptr) {
            newNode->next = nullptr;
            LinkedList<T>::head = newNode;
            LinkedList<T>::tail = newNode;
        }
        else {
            newNode->next = LinkedList<T>::head;
            LinkedList<T>::head = newNode;
        }
    }
    void remove(int index) {
        if (LinkedList<T>::head == nullptr) {
            throw "List is empty";
        }
        if (index != 0) {
            throw "Invalid index";
        }
        typename LinkedList<T>::Node* temp = LinkedList<T>::head;
        LinkedList<T>::head = LinkedList<T>::head->next;
        if (LinkedList<T>::head == nullptr) {
            LinkedList<T>::tail = nullptr;
        }
        delete temp;
    }
};

//template<class T>
//class Stack : public LinkedList<T> {
//public:
//    Stack<T>(): LinkedList<T>(){}
//    virtual ~Stack(){}
//
//    virtual Element<T>* pop() {
//        Element<T>* res = LinkedList<T>::tail;
//
//        if (LinkedList<T>::tail == NULL) return NULL;
//
//        if (LinkedList<T>::head == LinkedList<T>::tail) {
//            LinkedList<T>::count = 0;
//            res = LinkedList<T>::count = 0;
//            LinkedList<T>::head = LinkedList<T>::tail = NULL;
//            return res;
//        }
//        Element<T>* current;
//        for (current = LinkedList<T>::head; current->getNext() != LinkedList<T>::tail; current = current->getNext());
//        current->setNext(NULL);
//        LinkedList<T>::count--;
//        LinkedList<T>::tail = current;
//        return res;
//    }
//    virtual Element<T>* push(T value) {
//        Element<T>* newElem = new Element<T>(value);
//        if (LinkedList<T>::tail != NULL) {
//            LinkedList<T>::tail->setNext(newElem);
//            LinkedList<T>::tail = LinkedList<T>::tail->getNext();
//        }
//        else {
//            LinkedList<T>::head = LinkedList<T>::tail = newElem;
//        }
//        LinkedList<T>::count++;
//        return LinkedList<T>::tail;
//    }
//    virtual Element<T>* insert(T value, Element<T>* previous = NULL) {
//        if (previous == NULL) return push(value);
//        Element<T>* inserted = new Element<T>(value);
//        Element<T>* next = previous->getNext();
//        previous->setNext(inserted);
//        inserted->setNext(next);
//        LinkedList<T>::count++;
//        return inserted;
//    }
//};

//class my_class {
//public:
//    int data;
//    my_class(int v = 0) { data = v; }
//    my_class(const my_class& m) { data = m.data; }
//    ~my_class(){}
//    friend ostream& operator << (ostream& s, my_class& value);
//};

int main() {
    SinglyLinkedList my_list;
    my_list.push(5);
    my_list.push(10);
    my_list.push(3);
    my_list.push(8);
    my_list.push(2);
    my_list.push(6);

    // Find the first node with value 3
    Node* found_node = my_list.find(3);
    if (found_node != NULL) {
        cout << "Found node with value 3" << endl;
    }
    else {
        cout << "Node with value 3 not found" << endl;
    }

    // Filter the linked list based on the condition "greater than 5"
    SinglyLinkedList* filtered_list = my_list.filter('>', 5);
    cout << "Filtered list (condition: > 5): ";
    filtered_list->print();
    delete filtered_list;

    // Filter the linked list based on the condition "equal to 10"
    filtered_list = my_list.filter('=', 10);
    cout << "Filtered list (condition: = 10): ";
    filtered_list->print();
    delete filtered_list;

    return 0;
}