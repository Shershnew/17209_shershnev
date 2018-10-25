#pragma once

#include <string>
#include <map>
#include <iostream>

#include "Core_war.h"

typedef Node * (*creator_t)(size_t & i, std::vector<string> & words);
typedef std::string Id;

class Factory{
private:
	std::map<std::string, creator_t> creators;
public:
	Factory(){}
	Node * createCommandByName(const Id & id, size_t & i, std::vector<string> & words);
	bool registerCommand(const Id & id, const creator_t creator);
	static Factory & getFactory(){
		static Factory f;
		return f;
	}
};