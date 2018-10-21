#ifndef Core_warr
#define Core_warr

#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>

namespace coreWar{

const size_t space_width = 20;
const size_t space_height = 20;
const size_t war_space_len = space_height * space_width;
const size_t max_size_unit = 10;

typedef std::string string;

class Unit {
public:
	bool alive = true;
	size_t unit_pointer;
};

class Node{
protected:
	int get_addres_from_args(std::array<Node *, war_space_len> &arr, Unit & un, size_t i);
	int get_number_from_args(std::array<Node *, war_space_len> &arr, Unit & un, size_t i);
public:
	bool isCommand = false;
	int number = 0;
	std::vector<std::pair<size_t,int>> args;
	Node() : isCommand(false), number(0){}
	~Node(){}///????????????????????????????????????????????????????????????????????????????
	void canExecute(){
		if(!isCommand){
			throw "выполнение команды которой нет";
		}
	}
	virtual bool execute(std::array<Node *, war_space_len> &arr, Unit & un){
		canExecute();
	}
};

class Core_war{
private:
	void draw(){
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		system("clear");
		for (size_t i = 0; i < space_height; ++i){
			for (size_t j = 0; j < space_width; ++j){
				if(war_space[j + (i * space_height)]->isCommand){
					std::cout << "f ";
				} else
				if(war_space[j + (i * space_height)]->number > 0){
					std::cout << "# ";
				} else{
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
		}
	}
	void set(Node * node, size_t i);
	std::pair<size_t,int> get_arg(size_t &i, std::vector<string> & words);
public:
	std::vector<Unit> units;
	std::array<Node *, war_space_len> war_space;
	Core_war();
	~Core_war();
	bool add_unit(string path);
	int start(int n){
		for (int i = 0; i < n; ++i){
			try{
				draw();
				war_space[units[i % units.size()].unit_pointer]->execute(war_space, units[i % units.size()]);
				units[i % units.size()].unit_pointer = (units[i % units.size()].unit_pointer + 1) % war_space_len;
			}catch(const char * str){
				std::cout << str << std::endl;
				return i % units.size();
			}
		}
		return -1;
	}
};

//DAT B Инициализировать местоположение для значения B.
class DAT: public Node{
public:
	DAT(std::pair<size_t,int> arg1){
		isCommand = true;
		args.push_back(arg1);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

//MOV AB Переместить A в местоположение B. 
class MOV: public Node{
public:
	MOV(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
		isCommand = true;
		args.push_back(arg1);
		args.push_back(arg2);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

//ADD AB Добавить операнд A в содержание местоположение B и сохранить результат в местоположении B.
class ADD: public Node{
public:
	ADD(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
		isCommand = true;
		args.push_back(arg1);
		args.push_back(arg2);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

//SUB AB Вычесть операнд A из содержимого местоположения B и сохранить результат в местоположении B. 
class SUB: public Node{
public:
	SUB(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
		isCommand = true;
		args.push_back(arg1);
		args.push_back(arg2);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

//JMP B Перейти к местоположению B. 
class JMP: public Node{
public:
	JMP(std::pair<size_t,int> arg1){
		isCommand = true;
		args.push_back(arg1);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

/*
JMZ AB Если операнд A равен 0, перейдите в местоположение B;
в противном случае продолжить следующую команду.
*/
class JMZ: public Node{
public:
	JMZ(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
		isCommand = true;
		args.push_back(arg1);
		args.push_back(arg2);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

/*
DJZ AB Сокращение содержимого местоположения A на 1.
Если в местоположении A теперь выполняется 0, перейдите в положение B;
в противном случае продолжить следующую команду.
*/
class DJZ: public Node{
public:
	DJZ(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
		isCommand = true;
		args.push_back(arg1);
		args.push_back(arg2);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

/*
CMP AB Сравнить операнд A с операндом B.
Если они не равны, пропустите следующую инструкцию;
в противном случае продолжить
*/
class CMP: public Node{
public:
	CMP(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
		isCommand = true;
		args.push_back(arg1);
		args.push_back(arg2);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

}

#endif