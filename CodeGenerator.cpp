#include "CodeGenerator.h"
#include "SymbolTable.h"
#include <sstream>
#include <regex>

using std::string;
using std::stringstream;

// something went wrong 
inline bool isShiftLexem(const std::string& lex) 
{
    return std::regex_match(lex, std::regex("\\d+\\s*\\([a-zA-Z0-9]+\\)"));
}

inline bool isOperandGlobal(const std::string& operId)
{
    return SymbolTable::instance().isVar(operId) || isShiftLexem(operId);
}

inline bool isOperandRegister(const std::string& operId)
{
    return SymbolTable::instance().isRegister(operId);
}

std::string CodeGenerator::visit(Operand& rv)
{
    return rv.v;
}

std::string CodeGenerator::visit(Label& rv)
{
    return rv.v;
}

std::string CodeGenerator::visit(JustWrite& just)
{
    return just.v + '\n';
}

std::string CodeGenerator::visit(Assgm& ass)
{
    string left = ass.left->accept(*this);
    string right = ass.right->accept(*this);
    stringstream ss;

    if (isOperandGlobal(right))
        ss << "load " << left << ',' << right;
    else if (SymbolTable::instance().isRegister(right))
        ss << "mov " << left << ',' << right;
    else
        ss << "mvi " << left << ',' << right;
    
    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(To& to) 
{
    stringstream ss;
    ss << "stor " << to.left->accept(*this) << ',' << to.right->accept(*this);
    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(Plus& pl) 
{
    string left = pl.left->accept(*this);
    string right = pl.right->accept(*this);
    stringstream ss;

    if (isOperandGlobal(right))
        ss << "adm " << left << ',' << right;
    else if (SymbolTable::instance().isRegister(right))
        ss << "adr " << left << ',' << right;
    else
        ss << "adi " << left << ',' << right;

    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(Minus& m)
{
    string left = m.left->accept(*this);
    string right = m.right->accept(*this);
    stringstream ss;

    if (isOperandGlobal(right))
        ss << "sbm " << left << ',' << right;
    else if (SymbolTable::instance().isRegister(right))
        ss << "sbr " << left << ',' << right;
    else
        ss << "sbi " << left << ',' << right;

    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(Mul& m) 
{
    string left = m.left->accept(*this);
    string right = m.right->accept(*this);
    stringstream ss;

    if (isOperandGlobal(right))
        ss << "mum " << left << ',' << right;
    else if (SymbolTable::instance().isRegister(right))
        if (left == right)
            // a *= a
            if (left == "a")
                ss << "Semantic Error: in model 2 u cant multiple register a with register a";
            // b *= b 
            else
                ss << "mur a,b";
        // a *= b
        // b *= a
        else
            ss << "mur a,a";
    else
        ss << "mui " << left << ',' << right;

    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(Div& d) 
{
    string left = d.left->accept(*this);
    string right = d.right->accept(*this);
    stringstream ss;
    
    ss << "mui a,01\n";
    
    if (isOperandGlobal(right))
        ss << "dvm a," << right;
    else if (SymbolTable::instance().isRegister(right))
        ss << "Semantic Error: right operand cant be register";
    else
        ss << "dvi a," << right;
    
    if (left == "a")
        ss << "\nxchg";

    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(From& f) 
{
    stringstream ss;
    ss << "load " << f.left->accept(*this) << ',' << f.right->accept(*this);
    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(VarDeclaration& vd)
{
    stringstream ss;
    ss << vd.left->accept(*this) << ':' << ".ds " << vd.right->accept(*this);
    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(Push& p)
{
    stringstream ss;
    ss << "push " << p.oper->accept(*this);
    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(Pop& p)
{
    stringstream ss;
    ss << "pop " << p.oper->accept(*this);
    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(Swap& p)
{
    stringstream ss;
    ss << "xchg";
    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(Input& inp) 
{
    stringstream ss;
    string oper = inp.oper->accept(*this);

    if (isOperandGlobal(oper))
        ss << "in " << std::to_string(portCounter++) << '\n' << "stor a," << oper;
    else if (SymbolTable::instance().isRegister(oper))
        // input a
        if (oper == "a")
            ss << "in " << std::to_string(portCounter++);
        // input b
        else
            ss << "in " << std::to_string(portCounter++) << '\n' << "xchg";
    else 
        ss << "in " << oper;

    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(Out& inp)
{
    stringstream ss;
    string oper = inp.oper->accept(*this);

    if (isOperandGlobal(oper))
        ss << "load a," << oper << '\n' << "out " << std::to_string(portCounter++);
    else if (SymbolTable::instance().isRegister(oper))
        // out a
        if (oper == "a")
            ss << "out " << std::to_string(portCounter++);
        // out b
        else
            ss << "xchg" << '\n' << "out " << std::to_string(portCounter++);
    else
        ss << "out " << oper;

    ss << '\n';
    return ss.str();
}

void generateCmpCommand(const std::string& left, const std::string& right, stringstream& ss)
{
    char freeRegister = 'a';

    if (!isOperandGlobal(left) && !isOperandRegister(left)) {
        ss << "Semantic Error: left operand cant be hex literal";
        return;
    }

    if (isOperandGlobal(left)) {
        if (isOperandRegister(right))
            if (right == "a")
                freeRegister = 'b';
            else
                freeRegister = 'a';
        ss << "load " << freeRegister << ',' << left << '\n';
    }
    

    if (isOperandGlobal(right))
        ss << "Semantic Error: right operand cant be variable";
    else if (SymbolTable::instance().isRegister(right))
        ss << "cmr " << left << ',' << right;
    else
        if (isOperandGlobal(left))
            ss << "cmi " << freeRegister << ',' << right;
        else 
            ss << "cmi " << left << ',' << right;
}

std::string CodeGenerator::visit(Less& t)
{
    string left = t.left->accept(*this);
    string right = t.right->accept(*this);
    stringstream ss;
    generateCmpCommand(left, right, ss);
    ss << '\n' << "jn ";
    return ss.str();
}

std::string CodeGenerator::visit(Bigger& t)
{
    string left = t.left->accept(*this);
    string right = t.right->accept(*this);
    stringstream ss;
    generateCmpCommand(left, right, ss);
    ss << '\n' << "jp ";
    return ss.str();
}

std::string CodeGenerator::visit(Equal& t ) 
{
    string left = t.left->accept(*this);
    string right = t.right->accept(*this);
    stringstream ss;
    generateCmpCommand(left, right, ss);
    ss << '\n' << "jz ";
    return ss.str();
}

std::string CodeGenerator::visit(NotEqual& t)
{
    string left = t.left->accept(*this);
    string right = t.right->accept(*this);
    stringstream ss;
    generateCmpCommand(left, right, ss);
    ss << '\n' << "jnz ";
    return ss.str();
}

std::string CodeGenerator::visit(EqualLess& t)
{
    string left = t.left->accept(*this);
    string right = t.right->accept(*this);
    stringstream ss;
    generateCmpCommand(left, right, ss);
    ss << '\n' << "jnp ";
    return ss.str();
}

std::string CodeGenerator::visit(EqualBigger& t) 
{
    string left = t.left->accept(*this);
    string right = t.right->accept(*this);
    stringstream ss;
    generateCmpCommand(left, right, ss);
    ss << '\n' << "jnn ";
    return ss.str();
}
std::string CodeGenerator::visit(IfStatement& t)
{
    std::string generetedCondCode = t.cond->accept(*this);
    std::string generetedLabelCode = t.label->accept(*this);
    return generetedCondCode + generetedLabelCode + '\n';
}

std::string CodeGenerator::visit(WhileStatement& t)
{
    stringstream ss;
    std::string lc_str = std::to_string(loopCounter);
    ss << 'w' << lc_str << ':' << t.cond->accept(*this) << 'e' << lc_str;
    ss << '\n';
    return ss.str();
}

std::string CodeGenerator::visit(Stop& t)
{
    return "stop\n";
}

std::string CodeGenerator::visit(StopGenerating&)
{
    isGenerating = false;
    return "\nthanks for using Apraam's translator!\n";
}

std::string CodeGenerator::visit(JmpConstruction& t)
{
    return t.jmpTitle + ' ' + t.oper->accept(*this) + '\n';
}

std::string CodeGenerator::visit(Call& t)
{
    return "call " + t.oper->accept(*this) + '\n';
}

std::string CodeGenerator::generate()
{
    return pars->parse()->accept(*this);
}