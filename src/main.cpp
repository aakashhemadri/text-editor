#include<ncurses.h>
#include<string>

#include"Editor.h"

void ncursesInit(){
		initscr();				//start ncurses mode
		noecho();				//Disabling keystroke echo
		cbreak();				//Disableing line buffering
		keypad(stdscr,true);	//Enable special keys to be recorded
}

int main(int argc, char* argv[]){
		Editor ed;
		std::string fileName = "";
		if( argc > 1){
				fileName = argv[1];
				ed = Editor(fileName);
		}
		else{
				ed = Editor();
		}

		ncursesInit();			//Initialize ncurses

		
		while(ed.getMode() != 'x')
		{
				ed.updateStatus();
				ed.printStatusLine();
				ed.printBuff();
				int input = getch();                // Blocking until input
				ed.handleInput(input);
		}

		
		
		refresh();				//Refresh display
		endwin();				//End ncurses mode
		return 0;
}
