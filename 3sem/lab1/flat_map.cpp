#include "flat_map.h"
#include <iostream>
using namespace Fmap;

Flat_map::Flat_map(){
	len = 1;
	len_now = 0;
	mas = new Value[len];
	keys = new Key[len];
}

Flat_map::Flat_map(const Flat_map& b){
	len = b.len;
	len_now = b.len_now;
	mas = new Value[len];
	keys = new Key[len];
	for (int i = 0; i < len_now; ++i){
		set(i,b.keys[i],b.mas[i]);
	}	
}

Flat_map::~Flat_map(){
	delete[] mas;
	delete[] keys;
}

size_t Flat_map::size() const{
	return (size_t)len_now;
}

bool Flat_map::empty() const{
	if(len_now == 0)
		return true;
	return false;
}

void Flat_map::print(){
	for (int i = 0; i < len_now; ++i)
	{
		std::cout << i << " - " << keys[i] << " - " << mas[i].age << std::endl;
	}
}

Value& Flat_map::operator[](const Key& k){
	try{
		return at(k);
	}catch(const char * str){
		return define_value;
	}
}

Flat_map& Flat_map::operator=(const Flat_map& b){
	this->~Flat_map();
	len = b.len;
	len_now = b.len_now;
	mas = new Value[len];
	keys = new Key[len];
	for (int i = 0; i < len_now; ++i){
		set(i,b.keys[i],b.mas[i]);
	}
	return *this;
}

bool Flat_map::contains(const Key& k) const{
	if(len_now == 0){
		return false;
	}
	long long l = 0,r = len_now - 1;
	while(l != r){
		long long tec = l + ((r - l) / 2);
		if(k == keys[tec]){
			return true;
		}
		else if(k > keys[tec]){
			l = tec + 1;
		}
		else{
			r = tec;
		}
	}
	if(k == keys[l]){
		return true;
	}
	return false;
}

bool Flat_map::erase(const Key& k){
	if(len_now == 0){
		return false;
	}
	long long l = 0,r = len_now - 1;
	while(l != r){
		long long tec = l + ((r - l) / 2);
		if(k == keys[tec]){
			len_now--;
			for (int i = tec; i < len_now - 1; ++i){
				mas[i] = mas[i+1];
				keys[i] = keys[i+1];
			}
			return true;
		}
		else if(k > keys[tec]){
			l = tec + 1;
		}
		else{
			r = tec;
		}
	}
	if(k == keys[l]){
		len_now--;
		for (int i = l; i < len_now - 1; ++i){
			mas[i] = mas[i+1];
			keys[i] = keys[i+1];
		}
		return true;
	}
	return false;
}

void Flat_map::clear(){
	this->~Flat_map();
	Flat_map();
}

Value& Flat_map::at(const Key& k){
	if(len_now == 0){
		throw "контейнер пуст";
	}
	long long l = 0,r = len_now - 1;
	while(l != r){
		long long tec = l + ((r - l) / 2);
		if(k == keys[tec]){
			return mas[tec];
		}
		else if(k > keys[tec]){
			l = tec + 1;
		}
		else{
			r = tec;
		}
	}
	if(k == keys[l]){
		return mas[l];
	}
	throw "элемента не существует";
}

const Value& Flat_map::at(const Key& k) const{
	return (const Value&)at(k);
}

inline void Flat_map::set(long long i, const Key& k, const Value& v){
	mas[i] = v;
	keys[i] = k;
}

bool Flat_map::insert(const Key& k, const Value& v){
	if(len_now == len){
		long long new_len = len * 2;
		Value * mas2 = new Value[new_len];
		Key * keys2 = new Key[new_len];
		if(mas2 == 0){
			return false;
		}
		if(keys2 == 0){
			delete[] mas2;
			return false;
		}
		for (int i = 0; i < len_now; ++i){
			mas2[i] = mas[i];
			keys2[i] = keys[i];
		}
		delete[] mas;
		delete[] keys;
		mas = mas2;
		keys = keys2;
		len = new_len;
	}
	if(len_now == 0){
		set(0,k,v);
		len_now++;
		return true;
	}
	if(k > keys[len_now-1]){
		set(len_now,k,v);
		len_now++;
		return true;
	}
	long long l = 0,r = len_now - 1;
	while(l != r){
		long long tec = l + ((r - l) / 2);
		if(k == keys[tec]){
			set(tec,k,v);
			return true;
		}
		else if(k > keys[tec]){
			l = tec + 1;
		}
		else{
			r = tec;
		}
	}
	if(k == keys[l]){
		set(l,k,v);
		return true;
	}
	for(int i = len_now; i > l; i--){
		mas[i] = mas[i-1];
		keys[i] = keys[i-1];
	}
	set(l,k,v);
	len_now++;
	return true;
}