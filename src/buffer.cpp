#include"buffer.h"
BUFFER::BUFFER(){
    undo = new NODE();
    redo = new NODE();
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
}

std::string BUFFER::_insertLine(std::string line, int n){
    NODE *temp = new NODE();
    temp->line = line;
    temp->command = "INSERT";
    temp->pos = n;
    temp->next = undo;
    undo = temp;
    return undo->line;
}
std::string BUFFER::appendLine(std::string line)
{
    line = repTabs(line);
    lines.push_back(line);
    
    NODE* temp;
   if(line != ""){
    temp = new NODE();
    temp->line = line;
    temp->command = "INSERT";
    temp->pos = lines.size();
    temp->next = undo;
    undo = temp;
   }
   return undo->line;
}

std::string BUFFER::removeLine(int n)
{
    NODE* temp;
    temp = new NODE();
    temp->line = lines.at(n);
    temp->command = "DELETE";
    temp->pos = n;
    temp->next = undo;
    undo = temp;

    lines.erase(lines.begin()+n);

    return undo->line;
}
std::string BUFFER::undoBuffer(){
    if(undo->command == "INSERT"){
        lines.erase(lines.begin()+undo->pos);
        
        NODE* temp=undo;
        undo = undo->next;
        temp->next = redo;
        redo = temp;

//        return "";
        return "Deleted one line";
    }
    else if(undo->command == "DELETE"){
        undo->line = repTabs(undo->line);                   // Conversion (happens every time)
        lines.insert(lines.begin()+undo->pos, undo->line);
        
        NODE* temp=undo;
        undo = undo->next;
        temp->next = redo;
        redo = temp;

//        return "";
        return "Inserted one line";
    }
    else if(undo->command == "ROOT"){
        return "Already at oldest change";    
    }
}
std::string BUFFER::redoBuffer(){
    NODE* temp=redo;
    if(redo->command == "INSERT"){ 
        redo->line = repTabs(redo->line);                   // Conversion (happens every time)
        lines.insert(lines.begin()+redo->pos, redo->line);
    
        redo = redo->next;
        temp->next = undo;
        undo = temp;
        
        return "Deleted one line";
    }
    else if(redo->command == "DELETE"){ 
        lines.erase(lines.begin()+undo->pos);
        
        redo = redo->next;
        temp->next = undo;
        undo = temp;

        return "Inserted one line";
    }
    else if(redo->command == "ROOT"){
        return "Already at oldest change";
    }
}
