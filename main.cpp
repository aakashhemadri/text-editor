/******** INCLUDES ********/
#include<cstdlib>
#include<cstdio>
#include<errno.h>
#include<termios.h>
#include<unistd.h>
#include<ctype.h>
#include <sys/ioctl.h>
#include<iostream> 
#include<string> 
#include<fstream>   
#include"include/bufclasses.h" 

/******** DEFINES ********/
#define CTRL_KEY(k) ((k) & 0x1f)

/******** DECLARATIONS ********/


/******** TERMINAL ********/
class TERMINAL{
		public:
		std::fstream file;
		std::string buf;
		int srows;
		int scols;
		struct termios orig_termios;

		TERMINAL(const char *a = "newFile.txt"){
				file.open(a);
				buf = "";
		}
		void initEditor();
		void errorHandling(const char *);
		void enableRawMode();
		int getWindowSize();
		void editorReposition();
		void editorDrawRows();
		char editorReadKey();
		void editorProcessKeypress();
		void editorRefreshScreen();
}T;
		
void cleanup(){
		if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &T.orig_termios) == -1 )
				T.errorHandling("tcsetattr");
}
/******** INIT ********/

int main(int argc, char **argv){
		T.enableRawMode();
		T.initEditor();
		while (1){
				T.editorRefreshScreen();
				T.editorProcessKeypress();
		}
		return 0; 
} 
void TERMINAL::editorReposition(){
		buf ="";
		buf+="\x1b[2J";
		buf+="\x1b[H";
		write(STDOUT_FILENO,buf.c_str(),buf.size());
}
void TERMINAL::enableRawMode(){
		if(tcgetattr(STDIN_FILENO, &orig_termios) == -1)
				errorHandling("tcgetattr");
		atexit(cleanup);
		struct termios raw = orig_termios;
		tcgetattr(STDIN_FILENO, &raw);//RECIEVE STRUCTURE FROM TERMINAL

		raw.c_iflag &= ~(BRKINT | INPCK | ISTRIP | ICRNL | IXON);
		raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);//MODIFY TERMINAL TO DISABLE ECHO
				
		raw.c_oflag &= ~(OPOST);
		raw.c_cflag |= (CS8);
		
		raw.c_cc[VMIN] = 0;
		raw.c_cc[VTIME] = 1;

		if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)//WRITEBACK ATTRIBUTES
				errorHandling("tcsetattr");
}
void TERMINAL::errorHandling(const char *s){
		editorReposition();
		perror(s);
		exit(1);
}
char TERMINAL::editorReadKey() {
		int nread;
		char c;
		while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
				if (nread == -1 && errno != EAGAIN) 
						errorHandling("read");
		}
		return c;
}
void TERMINAL::editorProcessKeypress() {
		char c = editorReadKey();
		switch(c) {
				case CTRL_KEY('q'):
						editorReposition();
						exit(0);
				break;
		}	
}
void TERMINAL::editorRefreshScreen() {
		editorReposition();
		editorDrawRows();
		write(STDOUT_FILENO,buf.c_str(),buf.size());
}
void TERMINAL::editorDrawRows(){
		int i;
		for(i = 0; i < srows; i++) {
				//write(STDOUT_FILENO, "~", 3);
				buf+="~";
				if (i < srows - 1) {
						//write(STDOUT_FILENO, "\r\n", 2);
						buf+="\r\n";
				}
		}
}
int TERMINAL::getWindowSize() {
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    return -1;
  } else {
    scols = ws.ws_col;
    srows = ws.ws_row;
    return 0;
  }
}
void TERMINAL::initEditor(){
  if (getWindowSize() == -1) 
		errorHandling("getWindowSize");
}
