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
	MOV(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2);
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class ADD: public Node{
public:
	ADD(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2);
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class SUB: public Node{
public:
	SUB(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2);
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class JMP: public Node{
public:
	JMP(std::pair<size_t,int> arg1);
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class JMZ: public Node{
public:
	JMZ(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2);
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class DJZ: public Node{
public:
	DJZ(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2);
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

class CMP: public Node{
public:
	CMP(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2);
	static Node * create(size_t & i, std::vector<string> & words);
	bool execute(std::array<Node *, war_space_len> &arr, Unit & un) override;
};

