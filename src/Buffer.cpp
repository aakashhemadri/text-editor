#include"Buffer.h"

Buffer::Buffer(){
		
}
std::string Buffer::repTabs(std::string line)
{
    int tab = line.find("\t");
    if(tab == line.npos)
        return line;
    else
        return repTabs(line.replace(tab, 1, "    "));
}

void Buffer::insertLine(std::string line, int n)
{
    line = repTabs(line);                   // Conversion (happens every time)
    lines.insert(lines.begin()+n, line);
}

void Buffer::appendLine(std::string line)
{
    line = repTabs(line);
    lines.push_back(line);
}

void Buffer::removeLine(int n)
{
    lines.erase(lines.begin()+n);
}

