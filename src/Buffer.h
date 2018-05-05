#ifndef BUFFER_H
#define BUFFER_H

#include<string>
#include<vector>

#include"Undo.h"

class Buffer{
        public:
		Buffer();
    
        std::vector<std::string> lines;
        std::vector<std::string> undo;

		void insertLine(std::string, int);
	    void appendLine(std::string);
		void removeLine(int);
        void undo();
        void redo();

		std::string repTabs(std::string);
};

#endif
