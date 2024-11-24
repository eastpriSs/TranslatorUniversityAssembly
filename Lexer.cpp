#include "Lexer.h"
#include <iostream>

Lexer::Lexer(const Document* cs)
{
    chst = cs;
    begin = chst->getBeginIterator();
    end = chst->getEndIterator();
    it = begin;
    forwardIt = it + 1;
}

void Lexer::skipWhiteSpaces()
{
    while (std::isspace(*it) || *it == '\t') ++it;
    forwardIt = it + 1;
}

inline bool ishex(char c) {
    return ('0' <= c && c <= '9') || ('A' <= c && c <= 'F') || ('a' <= c && c <= 'f');
}

Token Lexer::scanOperand() 
{
    using namespace std;
    using Keyword::table;

    while (forwardIt != end)
        if (ishex(*forwardIt) || isalpha(*forwardIt))
            ++forwardIt;
        else break;

    if (forwardIt != end) {
        if (*forwardIt == '(') {
            ++forwardIt;
            while (forwardIt != end)
            {
                if (isalpha(*forwardIt) || isdigit(*forwardIt))
                    ++forwardIt;
                else break;
            }
            if (*forwardIt++ == ')')
                return Token(ttype::shift);
            else 
                return Token(ttype::unknown);
        
        }
        else if (*forwardIt == ':') 
        {
            ++forwardIt;
            return Token(ttype::label);
        }
    }
    string lexem = string(it, forwardIt);
    if (table.find(lexem) != table.end())
        return Token(table[lexem]);
    else
        return Token(ttype::operand);

    return Token(ttype::unknown);
}

Token Lexer::scanOperator() 
{
    switch (*it)
    {
    case '=':
    {
        switch (*forwardIt)
        {
        case '=':
            ++forwardIt;
            return Token(ttype::operEq);
        }
        return Token(ttype::assgm);
        break;
    }
    case '!':
    {
        switch (*forwardIt)
        {
        case '=':
            ++forwardIt;
            return Token(ttype::operNotEqual);
        }
        return Token(ttype::unknown);
        break;
    }
    case '-':
    {
        switch (*forwardIt)
        {
        case '>':
            ++forwardIt;
            return Token(ttype::to);
        case '=':
            ++forwardIt;
            return Token(ttype::sub);
        }
        break;
    }
    case '<':
    {
        switch (*forwardIt)
        {
        case '-':
            ++forwardIt;
            return Token(ttype::from);
        case '=':
            ++forwardIt;
            return Token(ttype::operEqLess);
        }
        return Token(ttype::operLess);
        break;
    }
    case '>':
    {
        switch (*forwardIt)
        {
        case '=':
            ++forwardIt;
            return Token(ttype::operEqBig);
        }
        return Token(ttype::operBigger);
        break;
    }
    case '+':
    {
        switch (*forwardIt)
        {
        case '=':
            ++forwardIt;
            return Token(ttype::plus);
        }
        break;
    }
    case '*':
    {
        switch (*forwardIt)
        {
        case '=':
            ++forwardIt;
            return Token(ttype::mul);
        }
        break;
    }
    case '/':
    {
        switch (*forwardIt)
        {
        case '=':
            ++forwardIt;
            return Token(ttype::div);
        }
        break;
    }
    }
    return Token(ttype::unknown);
}

Token Lexer::scan()
{
    Token scanningToken;

    if (it == end)
        return scanningToken;
    
    forwardIt = it + 1;
    
    skipWhiteSpaces();
    scanningToken = scanOperator();
    
    if (scanningToken.type == ttype::unknown)
        scanningToken = scanOperand();

    lastLexem = std::string(it, forwardIt);
    it = forwardIt;
    if (forwardIt != end)
        forwardIt = it + 1;
    
    return scanningToken;
}