#include "Command_DAT.h"

DAT::DAT(std::pair<size_t,int> arg1){
	isCommand = true;
	args.push_back(arg1);
	std::cout << arg1.first << " -- " << arg1.second << std::endl;
}

bool DAT::execute(std::array<Node *, war_space_len> & arr, Unit & un){
	canExecute();
	isCommand = false;
	std::cout << "DAT executing number = " << get_number_from_args(arr, un, 0) << std::endl;
	std::cout << "pointer = " << un.unit_pointer << std::endl;
	std::cout << "arr = " << arr[un.unit_pointer]->args[0].second << std::endl;
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