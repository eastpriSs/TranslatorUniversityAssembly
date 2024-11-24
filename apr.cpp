#include "Document.h"
#include "Compiler.h"

int main(int argc, char* argv[])
{
	Document d = Document(argv[1]);
	Compiler c;
	c.Compile(d);
}