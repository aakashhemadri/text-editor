#ifndef BUFFER_H
#define BUFFER_H

#include<string>
#include<vector>

class Buffer{
		public:
		Buffer();

		std::vector<std::string> lines;

		bool insertLine(std::string, int);
		bool appendLine(std::string, int);
		bool removeLine(std::string, int);

		std::string repTabs();
};

#endif
