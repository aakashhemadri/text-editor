#ifndef BUFFER_H
#define BUFFER_H

#include<string>
#include<vector>

class Buffer{
		public:
		Buffer();

		std::vector<std::string> lines;

		void insertLine(std::string, int);
	    void appendLine(std::string);
		void removeLine(int);

		std::string repTabs(std::string);
};

#endif
