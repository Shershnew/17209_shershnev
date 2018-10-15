#include <string>

namespace Fmap {

typedef std::string Key;

class Value {
public:
	unsigned age;
	unsigned weight;

	Value(int agge = 0) {
		age = agge;
		weight = 11;
	}

	friend bool operator==(const Value & a, const Value & b){
		if(a.age == b.age && a.weight == b.weight){
			return true;
		}
		return false;
	}
};

class Flat_map {
private:
	Value * mas;
	Key * keys;
	size_t len;
	size_t len_now;

	size_t bin_search(const Key k) const;
	int bin_search_er(const Key k) const;
	inline void set(long long i, const Key& k, const Value& v);

public:
	Flat_map(Flat_map&& b);
	
  	Flat_map();

  	Flat_map(const Flat_map& b);

  	~Flat_map();

  	void print();

	// Обменивает значения двух хэш-таблиц.
	// Подумайте, зачем нужен этот метод, при наличии стандартной функции
	// std::swap.
	void swap(Flat_map& b);

	Flat_map& operator=(const Flat_map& b);

	// Очищает контейнер.
	void clear();
	// Удаляет элемент по заданному ключу.
	bool erase(const Key& k);
	// Вставка в контейнер. Возвращаемое значение - успешность вставки.
	bool insert(const Key& k, const Value& v);

	// Проверка наличия значения по заданному ключу.
	bool contains(const Key& k) const;

	// Возвращает значение по ключу. Небезопасный метод.
	// В случае отсутствия ключа в контейнере, следует вставить в контейнер
	// значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
	Value& operator[](const Key& k);

	// Возвращает значение по ключу. Бросает исключение при неудаче.
	Value& at(const Key& k);
	const Value& at(const Key& k) const; //вызывается на константный обектах

	size_t size() const;
	bool empty() const;

	friend bool operator==(const Flat_map & a, const Flat_map & b){
		if(a.len_now == b.len_now){
			for (size_t i = 0; i < a.len_now; ++i){
				if(!((a.mas[i] == b.mas[i]) && (a.keys[i] == b.keys[i]))){
					return false;
				}
			}
		} else{
			return false;
		}
			return true;
	}

	friend bool operator!=(const Flat_map & a, const Flat_map & b){
		return !(a == b);
	}
};
}