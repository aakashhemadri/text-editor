#include<ncurses.h>
#include<string>

#include"editor.h"

void ncursesInit(){
		initscr();				//start ncurses mode
		noecho();				//Disabling keystroke echo
		cbreak();				//Disableing line buffering
		keypad(stdscr,true);	//Enable special keys to be recorded
}

int main(int argc, char* argv[]){
		EDITOR ed;
		std::string fileName = "";
		if( argc > 1){
				fileName = argv[1];
				ed = EDITOR(fileName);
		}
		else{
				ed = EDITOR();
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
