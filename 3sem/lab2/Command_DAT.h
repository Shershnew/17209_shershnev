#pragma once

#include "Core_war.h"
#include "Factory_commands.h"

class DAT: public Node{
public:
	DAT(std::pair<size_t,int> arg1);
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class MOV: public Node{
public:
	MOV(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
		isCommand = true;
		args.push_back(arg1);
		args.push_back(arg2);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class ADD: public Node{
public:
	ADD(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
		isCommand = true;
		args.push_back(arg1);
		args.push_back(arg2);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class SUB: public Node{
public:
	SUB(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
		isCommand = true;
		args.push_back(arg1);
		args.push_back(arg2);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class JMP: public Node{
public:
	JMP(std::pair<size_t,int> arg1){
		isCommand = true;
		args.push_back(arg1);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class JMZ: public Node{
public:
	JMZ(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
		isCommand = true;
		args.push_back(arg1);
		args.push_back(arg2);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class DJZ: public Node{
public:
	DJZ(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
		isCommand = true;
		args.push_back(arg1);
		args.push_back(arg2);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class CMP: public Node{
public:
	CMP(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
		isCommand = true;
		args.push_back(arg1);
		args.push_back(arg2);
		std::cout << arg1.first << " -- " << arg1.second << std::endl;
	}
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

bool is_dat_init = Factory::getFactory().registerCommand("DAT", DAT::create);
bool is_mov_init = Factory::getFactory().registerCommand("MOV", MOV::create);
bool is_add_init = Factory::getFactory().registerCommand("ADD", ADD::create);
bool is_sub_init = Factory::getFactory().registerCommand("SUB", SUB::create);
bool is_jmp_init = Factory::getFactory().registerCommand("JMP", JMP::create);
bool is_jmz_init = Factory::getFactory().registerCommand("JMZ", JMZ::create);
bool is_djz_init = Factory::getFactory().registerCommand("DJZ", DJZ::create);
bool is_cmp_init = Factory::getFactory().registerCommand("CMP", CMP::create);