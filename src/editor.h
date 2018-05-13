#ifndef EDITOR_H
#define EDITOR_H

#include<ncurses.h>

#include"buffer.h"

class EDITOR{
private:
		int x, y;
		char mode;
		BUFFER *buff;
		std::string status, filename, error_msg;

		// Cursor movement
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();

		void deleteLine();                  // Deletes current line
		void deleteLine(int);               // Deletes line <int>

		void saveFile();                    // Saves buffer into the file
public:
		EDITOR();							//Default constructor
		EDITOR(std::string);				//Parameterized constructor

		char getMode(){return mode;};

		void handleInput(int);				//Handles key presses.
		void printBuff();					
		void printStatusLine();				//Print status line at the bottom of the screen

		void updateStatus();

};

#endif
