#include "Core_war.h"

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

void Node::canExecute(){
	if(!isCommand){
		throw "выполнение команды которой нет";
	}
}

bool Node::execute(std::array<Node *, war_space_len> &arr, Unit & un){
	canExecute();
}

std::pair<size_t,int> Node::get_arg(size_t &i, std::vector<string> & words){
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

int Node::get_number_from_args(std::array<Node *, war_space_len> &arr, Unit & un, size_t i){
	if(args[i].first == 1){
		return args[i].second % war_space_len;
	}else
	if(args[i].first == 0){
		if(!arr[(un.unit_pointer + args[i].second) % war_space_len]->isCommand){
			return arr[(un.unit_pointer + args[i].second) % war_space_len]->number;
		}else{
			std::cout << "обращение за числом к команде 1" << std::endl;
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
			std::cout << "обращение за числом к команде 2" << std::endl;
		}
	}
}

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

bool Core_war::add_unit(string path){
	Unit un;
	std::ifstream file(path);
	if(!file){
		throw "файл не найден";
	}

	std::vector<string> words;
	string tec;
	while(!file.eof()){
		file >> tec;
		words.push_back(tec);
	}
	file.close();

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
		set(Factory<std::string, Node, Node * (*)(size_t &, std::vector<std::string> &)>::getFactory().createCommandByName(words[i], i, words), un.unit_pointer++);
	}
}

void Core_war::draw(){
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	system("clear");
	for (size_t i = 0; i < space_height; ++i){
		for (size_t j = 0; j < space_width; ++j){
			if(war_space[j + (i * space_height)]->isCommand){
				std::cout << "f ";
			} else
			if(war_space[j + (i * space_height)]->number > 0){
				std::cout << war_space[j + (i * space_height)]->number % 10 << " ";
			} else{
				std::cout << "  ";
			}
		}
		std::cout << std::endl;
	}
}

int Core_war::start(int n){
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