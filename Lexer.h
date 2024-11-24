#pragma once
#include "Document.h"
#include "Token.h"
#include <unordered_map>
#include <algorithm>
#include <string>

namespace Keyword
{
    static std::unordered_map<std::string, ttype> table =
    {
        {"push", ttype::PUSH},
        {"pop", ttype::POP},
        {"swap", ttype::SWAP},
        {"in", ttype::IN},
        {"out", ttype::OUT},
        {"if", ttype::IF},
        {"var", ttype::VAR},
        {"input", ttype::IN},
        {"push", ttype::PUSH},
        {"pop", ttype::POP},
        {"swap", ttype::SWAP},
        {"jmp", ttype::jmpConstruction},
        {"jn", ttype::jmpConstruction},
        {"jz", ttype::jmpConstruction},
        {"jp", ttype::jmpConstruction},
        {"jv", ttype::jmpConstruction},
        {"jnn", ttype::jmpConstruction},
        {"jnz", ttype::jmpConstruction},
        {"call", ttype::call},
        {"ret", ttype::ret},
        {"stop", ttype::stop},
        {"out", ttype::OUT}

    };
}

class Lexer
{
private:
    std::string lastLexem;
    std::vector<char>::const_iterator begin;
    std::vector<char>::const_iterator end;
    std::vector<char>::const_iterator it;
    std::vector<char>::const_iterator forwardIt;
    const Document* chst;
    static const int DEFAULT_KEYWORD_COUNT = 25;

private:
    void skipWhiteSpaces();
    [[nodiscard]]
    Token scanOperator();
    [[nodiscard]]
    Token scanOperand();

public:
    Lexer() = delete;
    Lexer(const Document*);
    Token scan();
    inline std::string getLastLexem() const { return lastLexem;  }
};

