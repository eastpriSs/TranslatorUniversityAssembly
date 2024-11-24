#pragma once
#include "Lexer.h"
#include "Token.h"
#include "Node.h"


class Parser
{
private:
	Lexer* lex;
	Token currTkn;
	void checkToken(const ttype&, const ttype&);

	Node* expression();
	Node* ifstatement();
	Node* callStatement();
	Node* jmpConstr();
	Node* input();
	Node* out();
	Node* push();
	Node* pop();
	Node* varDeclaration();

public:
	Parser(Lexer&);
	Node* parse();
};

