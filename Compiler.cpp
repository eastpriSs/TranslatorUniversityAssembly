#include "Compiler.h"
#include "Lexer.h"
#include "Parser.h"
#include "CodeGenerator.h"
#include <iostream>

void Compiler::Compile(const Document& chs)
{
    Lexer scnr(&chs);
    Parser pars(scnr);
    CodeGenerator gen(&pars);
    while (gen.isGenerating)
        std::cout << gen.generate();

}
