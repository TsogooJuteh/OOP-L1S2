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
	Exception& operator=(const Exception& other) {
        if (this != &other) {
            delete[] str;
            str = new char[strlen(other.str) + 1];
            strcpy(str, other.str);
        }
        return *this;
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
	Node<T>(T key): key(key), left(NULL), right(NULL){}
	Node<T>() {
		key = 0;
		left = right = NULL;
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

template<class T>
class AVLNode : public Node<T> {
public:
	int height;
	T key;
	AVLNode<T>* left;
	AVLNode<T>* right;
	AVLNode(T key): Node<T>(key), height(1) {}
	AVLNode<T>() {
		key = 0;
		left = right = nullptr;
		height = 0;
	}
	template<class U>
	friend ostream& operator << (ostream& out, const AVLNode<U>& avlnode);
	template<class U>
	friend istream& operator >> (istream& in, AVLNode<U>& avlnode);
};

template<class T>
ostream& operator << (ostream& out, const AVLNode<T>& avlnode) {
	out << "Key: " << avlnode.key;
	if (avlnode.left != nullptr)
		out << " | Left child: " << avlnode.left->key;
	if (avlnode.right != nullptr)
		out << " | Right child: " << avlnode.right->key;
	return out;
}

template<class T>
istream& operator >> (istream& in, AVLNode<T>& avlnode) {
	in >> avlnode.key;
	return in;
}

template<class T>
class AVLTree {
protected:
	void deleteTree(AVLNode<T>* avlnode) {
		if (avlnode == nullptr) {
			return;
		}
		deleteTree(avlnode->left);
		deleteTree(avlnode->right);
		delete avlnode;
	}
	void savetofilehelper(AVLNode<T>* avlnode, ofstream& file) {
		if (avlnode) {
			savetofilehelper(avlnode->left, file);
			file << avlnode->key << endl;
			savetofilehelper(avlnode->right, file);
		}
	}
	template<class U>
	void writeKeysInOrder(AVLNode<U>* avlnode, ostream& out) {
		if (avlnode) {
			writeKeysInOrder(avlnode->left, out);
			out << avlnode->key;
			if (avlnode->left) out << " | left child: " << avlnode->left->key;
			if (avlnode->right) out << " | right child: " << avlnode->right->key;
			out << endl;
			writeKeysInOrder(avlnode->right, out);
		}
	}
public:
	AVLNode<T>* root;
	AVLTree() : root(nullptr) {}
	~AVLTree() {
		deleteTree(root);
	}
	int height(AVLNode<T>* avlnode) {
		if (avlnode == nullptr) return 0;
		return avlnode->height;
	}
	int max(int a, int b) {
		return (a > b) ? a : b;
	}
	AVLNode<T>* newNode(T key) {
		AVLNode<T>* node = new AVLNode<T>();
		node->key = key;
		node->left = NULL;
		node->right = NULL;
		node->height = 1;
		return node;
	}
	AVLNode<T>* rightRotate(AVLNode<T>* y) {
		if (y == nullptr) throw Exception("Cannot rotate a null node\n");
		AVLNode<T>* x = y->left;
		if (x == nullptr) throw Exception("Cannot rotate a node, because it has no left child\n");
		AVLNode<T>* t2 = x->right;
		x->right = y;
		y->left = t2;
		y->height = max(height(y->left), height(y->right) + 1);
		x->height = max(height(x->left), height(x->right) + 1);
		return x;
	}
	AVLNode<T>* leftRotate(AVLNode<T>* x) {
		if (x == nullptr) {
			throw Exception("Cannot rotate a null node");
		}
		AVLNode<T>* y = x->right;
		if (y == nullptr) {
			throw Exception("Cannot rotate a node, because it has no right child");
		}
		AVLNode<T>* t2 = y->left;
		y->left = x;
		x->right = t2;
		x->height = max(height(x->left), height(x->right) + 1);
		y->height = max(height(y->left), height(y->right) + 1);
		return y;
	}
	int getBalance(AVLNode<T>* avlnode) {
		if (avlnode == NULL) return 0;
		return height(avlnode->left) - height(avlnode->right);
	}
	AVLNode<T>* search(T key, AVLNode<T>* root) {
		if (root == nullptr || root->key == key)
			return root;

		if (root->key < key)
			return search(key, root->right);

		return search(key, root->left);
	}
	AVLNode<T>* insert(AVLNode<T>* avlnode, int key) {
		if (avlnode == NULL) return(newNode(key));
		if (key < avlnode->key) avlnode->left = insert(avlnode->left, key);
		else if (key > avlnode->key) avlnode->right = insert(avlnode->right, key);
		else return avlnode;
		avlnode->height = 1 + max(height(avlnode->left), height(avlnode->right));
		int balance = getBalance(avlnode);
		if (balance > 1 && key > avlnode->left->key) {
			avlnode->left = leftRotate(avlnode->left);
			return rightRotate(avlnode);
		}
		if (balance < -1 && key < avlnode->right->key) {
			avlnode->right = rightRotate(avlnode->right);
			return leftRotate(avlnode);
		}
		return avlnode;
	}
	AVLNode<T>* minValueAVLN(AVLNode<T>* avlnode) {
		AVLNode<T>* current = avlnode;
		while (current->left != nullptr) current = current->left;
		return current;
	}
	AVLNode<T>* deletenode(AVLNode<T>* root, int key) {
		if (root == NULL) return root;
		if (key < root->key) root->left = deletenode(root->left, key);
		else if (key > root->key) root->right = deletenode(root->right, key);
		else {
			if ((root->left == NULL) || (root->right == NULL)) {
				AVLNode<T>* temp = root->left ?
								   root->left :
								   root->right;
				if (temp == NULL) {
					temp = root;
					root = NULL;
				}
				else *root = *temp;
				delete temp;
			}
			else {
				AVLNode<T>* temp = minValueAVLN(root->right);
				root->key = temp->key;
				root->right = deletenode(root->right, temp->key);
			}
		}

		if (root == NULL) return root;

		root->height = 1 + max(height(root->left), height(root->right));
		int balance = getBalance(root);
		if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
		if (balance > 1 && getBalance(root->left) < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		if (balance < -1 && getBalance(root->right) > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}
	void preOrder(AVLNode<T>* root) {
		if (root != NULL) {
			cout << root->key << " ";
			preOrder(root->left);
			preOrder(root->right);
		}
	}
	void save(const char* c) {
		ofstream outfile(c);
		if (!outfile.is_open()) {
			throw Exception("Failed to open file");
		}
		savetofilehelper(root, outfile);
		outfile.close();
	}

	AVLNode<T>* load(ifstream& in) {
		if (!in.is_open()) {
			throw Exception("Could not open file");
		}
		int key;
		while (in >> key) {
			root = insert(root, key);
		}
		return root;
	}

	template<class U>
	friend ostream& operator << (ostream& out, AVLTree<U>& avltree);
	template<class U>
	friend istream& operator >> (istream& in, AVLTree<U>& avltree);
};

template<class T>
ostream& operator << (ostream& out, AVLTree<T>& avltree) {
	writeKeysInOrder(avltree.root, out);
	return out;
}

template<class T>
istream& operator >>(istream& in, AVLTree<T>& avltree) {
	T key;
	while (in >> key) {
		avltree.root = avltree.insert(avltree.root, key);
	}
	return in;
}

int main() {
	AVLTree<int> avl;
	ifstream fin("test.txt");
	if (fin) {
		fin >> avl;
		fin.close();
	}
	else {
		cout << "Couldn't open the file. \n";
		return 1;
	}
	//try {
	//	avl.root = avl.rightRotate(avl.root);
	//}
	//catch (const Exception& e) {
	//	cout << "Exception was caught: " << endl;
	//	e.print();
	//}
	avl.preOrder(avl.root);
	//try {
	//	avl.load(fin);
	//}
	//catch (const Exception& e) {
	//	e.print();
	//}
	ofstream fout("result.txt");
	if (fout) {
		fout << avl;
		fout.close();
	}

	//avl.root = avl.insert(avl.root, 10);
	//avl.root = avl.insert(avl.root, 20);
	//avl.root = avl.insert(avl.root, 30);
	//avl.root = avl.insert(avl.root, 40);
	//avl.root = avl.insert(avl.root, 50);
	//avl.root = avl.leftRotate(avl.root);
	//AVLNode<int>* result = avl.search(20, avl.root);
	//if (result != nullptr) cout << "Found\n";
	//else cout << "Not Found\n";
	//
	//avl.root = avl.deletenode(avl.root, 30);
	//avl.preOrder(avl.root);

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