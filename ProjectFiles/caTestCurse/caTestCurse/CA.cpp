


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
void CA::mainMenu()
{
	char *menuItems[] = {"PLAY Music","PLAY 5N Music","EXIT" };
	int choice = 0;

	refreshBackground();

	WINDOW* titleBox = UI::titleBox();
	CACurse::mvwprintw(titleBox, 2, 5, "CA Music Generator");
	CACurse::wrefresh(titleBox);

	choice = UI::showNavMenu(mainWindow, "-MAIN MENU-", menuItems, 3);

	if (UI::popUpConfirm(menuItems[choice - 1]))
	{
		switch (choice)
		{
		case 1:
			playEmot();
			break;

		case 2:
			playFive();
			break;
		case 3:
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
void CA::playEmot()
{

	string nLines;  //defaults
	string patternCode;
	string speed;
	string emot;
	int* emotVar;
	string veloc;


	nLines = "200";
	patternCode = "30";
	speed = "250";

	string binary = std::bitset<8>(stoi(patternCode)).to_string();
	char *ruleSet = (char*)binary.c_str();






	playPattern(stoi(nLines), ruleSet, (char*)patternCode.c_str(), stoi(speed), (char*)emot.c_str()/*, stoi(veloc)*/);
}

//void CA::playPattern(int* emotVar, char* emot/*, int velo*/) {
//	int nCells = 100;
//	int keyNote = 0;
//	int choice = 0;
//	string emotion = emot;
//	std::copy(std::begin(Mj), std::end(Mj), std::begin(key));
//	flag = midiOutOpen(&device, midiport, 0, 0, CALLBACK_NULL);
//	if (flag != MMSYSERR_NOERROR) {
//		printf("Error opening MIDI Output.\n");
//	}
//
//	char *x = new char[nCells + 2];
//	char *x_old = new char[nCells + 2];
//	//cMj[0] = 'C'; xNotes[1] = 'D'; xNotes[2] = 'E'; xNotes[3] = 'F'; xNotes[4] = 'G'; xNotes[5] = 'A'; xNotes[0] = 'B';
//	//resize the console window based on number of lines user asked to see
//	CACurse::resize_term(40, 90);
//	//title box that displays the code# and ruleset of the current pattern
//	WINDOW* patternTitle = UI::titleBox();
//	//CACurse::mvwprintwCentered(patternTitle, 3, "PATTERN # %s", patternCode);
//	CACurse::mvwprintwCentered(patternTitle, 7, "Emotion %s", emot);
//	CACurse::wrefresh(patternTitle);
//	//window the pattern is displayed inside
//	WINDOW* patternWindow = CACurse::newwin(LINES -25 , COLS - 4, 8, (COLS / 2) - ((COLS - 4) / 2));
//	CACurse::wbkgd(patternWindow, A_BOLD | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
//	CACurse::wrefresh(patternWindow);
//	//dont pause for input
//	nodelay(patternWindow, TRUE);
//
//	//fill array with "dead" cells
//	for (int i = 0; i <= nCells + 1; i++)
//	{
//		x[i] = ' ';
//	}
//
//	//seed cell in the middle in "alive" state
//	x[nCells / 2] = '#';
//
//	//repeat for each row user asked for
//	for (int j = 1; j <= nSteps; j++)
//	{
//		//put generation 1 into a seperate array for checking
//		for (int i = 0; i < nCells + 2; i++)
//		{
//			x_old[i] = x[i];
//		}
//
//		for (int i = 1; i <= nCells; i++)
//		{
//			//define each possible rule in the neighborhood
//			rules[7] = (x_old[i - 1] == ' ' && x_old[i] == ' ' && x_old[i + 1] == ' ');
//			rules[6] = (x_old[i - 1] == ' ' && x_old[i] == ' ' && x_old[i + 1] == '#');
//			rules[5] = (x_old[i - 1] == ' ' && x_old[i] == '#' && x_old[i + 1] == ' ');
//			rules[4] = (x_old[i - 1] == ' ' && x_old[i] == '#' && x_old[i + 1] == '#');
//			rules[3] = (x_old[i - 1] == '#' && x_old[i] == ' ' && x_old[i + 1] == ' ');
//			rules[2] = (x_old[i - 1] == '#' && x_old[i] == ' ' && x_old[i + 1] == '#');
//			rules[1] = (x_old[i - 1] == '#' && x_old[i] == '#' && x_old[i + 1] == ' ');
//			rules[0] = (x_old[i - 1] == '#' && x_old[i] == '#' && x_old[i + 1] == '#');
//
//			//loop through each binary digit int he user defined ruleset
//			for (int a = 0; a < 8; a++)
//			{
//				//if binary digit is a 0, dont use rule
//				if (ruleSet[a] == '0')
//				{
//					rules[a] = false;
//				}
//
//			}
//
//			//check if character in old generate satisfies rule and set character in new array to "alive"
//			if (rules[0] || rules[1] || rules[2] || rules[3] || rules[4] || rules[5] || rules[6] || rules[7])
//			{
//				x[i] = '#';
//			}
//			//otherwise, if rules are not satisfied, set new character to "dead"
//			else
//			{
//				x[i] = ' ';
//			}
//			//}
//			//if ( x[i] == '#') //88keys
//			//{
//			//	//playNote(i);
//			//}
//			if (i == 45 && x[i] == '#')
//			{
//				playNote(keyNote);
//			}
//			else if (i == 46 && x[i] == '#')
//			{
//				playNote(keyNote +key[0]);
//			}
//			else if (i == 47 && x[i] == '#')
//			{
//				playNote(keyNote + key[1]);
//			}
//			else if (i == 48 && x[i] == '#')
//			{
//				playNote(keyNote + key[2]);
//			}
//			else if (i == 49 && x[i] == '#')
//			{
//				playNote(keyNote + key[3]);
//			}
//			else if (i == 50 && x[i] == '#')
//			{
//				playNote(keyNote + key[4]);
//			}
//			else if (i == 51 && x[i] == '#')
//			{
//				playNote(keyNote + key[5]);
//			}
//			else if (i == 52 && x[i] == '#')
//			{
//				playNote(keyNote + key[6]);
//			}
//		}
//		x[0] = x[nCells];
//		x[nCells + 1] = x[1];
//
//		//if key is pressed, end pattern loop
//		if ((CACurse::wgetch(patternWindow) != ERR))
//		{
//			choice = displayChangeMenu();
//
//			switch (choice)
//			{
//			case 1:
//				emotion = UI::showInputMessage(patternWindow, "Enter emotion", "Choose happy,sad, angry, excited ");
//				CACurse::wrefresh(patternWindow);
//				break;
//
//			case 2:
//				speed = stoi(UI::showInputMessage(patternWindow, "Enter Speed", "Choose Speed, 50-fast, 200-slow "));
//				CACurse::wrefresh(patternWindow);
//				break;
//
//			case 3:
//				velocity = stoi(UI::showInputMessage(patternWindow, "Enter Volume", "Enter Volume 0-100 "));
//				CACurse::wrefresh(patternWindow);
//				break;
//			}
//		}
//
//		//refresh after printing line
//		CACurse::wrefresh(patternWindow);
//		//pause before printing next line
//		napms(speed);	
//	}
//	//free memory
//	delete[] x;
//	delete[] x_old;
//	// turn any MIDI notes currently playing:
//	midiOutReset(device);
//	// Remove any data in MIDI device and close the MIDI Output port
//	midiOutClose(device);
//	CACurse::attron(A_BOLD | WA_BLINK | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
//	CACurse::mvprintw(LINES - 3, (COLS / 2) - 2, "BACK");
//	CACurse::attroff(A_BOLD | WA_BLINK | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
//	CACurse::refresh();
//	UI::hitEnter(patternWindow);
//	refreshBackground();
//	mainMenu();
//}



void CA::playPattern(int nSteps, char* ruleSet, char* patternCode, int speed, char* emot/*, int velo*/) {
	int nCells = 100;

	int choice = 0;
	velocity = 100;
	string emotion = emot;
	//std::copy(std::begin(Mj), std::end(Mj), std::begin(key));
	flag = midiOutOpen(&device, midiport, 0, 0, CALLBACK_NULL);
	if (flag != MMSYSERR_NOERROR) {
		printf("Error opening MIDI Output.\n");
	}

	char *x = new char[nCells + 2];
	char *x_old = new char[nCells + 2];
	//cMj[0] = 'C'; xNotes[1] = 'D'; xNotes[2] = 'E'; xNotes[3] = 'F'; xNotes[4] = 'G'; xNotes[5] = 'A'; xNotes[0] = 'B';
	//resize the console window based on number of lines user asked to see
	CACurse::resize_term(40, 90);
	//title box that displays the code# and ruleset of the current pattern
	WINDOW* patternTitle = UI::titleBox();
	CACurse::mvwprintw(patternTitle, 1, 16, "%s", ruleSet);
	CACurse::mvwprintwCentered(patternTitle, 3, "PATTERN # %s", patternCode);
	CACurse::mvwprintwCentered(patternTitle, 7, "Emotion %s", emot);
	CACurse::wrefresh(patternTitle);
	//window the pattern is displayed inside
	WINDOW* patternWindow = CACurse::newwin(LINES - 25, COLS - 4, 8, (COLS / 2) - ((COLS - 4) / 2));
	CACurse::wbkgd(patternWindow, A_BOLD | COLOR_PAIR(static_cast<int>(UI::Color::White_Black)));
	CACurse::wrefresh(patternWindow);
	//dont pause for input
	nodelay(patternWindow, TRUE);

	//fill array with "dead" cells
	for (int i = 0; i <= nCells + 1; i++)
	{
		x[i] = ' ';
	}

	//seed cell in the middle in "alive" state
	x[nCells / 2] = '#';

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

			playNote(i,x[i]); // checks if cell is alive and plays a note

		}
		x[0] = x[nCells];
		x[nCells + 1] = x[1];

		//if key is pressed, end pattern loop
		if ((CACurse::wgetch(patternWindow) != ERR))
		{
			choice = displayChangeMenu();

			switch (choice)
			{
			case 1:
				emotion = UI::showInputMessage(patternWindow, "Enter emotion", "Choose happy,sad, angry, excited ");
				CACurse::wrefresh(patternWindow);
				break;

			case 2:
				speed = stoi(UI::showInputMessage(patternWindow, "Enter Speed", "Choose Speed, 50-fast, 200-slow "));
				CACurse::wrefresh(patternWindow);
				break;

			case 3:
				velocity = stoi(UI::showInputMessage(patternWindow, "Enter Volume", "Enter Volume 0-100 "));
				CACurse::wrefresh(patternWindow);
				break;
			}
		}

		//refresh after printing line
		CACurse::wrefresh(patternWindow);
		//pause before printing next line
		napms(speed);
	}
	//free memory
	delete[] x;
	delete[] x_old;
	// turn any MIDI notes currently playing:
	midiOutReset(device);
	// Remove any data in MIDI device and close the MIDI Output port
	midiOutClose(device);
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
void CA::playNote(int i,char x)
{
	message.data[0] = 0x90;  // MIDI note-on message (requires to data bytes)
	message.data[1] = 60;
	message.data[2] = velocity;   // MIDI note-on message: Key velocity (100 = loud)
	message.data[3] = 0;     // Unused parameter

	int keyNote = 60;
	if (i == 45 && x == '#')
	{
		message.data[1] =keyNote;
		flag = midiOutShortMsg(device, message.word);
	}
	else if (i == 46 && x == '#')
	{
		message.data[1] =keyNote + key[0];
		flag = midiOutShortMsg(device, message.word);
	}
	else if (i == 47 && x == '#')
	{
		message.data[1] =keyNote + key[1];
		flag = midiOutShortMsg(device, message.word);
	}
	else if (i == 48 && x== '#')
	{
			message.data[1] =keyNote + key[2];
			flag = midiOutShortMsg(device, message.word);
	}
	else if (i == 49 && x == '#')
	{
		message.data[1] =keyNote + key[3];
		flag = midiOutShortMsg(device, message.word);
	}
	else if (i == 50 && x == '#')
	{
		message.data[1] =keyNote + key[4];
		flag = midiOutShortMsg(device, message.word);
	}
	else if (i == 51 && x == '#')
	{
		message.data[1] =keyNote + key[5];
		flag = midiOutShortMsg(device, message.word);
	}
	else if (i == 52 && x== '#')
	{
		message.data[1] =keyNote + key[6];
		flag = midiOutShortMsg(device, message.word);
	}

}
void CA::playdrum(int note)
{

	messageDrum.data[0] = 0x99;  // MIDI note-on message (requires to data bytes)
	messageDrum.data[1] = note;    // MIDI note-on message: Key number (60 = middle C)
	messageDrum.data[2] = 100;   // MIDI note-on message: Key velocity (100 = loud)
	messageDrum.data[3] = 0;     // Unused parameter


	flag = midiOutShortMsg(device, messageDrum.word);

}

int CA::displayChangeMenu()
{
	char *menuItems[] = { "Change Emotion", "Change Speed", "Change Volume"};
	int choice = 0;
	choice = UI::showChoicesMenu("Changes", menuItems, 3);
	CACurse::wrefresh(mainWindow);
	return choice;
}


//int* CA::emotValues(string emot)
//{
//	int john[7] = { 2,2,1,2,2,2,1 };
//	return john;
//}




