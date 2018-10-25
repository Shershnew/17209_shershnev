#include "Factory_commands.h"

Node * Factory::createCommandByName(const Id & id, size_t & i, std::vector<string> & words){
	auto it = creators.find(id);
	if(creators.end() == it){
		return nullptr;
	}
	Node * un = it->second(i, words);
	return un;
}

bool Factory::registerCommand(const Id & id, const creator_t creator){
	creators[id] = creator;
}