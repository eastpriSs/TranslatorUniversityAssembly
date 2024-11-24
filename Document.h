#pragma once
#include <fstream>
#include <vector>

class Document
{
private:
    std::vector<char> chstr;
    std::string filename;

public:
    inline std::vector<char>::const_iterator getBeginIterator() const { return chstr.begin(); }
    inline std::vector<char>::const_iterator getEndIterator() const { return chstr.end(); }
    inline std::string getFilename() const { return filename; }

    Document(const std::string&);
    ~Document() = default;
};

