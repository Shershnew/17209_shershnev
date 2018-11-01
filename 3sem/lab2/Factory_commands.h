#pragma once

#include <string>
#include <map>
#include <iostream>

#include "Core_war.h"

template<class Id, class Node, class creator_t>
class Factory{
private:
	std::map<Id, creator_t> creators;
	Factory() = default;
	Factory(const Factory & f){}
	Factory & operator=(const Factory & f) {}
public:
	Node * createCommandByName(const Id & id, size_t & i, std::vector<std::string> & words){
		auto it = creators.find(id);
		if(creators.end() == it){
			return nullptr;
		}
		Node * un = it->second(i, words);
		return un;
	}

	bool registerCommand(const Id & id, const creator_t creator){
		creators[id] = creator;
	}

	static Factory & getFactory(){
		static Factory f;
		return f;
	}
};