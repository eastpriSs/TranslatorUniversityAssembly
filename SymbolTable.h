#pragma once
#include "Node.h"
#include <string>
#include <vector>

class SymbolTable
{
private:
	SymbolTable() {}
	std::vector<std::string> varTb;
	std::vector<std::string> registerTb = {"a","b"};

public:
	void write(std::string);
	bool isVar(const std::string&);
	bool isRegister(const std::string&);
	static SymbolTable& instance() 
	{
		static SymbolTable singlton = {};
		return singlton;
	}
};

