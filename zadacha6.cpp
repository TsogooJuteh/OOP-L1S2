#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <cstring>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class Exception : public std::exception {
protected:
	char* str;
public:
	Exception(const char* s) {
		str = new char[strlen(s) + 1];
		if (str != NULL) {
			strcpy(str, s);
		}
	}
	Exception(const Exception& e) {
		str = new char[strlen(e.str) + 1];
		if (str != NULL) {
			strcpy(str, e.str);
		}
	}
	~Exception() {
		if (str != NULL) {
			delete[] str;
		}
	}
	virtual void print() const {
		cout << "Exception: " << str << endl;
	}
};

class Programmer {
protected:
    string firstName;
    string lastName;
    string email;
    string skype;
    string telegram;
    string mainProgrammingLanguage;
    string placeofWork;
    int level;
public:
    Programmer(string firstName, string lastName, string email, string skype, string telegram, string mainProgrammingLanguage, string placeofWork, int level) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->email = email;
        this->skype = skype;
        this->telegram = telegram;
        this->mainProgrammingLanguage = mainProgrammingLanguage;
        this->placeofWork = placeofWork;
        this->level = level;
    }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getEmail() const { return email; }
    string getSkype() const { return skype; }
    string getTelegram() const { return telegram; }
    string getMainProgrammingLanguage() const { return mainProgrammingLanguage; }
    string getPlaceofWork() const { return placeofWork; }
    int getLevel() const { return level; }
    string stringify() {
        return firstName + ", " + lastName + ", " + email + ", " + skype + ", " + telegram + ", " + mainProgrammingLanguage + ", " + placeofWork + ", " + to_string(level);
    }
    bool emailMatches(string email) {
        return this->email == email;
    }
    friend istream& operator >> (istream& in, Programmer& p);
    friend ostream& operator << (ostream& out, Programmer& p);
};

ostream& operator<<(ostream& out, Programmer& p)
{
    out << p.lastName << ", " << p.firstName << endl;
    out << p.email << endl;
    out << p.skype << endl;
    out << p.telegram << endl;
    out << p.mainProgrammingLanguage << endl;
    out << p.placeofWork << endl;
    out << p.level << endl;
    return out;
}

istream& operator >> (istream& in, Programmer& p) {
    in >> p.firstName;
    in >> p.lastName;
    in >> p.email;
    in >> p.skype;
    in >> p.telegram;
    in >> p.mainProgrammingLanguage;
    in >> p.placeofWork;
    in >> p.level;
    return in;
}

template <class T>
class Node {
public:
    Node* next;
    Node* prev;
    T info;
    Node(T data) {
        next = prev = nullptr;
        info = data;
    }
    Node(const T& info, Node<T>* prev, Node<T>* next)
        : next(next), prev(prev),  info(info) {}
    T getInfo() { return info; }
    void setInfo(T value) { info = value; }
    Node<T>* getNext() { return next; }
    Node<T>* getPrev() { return prev; }
    void setNext(Node<T>* value) { next = value; }
    void setPrev(Node<T>* value) { prev = value; }
};

template <class T>
class LinkedList {
protected:
    //Node<T>* head;
    //Node<T>* tail;
    //int count;
public:
    Node<T>* head;
    Node<T>* tail;
    int count;
    LinkedList() {
        head = tail = nullptr;
        count = 0;
    }
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void pop_front() = 0;
    virtual void pop_back() = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual void find(string email) = 0;
    virtual void filter(int level) = 0;
};

template<class T>
class DoubleLinkedList : public LinkedList<T> {
protected:
    int count;
    Node<T>* head;
    Node<T>* tail;
    bool typeIsEqualToProgrammer() {
        return typeid(T) == typeid(Programmer*);
    }
public:
    template<class U>
    friend istream& operator >> (istream& in, DoubleLinkedList<U>& list);
    template<class U>
    friend ostream& operator << (ostream& out, DoubleLinkedList<U>& list);
    DoubleLinkedList() {
        head = tail = nullptr;
        count = 0;
    }
    DoubleLinkedList(const T& data) {
        count = 1;
        head = tail = new Node<T>(data);
    }
    ~DoubleLinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    int Count() { return count; }
    Node<T>* First() { return head; }
    Node<T>* Last() { return tail; }
    void setFirst(Node<T>* _head) { head = _head; }
    void printList() {
        Node<T>* temp = this->head;
        int index = 0;
        while (temp != NULL) {
            if (typeIsEqualToProgrammer()) {
                Programmer* casted = dynamic_cast<Programmer*>(temp->getInfo());
                cout << to_string(index) + ": " + casted->stringify() << endl;
            }
            temp = temp->next;
            index++;
        }
        if (temp == NULL) cout << "" << endl;
        delete temp;
    }
    void push_back(T data) {
        Node<T>* node = new Node<T>(data);

        if (head == nullptr) {
            head = tail = node;
        }
        else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }

        count++;
        /*tail->next = new Node<T>(data, tail);
        tail = tail->next;*/
    }
    void push_front(T data) {
        head->prev = new Node<T>(data, nullptr, head);
        head = head->prev;
        count++;
    }
    void pop_front() {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        count--;
    }
    void pop_back() {
        Node<T>* temp = head;
        Node<T>* prev = nullptr;
        while (temp->next != nullptr) {
            prev = temp;
            temp = temp->next;
        }
        if (prev != nullptr)
            prev->next = nullptr;
        if (temp == head)
            head = nullptr;
        delete temp;
        count--;
        /*Node<T>* temp = head;
        Node<T>* prev = nullptr;
        while (temp->next != nullptr) {
            prev = temp;
            temp = temp->next;
        }
        if (prev != nullptr)
            prev->next = nullptr;
        if (temp == head)
            head = nullptr;
        delete temp;
        count--;*/
    }
    void insert(int index, T data) override {
        if (index<0 || index>count) throw Exception("Invalid Index");
        if (index == 0) {
            push_front(data);
            return;
        }
        else if (index == count - 1) {
            push_back(data);
            return;
        }
        if (head == nullptr) head = tail = new Node<T>(data);
        else {
            Node<T>* current = head;
            int current_index = 0;
            while (current_index != index) {
                current = current->next;
                current_index++;
            }
            Node<T>* prev_ptr = current->prev;
            current->prev = prev_ptr->next = new Node<T>(data, current->prev, current);
        }
        count++;
    }
    void remove(const int index) override {
        if (index<0 || index>count)
            throw Exception("Invalid Index");

        if (index == 0) {
            pop_front();
            return;
        }
        else if (index == count - 1) {
            pop_back();
            return;
        }
        Node<T>* current = head;
        int current_index = 0;
        while (current_index != index) {
            current = current->next;
            current_index++;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        count--;
    }
    void find(string email) {
        Node<T>* temporaryNode = this->head;
        while (temporaryNode != NULL) {
            T info = temporaryNode->getInfo();

            if (typeid(T) == typeid(Programmer*)) {
                Programmer* casted = dynamic_cast<Programmer*>(info);
                if (casted->emailMatches(email)) {
                    cout << casted->stringify() << endl;
                    return;
                }
            }
            temporaryNode = temporaryNode->next;
        }
        cout << "No matches were found. " << endl;
    }
    void filter(int level) {
        Node<T>* temporaryNode = this->head;
        while (temporaryNode != NULL) {
            T info = temporaryNode->getInfo();
            if (typeIsEqualToProgrammer()) {
                Programmer* casted = dynamic_cast<Programmer*>(info);
                if (casted->getLevel() == level) {
                    cout << casted->stringify() << endl;
                    return;
                }
            }
            temporaryNode = temporaryNode->next;
        }
    }
    ofstream& save(ofstream& out) {
        if (head == nullptr) {
            cout << "List is empty\n";
            return out;
        }
        if (out) {
            out << count << '\n' << count << '\n';
            Node<T>* current = head;

            while (current != nullptr) {
                out << current->info << ' ';
                current = current->next;
                if (current != nullptr) {
                    out << "\n " << *(current->info);
                }
            }
        }
        return out;
    }
    DoubleLinkedList<T>& load(ifstream& in) {
        if (in) {
            int temp_size, count;
            in >> count >> temp_size;

            for (int i = 0; i < temp_size; i++) {
                T _data;
                in >> _data;
                push_back(_data);
            }
        }
        return *this;
    }

};

template<class T>
istream& operator >> (istream& in, DoubleLinkedList<T>& list) {
    T value;
    while (in >> value) {
        list.push_back(value);
    }
    return in;
}

template<class T>
ostream& operator << (ostream& out, DoubleLinkedList<T>& list) {
    Node<T>* temp = list.head;
    while (temp != nullptr) {
        out << temp->getInfo() << ' ';
        temp = temp->getNext();
    }
    return out;
}

int main() {
    DoubleLinkedList<Programmer*> programmers;
    Programmer* p1 = new Programmer("Smith", "John", "johnsmith@gmail.com", "johnsmith", "johnsmith", "Python", "Google", 7);
    Programmer* p2 = new Programmer("Doe", "Jane", "janedoe@gmail.com", "janedoe", "janedoe", "C++", "Facebook", 8);
    Programmer* p3 = new Programmer("Builder", "Bob", "bob123@gmail.com", "bobthebuilder", "bobthebuilder", "Rust", "Netflix", 9);

    programmers.push_back(p1);
    programmers.push_back(p2);
    programmers.push_back(p3);
    programmers.printList();

    programmers.find("johnsmith@gmail.com");
    programmers.find("bob123@gmail.com");
    //programmers.insert(1, p3);
    programmers.printList();
    
    ofstream fout;
    fout.open("text.txt", ios::out);
    if (fout) {
        programmers.save(fout);
        fout.close();
    }
    
    //programmers.find("johnsmith@gmail.com");
    //programmers.filter(7);

    //programmers.remove(1);
    ///*programmers.printList();*/

    programmers.pop_back();
    programmers.pop_back();
    programmers.pop_back();

    delete p1;
    delete p2;
    delete p3;

    return 0;
}