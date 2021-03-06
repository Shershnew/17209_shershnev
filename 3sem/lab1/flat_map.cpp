#include "flat_map.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
using namespace Fmap;

const size_t len_kef = 2; //коэффициент расширения контейнера

Flat_map::Flat_map(): len(1), len_now(0) {
	mas = new Value[len];
	keys = new Key[len];
}

Flat_map::Flat_map(const Flat_map& b):len(b.len), len_now(b.len_now){
	mas = new Value[len];
	keys = new Key[len];
	std::copy(b.mas, b.mas + len_now, mas);
	std::copy(b.keys, b.keys + len_now, keys);
}

Flat_map::Flat_map(Flat_map&& b):
	len(b.len),
	len_now(b.len_now),
	mas(b.mas),
	keys(b.keys){
	b.mas  = nullptr;
	b.keys = nullptr;
}

Flat_map::~Flat_map(){
	delete[] mas;
	delete[] keys;
}

size_t Flat_map::bin_search(const Key k) const{
	if(len_now == 0){
		return 0;
	}
	if(k == keys[0])
		return 0;
	if(k == keys[len_now - 1])
		return len_now - 1;
	size_t l = 0,r = len_now - 1;
	while(l < r){
		size_t tec = l + ((r - l) / 2);
		if(k == keys[tec]){
			return tec;
		}
		else if(k > keys[tec]){
			l = tec + 1;
		}
		else{
			r = tec;
		}
	}
	return l;
}

int Flat_map::bin_search_er(const Key k) const{
	size_t el = bin_search(k);
	if(keys[el] == k){
		return el;
	}
	return -1;
}

void Flat_map::swap(Flat_map& b){//конструктор перемещения и опер
	std::swap(*this, b);
}

size_t Flat_map::size() const{
	return len_now;
}

bool Flat_map::empty() const{
	return (len_now == 0);
}

void Flat_map::print(){
	for (size_t i = 0; i < len_now; ++i){
		std::cout << i << " - " << keys[i] << " - " << mas[i].age << std::endl;
	}
	std::cout << std::endl;
}

Value& Flat_map::operator[](const Key& k){
	int el = bin_search_er(k);
	if(-1 != el){
		return mas[el];
	}
	Value * v = new Value(0);
	insert(k, *v);
	return *v;
}

Flat_map& Flat_map::operator=(const Flat_map& b){
	if(this == &b){
		return *this;
	}
	len = b.len;
	len_now = b.len_now;
	delete[] mas;
	delete[] keys;
	mas = new Value[len];
	keys = new Key[len];
	std::copy(b.mas, b.mas + len_now, mas);
	std::copy(b.keys, b.keys + len_now, keys);
	return *this;
}

bool Flat_map::contains(const Key& k) const{
	if(-1 == bin_search_er(k)){
		return false;
	}
	return true;
}

bool Flat_map::erase(const Key& k){
	int el = bin_search_er(k);
	if(-1 == el)
		return false;
	len_now--;
	std::copy(mas+el+1, mas + len_now, mas+el);
	std::copy(keys+el+1, keys + len_now, keys+el);
	return true;
}

void Flat_map::clear(){
	len_now = 0;
}

Value& Flat_map::at(const Key& k){
	if(len_now == 0){
		throw std::runtime_error ("container is empty");
	}
	int el = bin_search_er(k);
	if(-1 == el){
		throw std::runtime_error ("element not found");
	}
	return mas[el];
}

const Value& Flat_map::at(const Key& k) const{
	return (const Value&)at(k);//???????????????
}

inline void Flat_map::set(long long i, const Key& k, const Value& v){
	mas[i] = v;
	keys[i] = k;
}

bool Flat_map::insert(const Key& k, const Value& v){
	if(len_now == len){
		size_t new_len = len * len_kef;
		Value * mas2 = new Value[new_len];
		Key * keys2 = new Key[new_len];
		std::copy(mas, mas + len_now, mas2);
		std::copy(keys, keys + len_now, keys2);
		delete[] mas;
		delete[] keys;
		mas = mas2;
		keys = keys2;
		len = new_len;
	}
	if(len_now == 0){
		set(0, k, v);
		len_now++;
		return true;
	}
	if(k > keys[len_now-1]){
		set(len_now, k, v);
		len_now++;
		return true;
	}
	if(k == keys[0]){
		set(0, k, v);
		return true;
	}
	if(k == keys[len_now - 1]){
		set(len_now - 1, k, v);
		return true;
	}
	size_t el = bin_search(k);
	for(size_t i = len_now; i > el; i--){
		mas[i] = mas[i-1];
		keys[i] = keys[i-1];
	}
	set(el, k, v);
	len_now++;
	return true;
}