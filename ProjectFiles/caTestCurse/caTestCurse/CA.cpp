


using namespace std;

#include "CA.h"
#include <string>
#include <bitset>

CA::~CA()
{
	//CACurse::endwin();
}

CA& CA::getInstance()
{
	static CA instance;
	return instance;
}

void CA::setUp()
{
	CACurse::initscr();
	CACurse::noecho();
	CACurse::cbreak();
	CACurse::curs_set(0);
	CACurse::resize_term(40, 90);

	UI::loadColors();
}


void CA::refreshBackground()
{
	CACurse::resize_term(40, 90);
	CACurse::delwin(mainWindow);

	mainWindow = CACurse::newwin(LINES, COLS, 0, 0);
	CACurse::wbkgd(mainWindow, COLOR_PAIR(static_cast<int>(UI::Color::Black_Black)));

	CACurse::wattron(mainWindow, A_BOLD | COLOR_PAIR(static_cast<int>(UI::Color::Black_Black)));
	CACurse::wattroff(mainWindow, A_BOLD | COLOR_PAIR(static_cast<int>(UI::Color::Black_Black)));



	CACurse::wrefresh(mainWindow);
}

void CA::start()
{
	setUp();
	refreshBackground();
	welcomeScreen();
}




void CA::welcomeScreen()
{
	WINDOW *win = CACurse::newwin(15, 65, 2, 12);


	while (win != NULL)
	{



		CACurse::wrefresh(win);


		CACurse::wattron(mainWindow, A_BOLD | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
		CACurse::mvwprintwCentered(mainWindow, 13, "Welcome to CA GENERATED MUSIC");
		CACurse::mvwprintwCentered(mainWindow, LINES / 2 + 5, "Press <ENTER> To Begin");
		CACurse::wattroff(mainWindow, A_BOLD | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));


		CACurse::wrefresh(mainWindow);

		UI::hitEnter(mainWindow);


		CACurse::werase(win);
		CACurse::wrefresh(win);
		refreshBackground();
		mainMenu();
		CACurse::flash();
		return;

	}
}


//DESCRIPTION: 

void CA::mainMenu()
{
	char *menuItems[] = { "GENERATE 3N CA", "GENERATE 5N CA", "PLAY 3N Music", "PLAY 5N Music", "PLAY MUSIC W/ PROPERTIES", "CHANGE STUFF", "EXIT" };
	int choice = 0;

	refreshBackground();

	WINDOW* titleBox = UI::titleBox();
	CACurse::mvwprintw(titleBox, 2, 5, "CA Music Generator");
	CACurse::wrefresh(titleBox);

	choice = UI::showNavMenu(mainWindow, "-MAIN MENU-", menuItems, 7);

	if (UI::popUpConfirm(menuItems[choice - 1]))
	{
		switch (choice)
		{
		case 1:
			genThree();
			break;

		case 2:
			genFive();
			break;

		case 3:
			playThree();
			break;

		case 4:
			playFive();
			break;

		case 5:
			playProp();
			break;

		case 6:
			stuff();
			break;

		case 7:
			exit();
			break;
		}
	}
	else
	{
		refreshBackground();
		mainMenu();
	}
}

void CA::stuff()
{

	UI::showLargeMessage(
		mainWindow,
		"TBI",
		"TBI");



	refreshBackground();
	mainMenu();
}

void CA::playThree()
{
	string nLines;  //defaults
	string patternCode;


	nLines = UI::showInputMessage(mainWindow, "Enter Lines", "Please enter number of lines: ");
	patternCode = UI::showInputMessage(mainWindow, "Enter Pattern Code", "Please enter pattern number (0-255):");
	if (patternCode == "" || nLines == "")
	{
		nLines = "20";
		patternCode = "22";
	}

	string binary = std::bitset<8>(stoi(patternCode)).to_string();
	char *ruleSet = (char*)binary.c_str();
	//displayPattern(stoi(nLines), ruleSet, (char*)patternCode.c_str());
	playPattern(stoi(nLines), ruleSet, (char*)patternCode.c_str());
	refreshBackground();
	mainMenu();
}


void CA::genThree()
{
	string nLines;  //defaults
	string patternCode;


	nLines = UI::showInputMessage(mainWindow, "Enter Lines", "Please enter number of lines: ");
	patternCode = UI::showInputMessage(mainWindow, "Enter Pattern Code", "Please enter pattern number (0-255):");
	//if (patternCode == "" || nLines == "")
	//{
	//	nLines = "20";
	//	patternCode = "22";
	//}


	string binary = std::bitset<8>(stoi(patternCode)).to_string();
	char *ruleSet = (char*)binary.c_str();
	displayPattern(stoi(nLines), ruleSet, (char*)patternCode.c_str());
	refreshBackground();
	mainMenu();

}



void CA::genFive()
{
	UI::showLargeMessage(
		mainWindow,
		"TBI",
		"TBI");

	refreshBackground();
	mainMenu();
}

void CA::displayPattern(int nSteps, char* ruleSet, char* patternCode)
{

	int nCells = 120;

	char *x = new char[nCells + 2];
	char *x_old = new char[nCells + 2];




	//resize the console window based on number of lines user asked to see
	CACurse::resize_term(nSteps + 15, nCells + 6);

	//title box that displays the code# and ruleset of the current pattern
	WINDOW* patternTitle = UI::titleBox();
	CACurse::mvwprintw(patternTitle, 1, 16, "%s", ruleSet);
	CACurse::mvwprintwCentered(patternTitle, 3, "PATTERN # %s", patternCode);
	CACurse::wrefresh(patternTitle);

	//window the pattern is displayed inside
	WINDOW* patternWindow = CACurse::newwin(LINES - 12, COLS - 4, 8, (COLS / 2) - ((COLS - 4) / 2));
	CACurse::wbkgd(patternWindow, A_BOLD | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
	CACurse::wbox(patternWindow, 0, 0);
	CACurse::wrefresh(patternWindow);

	//dont pause for input
	nodelay(patternWindow, TRUE);

	//allow window to scroll down and replace lines at the top
	//scrollok(patternWindow, TRUE);

	//fill array with "dead" cells
	for (int i = 0; i <= nCells + 1; i++)
	{
		x[i] = ' ';
	}

	//seed cell in the middle in "alive" state
	x[nCells / 2] = '#';

	//print "generation 1"
	for (int i = 1; i <= nCells; i++)
	{
		CACurse::mvwprintw(patternWindow, 1, i, "%c", x[i]);
	}

	//repeat for each row user asked for
	for (int j = 1; j <= nSteps; j++)
	{
		//put generation 1 into a seperate array for checking
		for (int i = 0; i < nCells + 2; i++)
		{
			x_old[i] = x[i];

		}

		for (int i = 1; i <= nCells; i++)
		{
			//define each possible rule in the neighborhood
			rules[7] = (x_old[i - 1] == ' ' && x_old[i] == ' ' && x_old[i + 1] == ' ');
			rules[6] = (x_old[i - 1] == ' ' && x_old[i] == ' ' && x_old[i + 1] == '#');
			rules[5] = (x_old[i - 1] == ' ' && x_old[i] == '#' && x_old[i + 1] == ' ');
			rules[4] = (x_old[i - 1] == ' ' && x_old[i] == '#' && x_old[i + 1] == '#');
			rules[3] = (x_old[i - 1] == '#' && x_old[i] == ' ' && x_old[i + 1] == ' ');
			rules[2] = (x_old[i - 1] == '#' && x_old[i] == ' ' && x_old[i + 1] == '#');
			rules[1] = (x_old[i - 1] == '#' && x_old[i] == '#' && x_old[i + 1] == ' ');
			rules[0] = (x_old[i - 1] == '#' && x_old[i] == '#' && x_old[i + 1] == '#');

			//loop through each binary digit int he user defined ruleset
			for (int a = 0; a < 8; a++)
			{
				//if binary digit is a 0, dont use rule
				if (ruleSet[a] == '0')
				{
					rules[a] = false;
				}

			}

			//check if character in old generate satisfies rule and set character in new array to "alive"
			if (rules[0] || rules[1] || rules[2] || rules[3] || rules[4] || rules[5] || rules[6] || rules[7])
			{
				x[i] = '#';

			}
			//otherwise, if rules are not satisfied, set new character to "dead"
			else
			{
				x[i] = ' ';
			}












		}
		x[0] = x[nCells];
		x[nCells + 1] = x[1];

		for (int i = 1; i <= nCells; i++)
		{
			CACurse::mvwprintw(patternWindow, j + 1, i, "%c", x[i]);

		}

		//if key is pressed, end pattern loop
		if ((CACurse::wgetch(patternWindow) != ERR))
		{
			break;
		}

		//refresh after printing line
		CACurse::wrefresh(patternWindow);

		//pause thread for .25 seconds before printing next line
		/////////////////////////****************************************************/////////////////////////////////////
		napms(10);
		//////////////////////////////////////////////////******************************************/////////////////////////////
	}

	//free memory
	delete[] x;
	delete[] x_old;

	CACurse::attron(A_BOLD | WA_BLINK | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
	CACurse::mvprintw(LINES - 3, (COLS / 2) - 2, "BACK");
	CACurse::attroff(A_BOLD | WA_BLINK | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
	CACurse::refresh();

	UI::hitEnter(patternWindow);
	refreshBackground();
	mainMenu();

}

void CA::playPattern(int nSteps, char* ruleSet, char* patternCode) {
	int nCells = 100;
	flag = midiOutOpen(&device, midiport, 0, 0, CALLBACK_NULL);
	if (flag != MMSYSERR_NOERROR) {
		printf("Error opening MIDI Output.\n");
	}

	char *x = new char[nCells + 2];
	char *x_old = new char[nCells + 2];
	char *xNotes = new char[7];
	xNotes[0] = 'C'; xNotes[1] = 'D'; xNotes[2] = 'E'; xNotes[3] = 'F'; xNotes[4] = 'G'; xNotes[5] = 'A'; xNotes[0] = 'B';

	//resize the console window based on number of lines user asked to see
	CACurse::resize_term(nSteps + 15, nCells + 6);

	//title box that displays the code# and ruleset of the current pattern
	WINDOW* patternTitle = UI::titleBox();
	CACurse::mvwprintw(patternTitle, 1, 16, "%s", ruleSet);
	CACurse::mvwprintwCentered(patternTitle, 3, "PATTERN # %s", patternCode);
	CACurse::wrefresh(patternTitle);

	//window the pattern is displayed inside
	WINDOW* patternWindow = CACurse::newwin(LINES - 12, COLS - 4, 8, (COLS / 2) - ((COLS - 4) / 2));
	CACurse::wbkgd(patternWindow, A_BOLD | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
	CACurse::wbox(patternWindow, 0, 0);
	CACurse::wrefresh(patternWindow);

	//dont pause for input
	nodelay(patternWindow, TRUE);

	//allow window to scroll down and replace lines at the top
	scrollok(patternWindow, TRUE);

	//fill array with "dead" cells
	for (int i = 0; i <= nCells + 1; i++)
	{
		x[i] = ' ';
	}

	//seed cell in the middle in "alive" state
	x[nCells / 2] = '#';

	//print "generation 1"
	for (int i = 1; i <= nCells; i++)
	{
		CACurse::mvwprintw(patternWindow, 1, i, "%c", x[i]);
	}

	//repeat for each row user asked for
	for (int j = 1; j <= nSteps; j++)
	{
		//put generation 1 into a seperate array for checking
		for (int i = 0; i < nCells + 2; i++)
		{
			x_old[i] = x[i];
		}

		for (int i = 1; i <= nCells; i++)
		{
			//define each possible rule in the neighborhood
			rules[7] = (x_old[i - 1] == ' ' && x_old[i] == ' ' && x_old[i + 1] == ' ');
			rules[6] = (x_old[i - 1] == ' ' && x_old[i] == ' ' && x_old[i + 1] == '#');
			rules[5] = (x_old[i - 1] == ' ' && x_old[i] == '#' && x_old[i + 1] == ' ');
			rules[4] = (x_old[i - 1] == ' ' && x_old[i] == '#' && x_old[i + 1] == '#');
			rules[3] = (x_old[i - 1] == '#' && x_old[i] == ' ' && x_old[i + 1] == ' ');
			rules[2] = (x_old[i - 1] == '#' && x_old[i] == ' ' && x_old[i + 1] == '#');
			rules[1] = (x_old[i - 1] == '#' && x_old[i] == '#' && x_old[i + 1] == ' ');
			rules[0] = (x_old[i - 1] == '#' && x_old[i] == '#' && x_old[i + 1] == '#');

			//loop through each binary digit int he user defined ruleset
			for (int a = 0; a < 8; a++)
			{
				//if binary digit is a 0, dont use rule
				if (ruleSet[a] == '0')
				{
					rules[a] = false;
				}

			}

			//check if character in old generate satisfies rule and set character in new array to "alive"
			if (rules[0] || rules[1] || rules[2] || rules[3] || rules[4] || rules[5] || rules[6] || rules[7])
			{
				x[i] = '#';
			}
			//otherwise, if rules are not satisfied, set new character to "dead"
			else
			{
				x[i] = ' ';
			}

			if (i == 45 && x[i] == '#')
			{
				playNote(60);
			}
			else if (i == 46 && x[i] == '#')
			{
				playNote(62);
			}
			else if (i == 47 && x[i] == '#')
			{
				playNote(64);
			}
			else if (i == 48 && x[i] == '#')
			{
				playNote(65);
			}
			else if (i == 49 && x[i] == '#')
			{
				playNote(67);
			}
			else if (i == 50 && x[i] == '#')
			{
				playNote(69);
			}
			else if (i == 51 && x[i] == '#')
			{
				playNote(71);
			}
			else if (i == 52 && x[i] == '#')
			{
				playNote(72);
			}



		}
		x[0] = x[nCells];
		x[nCells + 1] = x[1];

		for (int i = 1; i <= nCells; i++)
		{
			CACurse::mvwprintw(patternWindow, j + 1, i, "%c", x[i]);

		}

		//if key is pressed, end pattern loop
		if ((CACurse::wgetch(patternWindow) != ERR))
		{
			break;
		}

		//refresh after printing line
		CACurse::wrefresh(patternWindow);

		//pause thread for .25 seconds before printing next line
		napms(25);
	}

	//free memory
	delete[] x;
	delete[] x_old;

	CACurse::attron(A_BOLD | WA_BLINK | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
	CACurse::mvprintw(LINES - 3, (COLS / 2) - 2, "BACK");
	CACurse::attroff(A_BOLD | WA_BLINK | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
	CACurse::refresh();

	UI::hitEnter(patternWindow);
	refreshBackground();
	mainMenu();
}
void CA::playFive()
{

	UI::showLargeMessage(
		mainWindow,
		"TBI",
		"TBI");



	refreshBackground();
	mainMenu();

}

void CA::playProp()
{
	UI::showLargeMessage(
		mainWindow,
		"TBI",
		"TBI");

	refreshBackground();
	mainMenu();
}


void CA::exit()
{
	UI::showMessage(mainWindow, "Bye", ":)");

}

int main(int argc, char *argv[])
{
	CA::getInstance().start();

	return 0;
}

void CA::playNote(int note)
{


	message.data[0] = 0x90;  // MIDI note-on message (requires to data bytes)
	message.data[1] = note;    // MIDI note-on message: Key number (60 = middle C)
	message.data[2] = 1000;   // MIDI note-on message: Key velocity (100 = loud)
	message.data[3] = 0;     // Unused parameter

							 // Assign the MIDI output port number (from input or default to 0)
	midiport = 0;

	flag = midiOutShortMsg(device, message.word);



	// turn any MIDI notes currently playing:
	midiOutReset(device);

	// Remove any data in MIDI device and close the MIDI Output port
	midiOutClose(device);




}



