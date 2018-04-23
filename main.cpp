#include<ncurses.h>
#include<string>

void ncursesInit(){
		initscr();				//start ncurses mode
		noecho();				//Disabling keystroke echo
		cbreak();				//Disableing line buffering
		keypad(stdscr,true);	//Enable special keys to be recorded
}

int main(int argc, char* argv[]){
		std::string fileName = "";
		if( argc > 1){
				fileName = argv[1];
		}

		ncursesInit();			//Initialize ncurses

		refresh();				//Refresh display
		endwin();				//End ncurses mode
		return 0;
}
