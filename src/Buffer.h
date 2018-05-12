#ifndef BUFFER_H
#define BUFFER_H

#include<string>
#include<vector>

class Buffer{
		struct NODE{
            struct NODE* next;
            std::string line;
            std::string command;
            int pos;
        };
        public:
        NODE *undo;
        NODE *redo;
        std::vector<std::string> lines;
        
        Buffer();
		void insertLine(std::string, int);
	    void appendLine(std::string);
		void removeLine(int);
        void undoBuffer();
        void redoBuffer();

		std::string repTabs(std::string);
};

#endif
