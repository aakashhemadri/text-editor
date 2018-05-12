#include"Buffer.h"
Buffer::Buffer(){
    undo = new NODE;
    undo->pos = -1;
    undo->next = NULL;
    undo->line = "";
    undo->command = "ROOT";

    redo = new NODE;
    redo->pos = -1;
    redo->next = NULL;
    redo->line = "";
    redo->command = "ROOT";
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
    
    struct NODE* temp;
    temp = new NODE;
    temp->line = line;
    temp->command = "INSERT";
    temp->pos = n;
    temp->next = undo;
    undo = temp;

}

void Buffer::appendLine(std::string line)
{
    line = repTabs(line);
    lines.push_back(line);
    
   if(line != ""){
    struct NODE* temp;
    temp = new NODE;
    temp->line = line;
    temp->command = "INSERT";
    temp->pos = lines.size();
    temp->next = undo;
    undo = temp;
   }
}

void Buffer::removeLine(int n)
{
    struct NODE* temp;
    temp = new NODE;
    temp->line = lines.at(n);
    temp->command = "DELETE";
    temp->pos = n;
    temp->next = undo;
    undo = temp;

    lines.erase(lines.begin()+n);
}

