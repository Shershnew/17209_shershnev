#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <string>

#include "Factory_commands.h"

typedef std::string string;

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
	void canExecute();
	virtual bool execute(std::array<Node *, war_space_len> &arr, Unit & un);
};

class Core_war{
private:
	void draw();
	void set(Node * node, size_t i);
public:
	std::vector<Unit> units;
	std::array<Node *, war_space_len> war_space;
	Core_war();
	~Core_war();
	bool add_unit(string path);
	int start(int n);
};