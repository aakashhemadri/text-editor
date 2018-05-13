#ifndef BUFFER_H
#define BUFFER_H

#include<iostream>
#include<string>
#include<vector>

class LL{
    public:
    class NODE{
        public:
        NODE* next;
        std::string line;
        std::string command;
        int pos;
        NODE(){
        pos = -1;
        next = NULL;
        line = "NONE";
        command = "ROOT";
         }
    };
    NODE *undo;
    NODE *redo;

};
class BUFFER:public LL{
        public:
        std::vector<std::string> lines;
        
        BUFFER();
        
        void insertLine(std::string, int);
        std::string _insertLine(std::string, int);
        void appendLine(std::string);
        std::string removeLine(int);
        std::string undoBuffer();
        std::string redoBuffer();

		std::string repTabs(std::string);
};

#endif
