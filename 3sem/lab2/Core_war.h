#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>

class Node;
typedef std::string string;

#include "Factory_commands.h"

const size_t space_width = 20;
const size_t space_height = 20;
const size_t war_space_len = space_height * space_width;
const size_t max_size_unit = 15;

class Unit {
public:
	bool alive = true;
	size_t unit_pointer;
};

class Node{
protected:
	int get_addres_from_args(std::array<Node *, war_space_len> &arr, Unit & un, size_t i);
	int get_number_from_args(std::array<Node *, war_space_len> &arr, Unit & un, size_t i);
	static std::pair<size_t,int> get_arg(size_t &i, std::vector<string> & words);
public:
	bool isCommand = false;
	int number = 0;
	std::vector<std::pair<size_t,int>> args;
	Node() : isCommand(false), number(0){}
	virtual ~Node(){}
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
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		system("clear");
		for (size_t i = 0; i < space_height; ++i){
			for (size_t j = 0; j < space_width; ++j){
				if(war_space[j + (i * space_height)]->isCommand){
					std::cout << "f ";
				} else
				if(war_space[j + (i * space_height)]->number > 0){
					std::cout << war_space[j + (i * space_height)]->number;
				} else{
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
		}
	}
	void set(Node * node, size_t i);
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