#include<iostream>
#include<cstring>

using namespace std;

class BaseString {
protected:
	char* p;
	int len;
	int capacity;
public:
	BaseString(char* ptr) {
		len = strlen(ptr) + 1;
		capacity = 256;
		p = new char[len];
		for (int i = 0; i < len; i++) {
			p[i] = ptr[i];
		}
		p[len] = '\0';
	}
	BaseString(int Capacity = 256) {
		capacity = Capacity;
		p = new char[capacity];
		len = 0;
	}
	~BaseString() {
		if (p != 0) {
			delete[] p;
		}
		len = 0;
	}
	int Length() { return len; }
	int Capacity() { return capacity; }
	char& operator[](int i) { return p[i]; }
	BaseString& operator=(BaseString& s) {
		if (this != &s) {
			delete[] p;
			len = s.Length();
			capacity = s.capacity;
			p = new char[len];
			for (int i = 0; i < len; i++) {
				p[i] = s[i];
			}
			p[len - 1] = '\0';
		}
		return *this;
	}
	BaseString(BaseString& s) {
		len = s.Length();
		capacity = s.capacity;
		p = new char[len];
		for (int i = 0; i < len; i++) {
			p[i] = s[i];
		}
		p[len - 1] = '\0';
	}
	virtual void print() {
		int i = 0;
		while (p[i] != '\0') { cout << p[i]; i++; }
	}
};

class VowelWord : public BaseString {
private:
public:
	VowelWord(char* ptr) : BaseString(ptr) {}
	VowelWord(int Capacity = 256) : BaseString(Capacity) {}
	VowelWord(VowelWord& s) : BaseString(s) {}
	~VowelWord() {}
	VowelWord& operator=(VowelWord& s) {
		len = s.Length();
		p = new char[s.capacity];
		capacity = s.capacity;
		for (int i = 0; i < len; i++) {
			p[i] = s[i];
		}
		p[len - 1] = '\0';
		return *this;
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
		if (in_word && (vowel_start || isvowel(p[len - 2]))) {
			count++;
		}
		return count;
	}
	bool isvowel(char c) {
		c = tolower(c);
		return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
		//c == 'а' || c == 'э' || c == 'и' || c == 'о' || c == 'у'|| c == 'я' || c == 'е' || c == 'ё' || c == 'ю' || c == 'ы'
	}
	//bool isvowel(char  c) {
	//	const char vowels[] = "аэиоуяюеёый";
	//	for (int i = 0; i < sizeof(vowels) - 1; i++) {
	//		if (c == vowels[i] || c == toupper(vowels[i])) {
	//			return true;
	//		}
	//	}
	//	return false;
	//}
};

int main() {
	char str[] = "FINALLY IT IS WORKING RIGHT? RIGHT?";
	VowelWord s(str);
	s.print();
	int count = s.countwords();
	cout << '\n' << count << endl;
	return 0;
}