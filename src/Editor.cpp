#include "Editor.h"

#include <fstream>
#include <iostream>
#include <string>

Editor::Editor(){
	x=0;y=0;mode='n';
	status = "Normal Mode";
	filename = "untitled";

    buff = new Buffer();
	buff->appendLine("");

}

Editor::Editor(std::string fn)
{
	x=0;y=0;mode='n';
	status = "Normal Mode";
	filename = fn;
	
    buff = new Buffer();
	
    std::ifstream in(fn.c_str());
	if(in.is_open())
	{
			while(!in.eof())
			{
			std::string temp;
			std::getline(in, temp);
			buff->appendLine(temp);
			}
	}
    else
	{
			std::cerr << "Cannot open file: '" << fn << "'\n";
			buff->appendLine("");
	}
}

void Editor::handleInput(int c)
{
    switch(c)
    {
    case KEY_LEFT:
        moveLeft();
        return;
    case KEY_RIGHT:
        moveRight();
        return;
    case KEY_UP:
        moveUp();
        return;
    case KEY_DOWN:
        moveDown();
        return;
    }
    switch(mode)
    {
    case 'n':
        switch(c)
        {
        case 'x':
            // Press 'x' to exit
            mode = 'x';
            break;
        case 'i':
            // Press 'i' to enter insert mode
            mode = 'i';
            break;
        case 's':
            // Press 's' to save the current file
            saveFile();
            break;
        }
        break;
    case 'i':
        switch(c)
        {
        case 27:
            // The Escape/Alt key
            mode = 'n';
            break;
        case 127:
        case KEY_BACKSPACE:
            // The Backspace key
            if(x == 0 && y > 0)
            {
                x = buff->lines[y-1].length();
                // Bring the line down
                buff->lines[y-1] += buff->lines[y];
                // Delete the current line
                deleteLine();
                moveUp();
            }
            else
            {
                // Removes a character
                buff->lines[y].erase(--x, 1);
            }
            break;
        case KEY_DC:
            // The Delete key
            if(x == buff->lines[y].length() && y != buff->lines.size() - 1)
            {
                // Bring the line down
                buff->lines[y] += buff->lines[y+1];
                // Delete the line
                deleteLine(y+1);
            }
            else
            {
                buff->lines[y].erase(x, 1);
            }
            break;
        case KEY_ENTER:
        case 10:
            // The Enter key
            // Bring the rest of the line down
            if(x < buff->lines[y].length())
            {
                // Put the rest of the line on a new line
                buff->insertLine(buff->lines[y].substr(x, buff->lines[y].length() - x), y + 1);
                // Remove that part of the line
                buff->lines[y].erase(x, buff->lines[y].length() - x);
            }
            else
            {
                buff->insertLine("", y+1);
            }
            x = 0;
            moveDown();
            break;
        case KEY_BTAB:
        case KEY_CTAB:
        case KEY_STAB:
        case KEY_CATAB:
        case 9:
            // The Tab key
            buff->lines[y].insert(x, 4, ' ');
            x += 4;
            break;
        default:
            // Any other character
            buff->lines[y].insert(x, 1, char(c));
            x++;
            break;
        }
        break;
    }
}
void Editor::moveLeft()
{
    if(x-1 >= 0)
    {
        x--;
        move(y, x);
    }
}

void Editor::moveRight()
{
    if(x+1 < COLS && x+1 <= buff->lines[y].length())
    {
        x++;
        move(y, x);
    }
}

void Editor::moveUp()
{
    if(y-1 >= 0)
        y--;
    if(x >= buff->lines[y].length())
        x = buff->lines[y].length();
    move(y, x);
}

void Editor::moveDown()
{
    if(y+1 < LINES-1 && y+1 < buff->lines.size())
        y++;
    if(x >= buff->lines[y].length())
        x = buff->lines[y].length();
    move(y, x);
}
void Editor::printBuff()
{
    for(int i=0; i<LINES-1; i++)
    {
        if(i >= buff->lines.size())
        {
            move(i, 0);
            clrtoeol();
        }
        else
        {
            mvprintw(i, 0, buff->lines[i].c_str());
        }
        clrtoeol();
    }
    move(y, x);
}
void Editor::printStatusLine()
{
    attron(A_REVERSE);
    mvprintw(LINES-1, 0, status.c_str());
    clrtoeol();
    attroff(A_REVERSE);
}
void Editor::deleteLine()
{
    buff->removeLine(y);
}

void Editor::deleteLine(int i)
{
    buff->removeLine(i);
}
void Editor::saveFile()
{
    if(filename == "")
    {
        // Set filename to untitled
        filename = "untitled";
    }

    std::ofstream f(filename.c_str());
    if(f.is_open())
    {
        for(int i=0; i<buff->lines.size(); i++)
        {
            f << buff->lines[i] << std::endl;
        }
        status = "Saved to file!";
    }
    else
    {
        status = "Error: Cannot open file for writing!";
    }
    f.close();
}
void Editor::updateStatus()
{
    switch(mode)
    {
    case 'n':
        // Normal mode
        status = "Normal Mode";
        break;
    case 'i':
        // Insert mode
        status = "Insert Mode";
        break;
    case 'x':
        // Exiting
        status = "Exiting";
        break;
    }
    status += "\tCOL: " + std::to_string(x) + "\tROW: " + std::to_string(y);
}

