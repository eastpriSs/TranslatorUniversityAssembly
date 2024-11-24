#include "SymbolTable.h"


bool SymbolTable::isVar(const std::string& target) 
{
	return std::find(varTb.begin(), varTb.end(), target) != varTb.end();
}

bool SymbolTable::isRegister(const std::string& target) 
{
	return std::find(registerTb.begin(), registerTb.end(), target) != registerTb.end();
}

void SymbolTable::write(std::string name) 
{
	varTb.push_back(name);
}
