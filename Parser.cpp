#include "Parser.h"
#include <iostream>
#include "SymbolTable.h"

Parser::Parser(Lexer& l) 
{
	lex = &l;
}


void Parser::checkToken(const ttype& expected, const ttype& found) 
{
	if (expected != found)
		std::cout << "Syntax error";
}


Node* Parser::expression() 
{
	Node* leftOperand = new Operand(lex->getLastLexem());
	
	currTkn = lex->scan();
	ttype opert = currTkn.type;

	currTkn = lex->scan();
	Node* rightOperand = new Operand(lex->getLastLexem());
	switch (opert)
	{
	case ttype::assgm:			return new Assgm(leftOperand, rightOperand);
	case ttype::plus:			return new Plus(leftOperand, rightOperand);
	case ttype::mul:			return new Mul(leftOperand, rightOperand);
	case ttype::sub:			return new Minus(leftOperand, rightOperand);
	case ttype::to:				return new To(leftOperand, rightOperand);
	case ttype::from:			return new From(leftOperand, rightOperand);
	case ttype::div:			return new Div(leftOperand, rightOperand);
	case ttype::operLess:		return new Less(leftOperand, rightOperand);
	case ttype::operBigger:		return new Bigger(leftOperand, rightOperand);
	case ttype::operEq:			return new Equal(leftOperand, rightOperand);
	case ttype::operEqLess:		return new EqualLess(leftOperand, rightOperand);
	case ttype::operEqBig:		return new EqualBigger(leftOperand, rightOperand);
	case ttype::operNotEqual:	return new NotEqual(leftOperand, rightOperand);
	}
	return nullptr;
}

Node* Parser::varDeclaration() 
{
	currTkn = lex->scan();
	Node* leftOperand = new Operand(lex->getLastLexem());
	SymbolTable::instance().write(lex->getLastLexem());

	currTkn = lex->scan();
	Node* rightOperand = new Operand(lex->getLastLexem());

	return new VarDeclaration(leftOperand, rightOperand);
}

Node* Parser::input()
{
	currTkn = lex->scan();
	Node* operand = new Operand(lex->getLastLexem());
	return new Input(operand);
}

Node* Parser::out() 
{
	currTkn = lex->scan();
	Node* operand = new Operand(lex->getLastLexem());
	return new Out(operand);
}

Node* Parser::push()
{
	currTkn = lex->scan();
	Node* operand = new Operand(lex->getLastLexem());
	return new Push(operand);
}

Node* Parser::pop()
{
	currTkn = lex->scan();
	Node* operand = new Operand(lex->getLastLexem());
	return new Pop(operand);
}

Node* Parser::ifstatement() 
{
	currTkn = lex->scan();
	Node* conditionTree = expression();
	currTkn = lex->scan(); // eat ':'
	currTkn = lex->scan();
	Node* label = new Operand(lex->getLastLexem());
	return new IfStatement(conditionTree, label);
}

Node* Parser::jmpConstr() 
{
	std::string&& jmpTitle = lex->getLastLexem();
	currTkn = lex->scan();
	Operand* op = new Operand(lex->getLastLexem());
	return new JmpConstruction(jmpTitle, op);
}

Node* Parser::callStatement() 
{
	currTkn = lex->scan();
	return new Call(new Operand(lex->getLastLexem()));
}

Node* Parser::parse() 
{
	while (currTkn = lex->scan(), currTkn.type != ttype::eof) 
	{
		switch (currTkn.type)
		{
		case ttype::operand:
			return expression();
		case ttype::label:
			return new Label(lex->getLastLexem());
		case ttype::IF:
			return ifstatement();
		case ttype::VAR:
			return varDeclaration();
		case ttype::IN:
			return input();
		case ttype::OUT:
			return out();
		case ttype::PUSH:
			return push();
		case ttype::POP:
			return pop();
		case ttype::jmpConstruction:
			return jmpConstr();
		case ttype::call:
			return callStatement();
		case ttype::ret:
			return new JustWrite(lex->getLastLexem());
		case ttype::SWAP:
			return new Swap();
		case ttype::stop:
			return new Stop();
		default:
			break;
		}
	}
	return new StopGenerating();
}