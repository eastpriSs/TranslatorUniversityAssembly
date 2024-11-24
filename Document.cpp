#include "Document.h"

Document::Document(const std::string& path)
{
    using std::ifstream;

    ifstream f(path);
    chstr.reserve(2048);
    
    if (!f)
        throw std::invalid_argument("file did not open.");

    filename = path;
    char c;
    while (f.get(c))
        chstr.push_back(c);
}