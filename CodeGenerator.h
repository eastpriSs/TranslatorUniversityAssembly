#pragma once
#include <string>
#include "Node.h"
#include "Parser.h"

class CodeGenerator final : public Visitor
{
private:
    Parser* pars = nullptr;
    uint8_t portCounter = 0;
    uint8_t loopCounter = 0;

    std::string visit(Operand&) override;
    std::string visit(Assgm&) override;
    std::string visit(To&) override;
    std::string visit(From&) override;
    std::string visit(Plus&) override;
    std::string visit(Mul&) override;
    std::string visit(Div&) override;
    std::string visit(Minus&) override;
    std::string visit(VarDeclaration&) override;
    std::string visit(Input&) override;
    std::string visit(Out&) override;
    std::string visit(Push&) override;
    std::string visit(Pop&) override;
    std::string visit(Swap&) override;
    std::string visit(Label&) override;
    std::string visit(Less&) override;
    std::string visit(Bigger&) override;
    std::string visit(Equal&) override;
    std::string visit(NotEqual&) override;
    std::string visit(EqualLess&)  override;
    std::string visit(EqualBigger&) override;
    std::string visit(IfStatement&) override;
    std::string visit(Stop&) override;
    std::string visit(StopGenerating&) override;
    std::string visit(WhileStatement&) override;
    std::string visit(JustWrite&) override;
    std::string visit(JmpConstruction&) override;
    std::string visit(Call&) override;

public:
    bool isGenerating = true;
    CodeGenerator(Parser* p) : pars(p) {}
    std::string generate();
};

