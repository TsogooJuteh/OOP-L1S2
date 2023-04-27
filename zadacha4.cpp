#include<iostream>
#include<cstring>

using namespace std;

class BaseString {
protected:
	char* p;
	int len;
	int capacity;
public:
	BaseString(const char* ptr) {
		if (ptr != NULL){
			len = strlen(ptr) + 1;
			capacity = 256;
			p = new char[len];
			if (p != NULL) {
				for (int i = 0; i < len; i++) {
					p[i] = ptr[i];
				}
				p[len - 1] = '\0';
			} else {
				len = 0;
				capacity = 0;
				p = NULL;
			}
		} else {
			len = 0;
			capacity = 0;
			p = NULL;
		}
	}
	BaseString(int Capacity = 256) {
		if (Capacity > 0) {
			capacity = Capacity;
			p = new char[capacity];
			if (p == NULL){
				capacity = 0;
				p = NULL;
			}
		} else {
			capacity = 0;
			p = NULL;
		}
		len = 0;
	}
	~BaseString() {
		if (p != NULL) {
			delete[] p;
		}
		len = 0;
	}
	int Length() const { return len; }
	int Capacity() const { return capacity; }
	char& operator[](int i) const { return p[i]; }
	BaseString& operator=(const BaseString& s) {
		if (this != &s) {
			if(p != NULL){
				delete[] p;
			}
			len = s.Length();
			capacity = s.capacity;
			p = new char[len];
			if (p != NULL) {
				for (int i = 0; i < len; i++) {
					p[i] = s[i];
				}
				p[len - 1] = '\0';
			} else {
				len = 0;
				capacity = 0;
				p = NULL;
			}
		}
		return *this;
	}
	BaseString(const BaseString& s) {
		len = s.Length();
		capacity = s.capacity;
		p = new char[len];
		if (p != NULL) {
			for (int i = 0; i < len; i++) {
				p[i] = s[i];
			}
			p[len - 1] = '\0';
		} else {
			len = 0;
			capacity = 0;
			p = NULL;
		}
	}
	virtual void print() const {
		if (p != NULL) {
			int i = 0;
			while (p[i] != '\0') { cout << p[i]; i++; }
		}
	}
};

class VowelWord : public BaseString {
private:
public:
	VowelWord(const char* ptr) : BaseString(ptr) {}
	VowelWord(int Capacity = 256) : BaseString(Capacity) {}
	VowelWord(const VowelWord& s) : BaseString(s) {}
	~VowelWord() {}
	VowelWord& operator=(const VowelWord& s) {
		if (this != &s){
			if(p != NULL){
				delete[] p;
			}
			len = s.Length();
			capacity = s.capacity;
			p = new char[capacity];
			if (p != NULL) {
				for (int i = 0; i < len; i++) {
					p[i] = s[i];
				}
				p[len - 1] = '\0';
			} else {
				len = 0;
				capacity = 0;
				p = NULL;
			}
		}
		return *this;
	}
	inline bool isvowel(char c) {
		c = tolower(c);
		return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
	}
	int countwords() {
		int count = 0;
		bool in_word = false;
		bool vowel_start = false;
		for (int i = 0; i < len; i++) {
			char c = p[i];
			if (isalpha(c)) {
				if (!in_word) {
					in_word = true;
					vowel_start = isvowel(c);
				}
			}
			else {
				if (in_word && (vowel_start || isvowel(p[i - 1]))) {
					count++;
				}
				in_word = false;
				vowel_start = false;
			}
		}
		if (in_word && (vowel_start || isvowel(p[len - 1]))) {
			count++;
		}
		return count;
	}
};

int main() {
	char str[] = "Hello , My name is World. What is your name, sir?:)about myself";
	VowelWord s(str);
	s.print();
	int count = s.countwords();
	cout << '\n' << count << endl;
	return 0;
}