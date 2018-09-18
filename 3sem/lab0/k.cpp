#include <iostream>
#include <stdlib.h>

class Mystring{
public:
	char * str;
private:
	int capacity;
	int len_now;

public:
	void clear(){
		len_now = 0;
		capacity = 10;
		char * strd = str;
		str = new char[capacity];
		delete strd;
	}

	void append(char c){
		if(len_now == capacity){
				str = 
				(char *)realloc(str, capacity * 2);
				capacity *= 2;
		}
		str[len_now++] = c;
	}

	void add(char * c){
		long long i = 0;
		while(c[i] != '\0'){
			append(c[i]);
			i++;
		};
	}

	void set(char * c){
		clear();
		add(c);
	}

	Mystring operator+=(Mystring& a){
		add(a.str);
		Mystring * r = new Mystring(str);
		return * r;
	}

	Mystring(int size = 10){
		capacity = size;
		str = new char[size];
		len_now = 0;
	}

	Mystring(char * c){
		capacity = 10;
		str = new char[10];
		len_now = 0;
		set(c);
	}

	~Mystring(){
		delete[] str;
	}
};

int main(){
	Mystring a("hellow ");
	Mystring b("World");
	Mystring c = a += b;
	std::cout << c.str;
	return 0;
}