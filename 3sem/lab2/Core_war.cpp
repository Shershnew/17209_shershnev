#include "Core_war.h"

using namespace coreWar;

Core_war::Core_war(){
	for (size_t i = 0; i < war_space_len; ++i){
		war_space[i] = new Node();
	}
}

Core_war::~Core_war(){
	for (size_t i = 0; i < war_space_len; ++i){
		delete war_space[i];
	}
}

void Core_war::set(Node * node, size_t i){
	delete war_space[i];
	war_space[i] = node;

}

bool isdigit_(string &str){
	int r = 0;
	if(str[0] == '-') r++;
	if(str[r] == '0' && str.size() > 1){
		return false;
	}
	for (int i = r; i < str.size(); ++i){
		if(!(str[i] >= '0' && str[i] <= '9')){
			return false;
		}
	}
	return true;
}

std::pair<size_t,int> Core_war::get_arg(size_t &i, std::vector<string> & words){
	i++;
	std::pair<size_t,int> arg = {0, 0};
	if(words[i] == "#"){
		i++;
		arg.first = 1;
	}else
	if(words[i] == "@"){
		i++;
		arg.first = 2;
	}

	if(isdigit_(words[i])){
		arg.second = std::stoi(words[i]);
	}else{
		std::cout << "error not a digit" << std::endl;
	}
	return arg;
}

bool Core_war::add_unit(string path){
	Unit un;
	std::ifstream file(path);
	if(!file){
		throw "файл не найден";
	}

	//разбиваем на слова
	std::vector<string> words;
	string tec;
	while(!file.eof()){
		file >> tec;
		words.push_back(tec);
	}
	file.close();
	
	std::cout << std::endl;
	for (int i = 0; i < words.size(); ++i){
		std::cout << " -- " << words[i];
	}
	std::cout << std::endl;
	std::cout << std::endl;

	//ищем место для unit
	bool found = false;

	while(!found){
		found = true;
		std::srand(unsigned(std::time(0)));
		un.unit_pointer = std::rand() % (war_space_len - max_size_unit);
		for (size_t i = 0; i < units.size(); ++i){
			size_t abs = un.unit_pointer - units[i].unit_pointer;
			if(abs < 0) abs *= -1;
			if(abs <= max_size_unit) found = false;	
		}
	}
	units.push_back(un);

	for (size_t i = 0; i < words.size(); ++i){
		if(words[i] == "DAT"){
			set(new DAT(get_arg(i, words)), un.unit_pointer++);
		}else
		if(words[i] == "MOV"){
			set(new MOV(get_arg(i, words), get_arg(i, words)), un.unit_pointer++);
		}else
		if(words[i] == "ADD"){
			set(new ADD(get_arg(i, words), get_arg(i, words)), un.unit_pointer++);
		}else
		if(words[i] == "SUB"){
			set(new SUB(get_arg(i, words), get_arg(i, words)), un.unit_pointer++);
		}else
		if(words[i] == "JMP"){
			set(new JMP(get_arg(i, words)), un.unit_pointer++);
		}else
		if(words[i] == "JMZ"){
			set(new JMZ(get_arg(i, words), get_arg(i, words)), un.unit_pointer++);
		}else
		if(words[i] == "DJZ"){
			set(new DJZ(get_arg(i, words), get_arg(i, words)), un.unit_pointer++);
		}else
		if(words[i] == "CMP"){
			set(new CMP(get_arg(i, words), get_arg(i, words)), un.unit_pointer++);
		}else{
			std::cout << "ошибка компиляции";
		};
	}
}

Node * createNodeByName(const std::string& name) {
	
}

int Node::get_number_from_args(std::array<Node *, war_space_len> &arr, Unit & un, size_t i){
	if(args[i].first == 1){
		return args[i].second % war_space_len;
	}else
	if(args[i].first == 0){
		if(!arr[(un.unit_pointer + args[i].second) % war_space_len]->isCommand){
			return arr[(un.unit_pointer + args[i].second) % war_space_len]->number;
		}else{
			std::cout << "обращение за числом к команде" << std::endl;
		}
	}
}

int Node::get_addres_from_args(std::array<Node *, war_space_len> &arr, Unit & un, size_t i){
	if(args[i].first == 1){
		return args[i].second % war_space_len;
	}else
	if(args[i].first == 0){
		return (un.unit_pointer + args[i].second) % war_space_len;
	}else
	if(args[i].first == 2){
		if(!arr[(un.unit_pointer + args[i].second) % war_space_len]->isCommand){
			return arr[(un.unit_pointer + args[i].second) % war_space_len]->number;
		}else{
			std::cout << "обращение за числом к команде" << std::endl;
		}
	}
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