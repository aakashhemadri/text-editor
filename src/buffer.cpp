#include"buffer.h"
BUFFER::BUFFER(){
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
std::string BUFFER::repTabs(std::string line)
{
    int tab = line.find("\t");
    if(tab == line.npos)
        return line;
    else
        return repTabs(line.replace(tab, 1, "    "));
}

void BUFFER::insertLine(std::string line, int n)
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

void BUFFER::appendLine(std::string line)
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

void BUFFER::removeLine(int n)
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
void BUFFER::undoBuffer(){
    struct NODE* temp=undo;
    if(undo->command == "INSERT"){
        lines.erase(lines.begin()+undo->pos);
    }
    else if(undo->command == "DELETE"){
        undo->line = repTabs(undo->line);                   // Conversion (happens every time)
        lines.insert(lines.begin()+undo->pos, undo->line);
    }
    else if(undo->command == "ROOT"){
    
    }
    undo = undo->next;
    temp->next = redo;
    redo = temp;
    delete temp;
}
void BUFFER::redoBuffer(){
    struct NODE* temp=redo;
    if(redo->command == "INSERT"){ 
        redo->line = repTabs(redo->line);                   // Conversion (happens every time)
        lines.insert(lines.begin()+redo->pos, redo->line);
    }
    else if(redo->command == "DELETE"){ 
        lines.erase(lines.begin()+undo->pos);
    }
    else if(redo->command == "ROOT"){

    }
    redo = redo->next;
    temp->next = undo;
    undo = temp;
    delete temp;
}
