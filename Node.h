#pragma once
#include <string>

class Operand;
class Assgm;
class To;
class From;
class Plus;
class Mul;
class Div;
class Minus;
class VarDeclaration;
class Input;
class Out;
class Push;
class Pop;
class Swap;
class Label;
class Less;
class Bigger;
class Equal;
class EqualLess;
class EqualBigger;
class IfStatement;
class NotEqual;
class Stop;
class StopGenerating;
class WhileStatement;
class JustWrite;
class JmpConstruction;
class Call;

class Visitor
{
public:
    virtual std::string visit(Operand&) = 0;
    virtual std::string visit(Assgm&) = 0;
    virtual std::string visit(To&) = 0;
    virtual std::string visit(From&) = 0;
    virtual std::string visit(Plus&) = 0;
    virtual std::string visit(Mul&) = 0;
    virtual std::string visit(Div&) = 0;
    virtual std::string visit(Minus&) = 0;
    virtual std::string visit(VarDeclaration&) = 0;
    virtual std::string visit(Input&) = 0;
    virtual std::string visit(Out&) = 0;
    virtual std::string visit(Push&) = 0;
    virtual std::string visit(Pop&) = 0;
    virtual std::string visit(Swap&) = 0;
    virtual std::string visit(Label&) = 0;
    virtual std::string visit(Less&) = 0;
    virtual std::string visit(Bigger&) = 0;
    virtual std::string visit(Equal&) = 0;
    virtual std::string visit(NotEqual&) = 0;
    virtual std::string visit(EqualLess&) = 0;
    virtual std::string visit(EqualBigger&) = 0;
    virtual std::string visit(IfStatement&) = 0;
    virtual std::string visit(Stop&) = 0;
    virtual std::string visit(StopGenerating&) = 0;
    virtual std::string visit(WhileStatement&) = 0;
    virtual std::string visit(JustWrite&) = 0;
    virtual std::string visit(JmpConstruction&) = 0;
    virtual std::string visit(Call&) = 0;
};

class Node
{
private:

public:
    virtual ~Node() = default;
    virtual std::string accept(Visitor& visitor) = 0;
};

class Operand final : public Node
{
public:
    std::string v;

    virtual std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Operand(std::string&& x) : v(x) {}
    ~Operand() = default;
};

class JustWrite final : public Node
{
public:
    std::string v;

    virtual std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    JustWrite(std::string&& x) : v(x) {}
    ~JustWrite() = default;
};

class JmpConstruction final : public Node
{
public:
    Node* oper;
    std::string jmpTitle;
    

    virtual std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    JmpConstruction(const std::string& x, Node* o) : jmpTitle(x), oper(o) {}
    ~JmpConstruction() = default;
};

class Stop final : public Node
{
public:
    virtual std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Stop() {}
    ~Stop() = default;
};

class StopGenerating final : public Node
{
public:
    virtual std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    StopGenerating() {}
    ~StopGenerating() = default;
};

class Label final : public Node
{
public:
    std::string v;

    virtual std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Label(std::string&& x) : v(x) {}
    ~Label() = default;
};

class Swap final : public Node
{
public:
    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Swap() {}
    ~Swap() = default;
};

class Input final : public Node
{
public:
    Node* oper;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Input(Node* x) : oper(x) {}
    ~Input() = default;
};

class Call final : public Node
{
public:
    Node* oper;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Call(Node* x) : oper(x) {}
    ~Call() = default;
};

class Push final : public Node
{
public:
    Node* oper;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Push(Node* x) : oper(x) {}
    ~Push() = default;
};

class Pop final : public Node
{
public:
    Node* oper;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Pop(Node* x) : oper(x) {}
    ~Pop() = default;
};


class Out final : public Node
{
public:
    Node* oper;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Out(Node* x) : oper(x) {}
    ~Out() = default;
};

class Assgm final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Assgm(Node* l, Node* r) : left(l), right(r) {}
    ~Assgm() = default;
};

class VarDeclaration final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    VarDeclaration(Node* l, Node* r) : left(l), right(r) {}
    ~VarDeclaration() = default;
};

class To final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    To(Node* l, Node* r) : left(l), right(r) {}
    ~To() = default;
};

class From final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    From(Node* l, Node* r) : left(l), right(r) {}
    ~From() = default;
};

class Mul final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Mul(Node* l, Node* r) : left(l), right(r) {}
    ~Mul() = default;
};

class Plus final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Plus(Node* l, Node* r) : left(l), right(r) {}
    ~Plus() = default;
};

class Minus final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Minus(Node* l, Node* r) : left(l), right(r) {}
    ~Minus() = default;
};

class Div final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Div(Node* l, Node* r) : left(l), right(r) {}
    ~Div() = default;
};

class Less final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Less(Node* l, Node* r) : left(l), right(r) {}
    ~Less() = default;
};

class Bigger final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Bigger(Node* l, Node* r) : left(l), right(r) {}
    ~Bigger() = default;
};

class Equal final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    Equal(Node* l, Node* r) : left(l), right(r) {}
    ~Equal() = default;
};

class NotEqual final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    NotEqual(Node* l, Node* r) : left(l), right(r) {}
    ~NotEqual() = default;
};

class EqualLess final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    EqualLess(Node* l, Node* r) : left(l), right(r) {}
    ~EqualLess() = default;
};

class EqualBigger final : public Node
{
public:
    Node* left;
    Node* right;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    EqualBigger(Node* l, Node* r) : left(l), right(r) {}
    ~EqualBigger() = default;
};



class IfStatement final : public Node
{
public:
    Node* cond;
    Node* label;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    IfStatement(Node* c, Node* l) : cond(c), label(l) {}
    ~IfStatement() = default;
};

class WhileStatement final : public Node
{
public:
    Node* cond;

    std::string accept(Visitor& visitor)
    {
        return visitor.visit(*this);
    }

    WhileStatement(Node* c) : cond(c) {}
    ~WhileStatement() = default;
};