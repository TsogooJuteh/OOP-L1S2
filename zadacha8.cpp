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
			strcpy_s(str, strlen(s) + 1, s);
		}
	}
	Exception(const Exception& e) {
		str = new char[strlen(e.str) + 1];
		if (str != NULL) {
			strcpy_s(str, strlen(e.str) + 1 , e.str);
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

template<class T>
class Node {
public:
	T key;
	Node* left;
	Node* right;
	Node<T>(T key): key(key), left(nullptr), right(nullptr){}
	Node<T>() {
		key = 0;
		left = right = nullptr;
	}
	template<class U>
	friend ostream& operator << (ostream& out, const Node<U>& node);
	template<class U>
	friend istream& operator >> (istream& in, Node<U>& node);
};

template<class T>
ostream& operator<<(ostream& out, const Node<T>& node) {
	out << "Key: " << node.key;
	if (node.left != nullptr)
		out << " | Left child: " << node.left->key;
	if (node.right != nullptr)
		out << " | Right child: " << node.right->key;
	return out;
}

template<class T>
istream& operator>>(istream& in, Node<T>& node) {
	in >> node.key;
	return in;
}

template<class T>
class SplayTree {
protected:
	void savetofilehelper(Node<T>* node, ofstream& file) {
		if (node) {
			savetofilehelper(node->left, file);
			file << node->key << endl;
			savetofilehelper(node->right, file);
		}
	}
	void deleteTree(Node<T>* node) {
		if (node == nullptr) {
			return;
		}
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
public:
	Node<T>* root;
	SplayTree(): root(nullptr) {}
	~SplayTree() {
		deleteTree(root);
	}
	Node<T>* rightrotate(Node<T>* node) {
		if (node == nullptr) {
			throw Exception("cannot rotate a null node");
		}
		Node<T>* newNode = node->left;
		if (newNode == nullptr) {
			throw Exception("Cannot rotate a node, because it has no left child");
		}
		else {
			node->left = newNode->right;
			newNode->right = node;
			return newNode;
		}
	}
	Node<T>* leftrotate(Node<T>* node) {
		if (node == nullptr) {
			throw Exception("Cannot rotate a null node");
		}
		Node<T>* newNode = node->right;
		if (newNode == nullptr) {
			throw Exception("Cannot rotate a node, because it has no right child");
		}
		else {
			node->right = newNode->left;
			newNode->left = node;
			return newNode;
		}
	}
	Node<T>* splay(T key, Node<T>* root) {
		if (!root) return NULL;
		Node<T> header;
		header.left = header.right = NULL;
		Node<T>* LeftTreeMax = &header;
		Node<T>* RightTreeMin = &header;
		while (1) {
			if (key < root->key) {
				if (!root->left) {
					break;
				}
				if (key < root->left->key) {
					root = rightrotate(root);
					if (!root->left) break;
				}
				RightTreeMin->left = root;
				RightTreeMin = RightTreeMin->left;
				root = root->left;
				RightTreeMin->left = NULL;
			}
			else if (key > root->key) {
				if (!root->right) break;
				if (key > root->right->key) {
					root = leftrotate(root);
					if (!root->right) break;
				}
				LeftTreeMax->right = root;
				LeftTreeMax = LeftTreeMax->right;
				root = root->right;
				LeftTreeMax->right = NULL;
			}
			else break;
		}
		LeftTreeMax->right = root->left;
		RightTreeMin->left = root->right;
		root->left = header.right;
		root->right = header.left;
		return root;
	}
	Node<T>* New_Node(T key) {
		Node<T>* p_node = new Node<T>;
		if (!p_node) {
			throw Exception("Out of Memory");
		}
		p_node->key = key;
		p_node->left = p_node->right = NULL;
		return p_node;
	}
	Node<T>* Insert(T key, Node<T>* root) {
		static Node<T>* p_node = NULL;
		if (!p_node) p_node = New_Node(key);
		else p_node->key = key;
		if (!root) {
			root = p_node;
			p_node = NULL;
			return root;
		}
		root = splay(key, root);
		if (key < root->key) {
			p_node->left = root->left;
			p_node->right = root;
			root->left = NULL;
			root = p_node;
		}
		else if (key > root->key) {
			p_node->right = root->right;
			p_node->left = root;
			root->right = NULL;
			root = p_node;
		}
		else return root;
		p_node = NULL;
		return root;
	}
	Node<T>* Delete(T key, Node<T>* root) {
		Node<T>* temp;
		if (!root) return NULL;
		root = splay(key, root);
		if (key != root->key) return root;
		else {
			if (!root->left) {
				temp = root;
				root = root->right;
			}
			else {
				temp = root;
				root = splay(key, root->left);
				root->right = temp->right;
			}
			delete temp;
			return root;
		}
	}
	Node<T>* search(T key, Node<T>* root) {
		return splay(key, root);
	}
	void InOrder(Node<T>* root) {
		if (root) {
			InOrder(root->left);
			cout << "key: " << root->key;
			if (root->left) cout << " | left child: " << root->left->key;
			if (root->right) cout << " | right child: " << root->right->key;
			cout << "\n";
			InOrder(root->right);
		}
	}
	Node<T>* merge(Node<T>* t1, Node<T>* t2) {
		if (t1 == nullptr) return t2;
		if (t2 == nullptr) return t1;
		t1->key += t2->key;
		t1->left = merge(t1->left, t2->left);
		t2->right = merge(t1->right, t2->right);
		return t1;
	}
	void save(const char* c) {
		ofstream infile(c);
		if (!infile.is_open()) {
			throw Exception("Failed to open file");
		}
		savetofilehelper(root, infile);
		infile.close();
	}
	Node<T>& load(ifstream& in) {
		if (in) {
			T key;
			while (in >> key) {
				root = Insert(key, root);
			}
		}
		return *this;
	}
	template<class U>
	friend ostream& operator << (ostream& out, const SplayTree<U>& st);
	template<class U>
	friend istream& operator >> (istream& in, SplayTree<U>& st);
};

template<class T>
void writeKeysInOrder(Node<T>* node, ostream& out) {
	if (node) {
		writeKeysInOrder(node->left, out);
		out << node->key;
		if (node->left) out << " | left child: " << node->left->key;
		if (node->right) out << " | right child: " << node->right->key;
		out << endl;
		writeKeysInOrder(node->right, out);
	}
}

template<class T>
ostream& operator<<(ostream& out, const SplayTree<T>& st) {
	writeKeysInOrder(st.root, out);
	return out;
}

template<class T>
istream& operator >> (istream& in, SplayTree<T>& st) {
	T key;
	while (in >> key) {
		st.root = st.Insert(key, st.root);
	}
	return in;
}

int main() {
	//SplayTree<int> st;
	//ifstream fin("test.txt");
	//if (fin) {
	//	fin >> st;
	//	fin.close();
	//}
	//else {
	//	cout << "Couldn't open the file";
	//	return 1;
	//}
	//st.root = st.Insert(10, st.root);
	//st.root = st.Insert(20, st.root);
	//st.root = st.Insert(30, st.root);
	//st.Delete(90, st.root);
	//try {
	//	st.root = st.rightrotate(st.root);
	//}
	//catch (const Exception &e) {
	//	cout << "Exception was caught: " << endl;
	//	e.print();
	//}

	//st.InOrder(st.root);
	//ofstream fout("result.txt");
	//if (fout) {
	//	fout << st;
	//	fout.close();
	//}
	//try {
	//	SplayTree<int> st;
	//	st.root = st.Insert(10, st.root);
	//	st.root = st.Insert(20, st.root);
	//	st.root = st.Insert(30, st.root);
	//	try {
	//		st.root = st.rightrotate(st.root);
	//	}
	//	catch (Exception& e) {
	//		cout << "Exception was caught: ";
	//		e.print();
	//	}
	//	try {
	//		st.root = st.leftrotate(st.root);
	//	}
	//	catch (Exception& e) {
	//		cout << "Exception was caught: ";
	//		e.print();
	//	}
	//	try {
	//		st.root = st.leftrotate(st.root);
	//	}
	//	catch (Exception& e) {
	//		cout << "Exception was caught: ";
	//		e.print();
	//	}
	//	st.InOrder(st.root);
	//}
	//catch (Exception& e) {
	//	cout << "Exception was caught: ";
	//	e.print();
	//}
	return 0;
}