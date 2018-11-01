#include "Command_DAT.h"

DAT::DAT(std::pair<size_t,int> arg1){
	isCommand = true;
	args.push_back(arg1);
}

MOV::MOV(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
	isCommand = true;
	args.push_back(arg1);
	args.push_back(arg2);
}

ADD::ADD(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
	isCommand = true;
	args.push_back(arg1);
	args.push_back(arg2);
}

SUB::SUB(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
	isCommand = true;
	args.push_back(arg1);
	args.push_back(arg2);
}

JMP::JMP(std::pair<size_t,int> arg1){
	isCommand = true;
	args.push_back(arg1);
}

JMZ::JMZ(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
	isCommand = true;
	args.push_back(arg1);
	args.push_back(arg2);
}

DJZ::DJZ(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
	isCommand = true;
	args.push_back(arg1);
	args.push_back(arg2);
}

CMP::CMP(std::pair<size_t,int> arg1, std::pair<size_t,int> arg2){
	isCommand = true;
	args.push_back(arg1);
	args.push_back(arg2);
}

bool DAT::execute(std::array<Node *, war_space_len> & arr, Unit & un){
	canExecute();
	isCommand = false;
	number = get_number_from_args(arr, un, 0);
}

bool MOV::execute(std::array<Node *, war_space_len> & arr, Unit & un){
	canExecute();
	arr[get_addres_from_args(arr, un, 1)]->isCommand = false;
	arr[get_addres_from_args(arr, un, 1)]->number = get_number_from_args(arr, un, 0);
}

bool ADD::execute(std::array<Node *, war_space_len> & arr, Unit & un){
	canExecute();
	arr[get_addres_from_args(arr, un, 1)]->number += get_number_from_args(arr, un, 0);
}

bool SUB::execute(std::array<Node *, war_space_len> & arr, Unit & un){
	canExecute();
	arr[get_addres_from_args(arr, un, 1)]->number -= get_number_from_args(arr, un, 0);
}

bool JMP::execute(std::array<Node *, war_space_len> & arr, Unit & un){
	canExecute();
	un.unit_pointer = (-1 + get_addres_from_args(arr, un, 0)) % war_space_len;
}

bool JMZ::execute(std::array<Node *, war_space_len> & arr, Unit & un){
	canExecute();
	if(get_number_from_args(arr, un, 0) == 0){
		un.unit_pointer = (-1 + get_addres_from_args(arr, un, 1)) % war_space_len;		
	}
}

bool DJZ::execute(std::array<Node *, war_space_len> & arr, Unit & un){
	canExecute();
	arr[get_addres_from_args(arr, un, 0)]->number -= 1;
	if(get_number_from_args(arr, un, 0) == 0){
		un.unit_pointer = (-1 + get_addres_from_args(arr, un, 1)) % war_space_len;		
	}
}

bool CMP::execute(std::array<Node *, war_space_len> & arr, Unit & un){
	canExecute();
	if(get_number_from_args(arr, un, 0) != get_number_from_args(arr, un, 1)){
		un.unit_pointer += 1;
	}
}

Node * DAT::create(size_t & i, std::vector<string> & words){
	return new DAT(get_arg(i, words));
}

Node * MOV::create(size_t & i, std::vector<string> & words){
	return new MOV(get_arg(i, words), get_arg(i, words));
}

Node * ADD::create(size_t & i, std::vector<string> & words){
	return new ADD(get_arg(i, words), get_arg(i, words));
}

Node * SUB::create(size_t & i, std::vector<string> & words){
	return new SUB(get_arg(i, words), get_arg(i, words));
}

Node * JMP::create(size_t & i, std::vector<string> & words){
	return new JMP(get_arg(i, words));
}

Node * JMZ::create(size_t & i, std::vector<string> & words){
	return new JMZ(get_arg(i, words), get_arg(i, words));
}

Node * DJZ::create(size_t & i, std::vector<string> & words){
	return new DJZ(get_arg(i, words), get_arg(i, words));
}

Node * CMP::create(size_t & i, std::vector<string> & words){
	return new CMP(get_arg(i, words), get_arg(i, words));
}

bool is_dat_init = Factory<std::string, Node, Node * (*)(size_t &, std::vector<std::string> &)>::getFactory().registerCommand("DAT", DAT::create);
bool is_mov_init = Factory<std::string, Node, Node * (*)(size_t &, std::vector<std::string> &)>::getFactory().registerCommand("MOV", MOV::create);
bool is_add_init = Factory<std::string, Node, Node * (*)(size_t &, std::vector<std::string> &)>::getFactory().registerCommand("ADD", ADD::create);
bool is_sub_init = Factory<std::string, Node, Node * (*)(size_t &, std::vector<std::string> &)>::getFactory().registerCommand("SUB", SUB::create);
bool is_jmp_init = Factory<std::string, Node, Node * (*)(size_t &, std::vector<std::string> &)>::getFactory().registerCommand("JMP", JMP::create);
bool is_jmz_init = Factory<std::string, Node, Node * (*)(size_t &, std::vector<std::string> &)>::getFactory().registerCommand("JMZ", JMZ::create);
bool is_djz_init = Factory<std::string, Node, Node * (*)(size_t &, std::vector<std::string> &)>::getFactory().registerCommand("DJZ", DJZ::create);
bool is_cmp_init = Factory<std::string, Node, Node * (*)(size_t &, std::vector<std::string> &)>::getFactory().registerCommand("CMP", CMP::create);