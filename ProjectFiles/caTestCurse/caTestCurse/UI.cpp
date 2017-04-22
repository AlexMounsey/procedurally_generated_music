

#include "UI.h"
#include "CACurse.h"
#include <stdio.h>
#include <time.h>
#include "StringFormatter.h"

WINDOW* UI::setUp(int scrHeight, int scrWidth)
{
	WINDOW* mainWindow = CACurse::initscr();
	CACurse::noecho();
	CACurse::cbreak();
	CACurse::curs_set(0);
	CACurse::resize_term(scrHeight, scrWidth);

	loadColors();

	return mainWindow;
}

void UI::loadColors()
{
	CACurse::start_color();
	CACurse::init_pair(static_cast<int>(Color::Green_Black), COLOR_GREEN, COLOR_BLACK);
	CACurse::init_pair(static_cast<int>(Color::White_Black), COLOR_WHITE, COLOR_BLACK);
	CACurse::init_pair(static_cast<int>(Color::Black_Black), COLOR_BLACK, COLOR_BLACK);
	CACurse::init_pair(static_cast<int>(Color::Black_Green), COLOR_BLACK, COLOR_GREEN);
}

string UI::showInputMessage(WINDOW* parentWindow, string title, string message)
{
	WINDOW* win = UI::messageFrame();
	char * cMessage = (char*)message.c_str();
	char userInput[80];

	CACurse::curs_set(1);
	CACurse::echo();

	CACurse::wattron(win, A_BOLD | WA_BLINK);
	CACurse::mvwprintwCentered(win, 6, "CONTINUE");
	CACurse::wattroff(win, A_BOLD | WA_BLINK);

	CACurse::mvwprintw(win, 1, 1, cMessage);
	CACurse::mvwprintw(win, 3, 11, " ");
	CACurse::wrefresh(win);

	WINDOW *inputBox = CACurse::newwin(3, 40, 18, 25);
	CACurse::wbox(inputBox, 0, 0);
	CACurse::wrefresh(inputBox);

	wgetstr(win, userInput);
	CACurse::werase(win);
	CACurse::werase(inputBox);

	CACurse::curs_set(0);
	CACurse::noecho();

	return (string)userInput;
}

void UI::showMessage(WINDOW* parentWindow, string title, string message)
{
	char * cMessage = (char*)message.c_str();

	WINDOW* win = UI::messageFrame();

	CACurse::wattron(win, A_BOLD | WA_BLINK);
	CACurse::mvwprintwCentered(win, 6, "CONTINUE");
	CACurse::wattroff(win, A_BOLD | WA_BLINK);

	CACurse::mvwprintwCentered(win, 3, cMessage);
	CACurse::wrefresh(win);

	UI::hitEnter(win);
	CACurse::werase(win);

}

void UI::showLargeMessage(WINDOW* parentWindow, string title, string message)
{
	WINDOW* win = largeMessageFrame();
	WINDOW* textArea = derwin(win, 16, 71, 0, 2);
	StringFormatter::formatString(&message, 71);

	char* cTitle = (char*)title.c_str();
	char* cMessage = (char*)message.c_str();

	CACurse::wattron(win, A_BOLD | WA_BLINK);
	CACurse::mvwprintwCentered(win, 17, "CONTINUE");
	CACurse::wattroff(win, A_BOLD | WA_BLINK);

	CACurse::mvwprintwCentered(textArea, 2, cTitle);
	CACurse::mvwprintw(textArea, 4, 1, cMessage);

	CACurse::wrefresh(textArea);
	CACurse::wrefresh(win);

	UI::hitEnter(win);


}

int UI::showNavMenu(WINDOW* parentWindow, string title, char* menuItems[], int nMenuItems)
{
	int choice;
	char* cTitle = (char*)title.c_str();

	WINDOW *win = CACurse::newwin(15, 40, 14, (COLS / 2) - 20);
	WINDOW *shadowWin = CACurse::newwin(15, 40, 15, (COLS / 2) - 19);
	CACurse::wbkgd(win, COLOR_PAIR(static_cast<int>(UI::Color::Black_Green)));
	CACurse::mvwprintw(win, 2, 15, cTitle);
	CACurse::wrefresh(shadowWin);
	CACurse::wrefresh(win);

	choice = UI::navigationMenu(win, menuItems, nMenuItems);


	return choice;


}

WINDOW* UI::titleBox()
{
	WINDOW *win = CACurse::newwin(5, 40, 2, (COLS / 2) - 20);
	WINDOW *shadowWin = CACurse::newwin(5, 40, 3, (COLS / 2) - 19);
	CACurse::wbox(win, 0, 183);

	CACurse::wbkgd(win, COLOR_PAIR(static_cast<int>(UI::Color::Black_Green)));



	CACurse::wrefresh(shadowWin);
	CACurse::wrefresh(win);


	return win;
}




int UI::showChoicesMenu(string title, char* menuItems[], int nMenuItems)
{
	int choice;
	char* cTitle = (char*)title.c_str();

	WINDOW *win = CACurse::newwin(15, 40, 14, (COLS / 2) - 20);
	CACurse::wbkgd(win, COLOR_PAIR(static_cast<int>(UI::Color::Black_Green)));
	CACurse::mvwprintw(win, 2, 15, cTitle);

	choice = UI::navigationMenu(win, menuItems, nMenuItems);
	//CACurse::wclear(win);
	CACurse::werase(win);
	return choice;


}



bool UI::popUpConfirm(char* choice)
{
	char *menuItems[] = {

		"Continue",
		"Back"
	};

	int menuItemSelection;

	WINDOW *win = messageFrame();


	CACurse::wattron(win, A_BOLD);
	CACurse::mvwprintw(win, 2, 2, "You are selecting <%s>", choice);
	CACurse::wattroff(win, A_BOLD);


	menuItemSelection = navigationMenu(win, menuItems, 2);

	if (menuItemSelection == 1)
	{
		CACurse::werase(win);
		return true;
	}
	CACurse::wrefresh(win);
	return false;
}

WINDOW* UI::messageFrame()
{
	WINDOW *win = CACurse::newwin(9, 60, 16, 15);
	CACurse::wbox(win, 0, 0);
	CACurse::wbkgd(win, A_BOLD | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));

	return win;
}

WINDOW* UI::largeMessageFrame()
{
	WINDOW *win = CACurse::newwin(20, 74, 10, 8);
	CACurse::wbox(win, 0, 0);
	CACurse::wbkgd(win, A_BOLD | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));

	return win;
}

int UI::navigationMenu(WINDOW *win, char* menuItems[], int numMenuItems)
{
	int highlight = 1;
	int choice = 0;
	int keyPress;
	int n_menuChoices = numMenuItems;
	keypad(win, TRUE);
	printMenuItems(win, menuItems, numMenuItems, highlight);
	while (choice == 0)
	{
		keyPress = wgetch(win);
		switch (keyPress)
		{
		case KEY_UP:
			//if 
			if (highlight == 1)
			{
				highlight = n_menuChoices;
			}
			else
			{
				--highlight;
			}
			break;

			//if key down
		case KEY_DOWN:
			if (highlight == n_menuChoices)
			{
				highlight = 1;
			}
			else
			{
				++highlight;
			}
			break;

			//if ENTER key
		case 10:
			//set user choice to highlighted choice
			choice = highlight;
			break;

		default:
			refresh();
			break;
		}
		printMenuItems(win, menuItems, numMenuItems, highlight);
		if (choice != 0)	// User did a choice come out of the  loop 
		{
			break;
		}

	}

	return choice;

}

void UI::printMenuItems(WINDOW *win, char* menuItems[], int numMenuItems, int highlight)
{
	int n_menuChoices = numMenuItems;

	int x, y, i;

	x = 7;
	y = 5;

	CACurse::wbox(win, 0, 0);


	for (i = 0; i < n_menuChoices; ++i)
	{
		if (highlight == i + 1){
			CACurse::wattron(win, A_BOLD | WA_BLINK | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
			CACurse::mvwprintw(win, y, x, menuItems[i]);
			CACurse::wattroff(win, A_BOLD | WA_BLINK | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
		}
		else

			CACurse::mvwprintw(win, y, x, menuItems[i]);
		y++;
	}




	CACurse::wrefresh(win);
}

void UI::hitEnter(WINDOW *win)
{
	int keyPress;
	bool pressedEnter = false;

	while (CACurse::wgetch(win)!=10)
	{
		//pause for key input
		keyPress = CACurse::wgetch(win);

		//test key input
		if (keyPress == 10)
		{
			break;
		}

	}

}

