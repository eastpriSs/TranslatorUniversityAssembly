#pragma once

enum class ttype {
    PUSH,POP,SWAP,IN,OUT,IF,
    numberLiteral,id,unknown,assgm,
    to,from,plus,mul,sub,div,VAR,shift,operand,
    label,operLess,operBigger,operEqLess,operEqBig,operEq,
    operNotEqual,stop,jmpConstruction,call,ret,
    eof
};

class Token
{
public:
    Token() : type(ttype::eof) {}
    Token(ttype t) : type(t) {}
    ttype type = ttype::eof;
};