


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
	char *menuItems[] = {"PLAY Music","EXIT" };
	int choice = 0;

	refreshBackground();

	WINDOW* titleBox = UI::titleBox();
	CACurse::mvwprintw(titleBox, 2, 5, "CA Music Generator");
	CACurse::wrefresh(titleBox);

	choice = UI::showNavMenu(mainWindow, "-MAIN MENU-", menuItems, 2);

	if (UI::popUpConfirm(menuItems[choice - 1]))
	{
		switch (choice)
		{
		case 1:
			playEmot();
			break;
		case 2:
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
	int emot;
	/*string binary = std::bitset<8>(stoi(patternCode)).to_string();
	char *ruleSet = (char*)binary.c_str();*/
	emot = stoi(UI::showInputMessage(mainWindow, "Enter emotion", "Choose(1-4) 1=happy,2=sad,3=angry,4=fear"));
	playPattern(CA::emotValues(emot));
}


void CA::playPattern(vector<int> emotVars) {

	int nCells = 100, choice = 0, nSteps = 100;
	int patternCode = emotVars[0], emot = emotVars[1], speed = emotVars[2], key = emotVars[3], velocity = emotVars[4], scale = emotVars[5];
	string disppp = to_string(patternCode);
	string ruleSet = bitset<16>(patternCode).to_string();
	const char *dispat = disppp.c_str();
	flag = midiOutOpen(&device, midiport, 0, 0, CALLBACK_NULL);
	if (flag != MMSYSERR_NOERROR) {
		printf("Error opening MIDI Output.\n");
	}

	char *x = new char[nCells + 2];
	char *x_old = new char[nCells + 2];
	char *x_older = new char[nCells + 2];
	//cMj[0] = 'C'; xNotes[1] = 'D'; xNotes[2] = 'E'; xNotes[3] = 'F'; xNotes[4] = 'G'; xNotes[5] = 'A'; xNotes[0] = 'B';
	//resize the console window based on number of lines user asked to see
	CACurse::resize_term(40, 90);
	//title box that displays the code# and ruleset of the current pattern
	WINDOW* patternTitle = UI::titleBox();
	CACurse::mvwprintw(patternTitle, 1, 16, "%s", dispat);
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
			x_older[i] = x_old[i];
			x_old[i] = x[i];
			
		}

		for (int i = 1; i <= nCells; i++)
		{
			
			ruleSet = std::bitset<16>(patternCode).to_string();

			//define each possible rule in the neighborhood
			rules[15] = (x_old[i - 1] == ' ' && x_old[i] == ' ' && x_old[i + 1] == ' ' && x_older[i] == ' ');
			rules[14] = (x_old[i - 1] == '#' && x_old[i] == ' ' && x_old[i + 1] == ' ' && x_older[i] == ' ');
			rules[13] = (x_old[i - 1] == ' ' && x_old[i] == '#' && x_old[i + 1] == ' ' && x_older[i] == ' ');
			rules[12] = (x_old[i - 1] == ' ' && x_old[i] == ' ' && x_old[i + 1] == '#' && x_older[i] == ' ');
			rules[11] = (x_old[i - 1] == ' ' && x_old[i] == ' ' && x_old[i + 1] == ' ' && x_older[i] == '#');
			rules[10] = (x_old[i - 1] == '#' && x_old[i] == '#' && x_old[i + 1] == ' ' && x_older[i] == ' ');//
			rules[9] = (x_old[i - 1] == '#' && x_old[i] == ' ' && x_old[i + 1] == '#' && x_older[i] == ' ');//
			rules[8] = (x_old[i - 1] == '#' && x_old[i] == ' ' && x_old[i + 1] == ' ' && x_older[i] == '#');//
			rules[7] = (x_old[i - 1] == ' ' && x_old[i] == '#' && x_old[i + 1] == '#' && x_older[i] == ' ');//
			rules[6] = (x_old[i - 1] == ' ' && x_old[i] == '#' && x_old[i + 1] == ' ' && x_older[i] == '#');//
			rules[5] = (x_old[i - 1] == ' ' && x_old[i] == ' ' && x_old[i + 1] == '#' && x_older[i] == '#');//
			rules[4] = (x_old[i - 1] == '#' && x_old[i] == '#' && x_old[i + 1] == '#' && x_older[i] == ' ');//
			rules[3] = (x_old[i - 1] == '#' && x_old[i] == ' ' && x_old[i + 1] == '#' && x_older[i] == '#');
			rules[2] = (x_old[i - 1] == '#' && x_old[i] == '#' && x_old[i + 1] == ' ' && x_older[i] == '#');
			rules[1] = (x_old[i - 1] == ' ' && x_old[i] == '#' && x_old[i + 1] == '#' && x_older[i] == '#');
			rules[0] = (x_old[i - 1] == '#' && x_old[i] == '#' && x_old[i + 1] == '#' && x_older[i] == '#');
			//loop through each binary digit int he user defined ruleset
			for (int a = 0; a < 16; a++)
			{
				//if binary digit is a 0, dont use rule
				if (ruleSet.at(a) == '0')
				{
					rules[a] = false;
				}

			}
			//check if character in old generate satisfies rule and set character in new array to "alive"
			if (rules[0] || rules[1] || rules[2] || rules[3] || rules[4] || rules[5] || rules[6] || rules[7]||rules[8] || rules[9] || rules[10] || rules[11] || rules[12] || rules[13] || rules[14] || rules[15])
			{
				x[i] = '#';
			}
			//otherwise, if rules are not satisfied, set new character to "dead"
			else
			{
				x[i] = ' ';
			}

			 //if key is pressed, end pattern loop
			if (CACurse::wgetch(patternWindow) != ERR  && CACurse::wgetch(patternWindow) != 10)
			{
				choice = displayChangeMenu();

				switch (choice)
				{
				case 1:
					emot = stoi(UI::showInputMessage(patternWindow, "Enter emotion", "Choose(1-4) 1=happy,2=sad,3=angry,4=fear"));
					emotVars=emotValues(emot);
					patternCode = emotVars[0], emot = emotVars[1], speed = emotVars[2], key = emotVars[3], velocity = emotVars[4], scale = emotVars[5];
					nSteps += 100;
					break;

				case 2:
					speed = stoi(UI::showInputMessage(patternWindow, "Enter Speed", "Choose Speed, <75=fast, >200=slow "));
					break;

				case 3:
					//UI::hitEnter(patternWindow);
					refreshBackground();
					mainMenu();
					break;
				}
				disppp = to_string(patternCode);
				dispat = disppp.c_str();
				CACurse::resize_term(40, 90);
				patternTitle = UI::titleBox();
				CACurse::mvwprintw(patternTitle, 1, 16, "%s", dispat);
				CACurse::wrefresh(patternTitle);
		}
			else if(CACurse::wgetch(patternWindow) == 10)
			{

				break;

			}


		playNote(i, x[i], key, velocity,scale); // checks if cell is alive and plays a note
		x[0] = x[nCells];
		x[nCells + 1] = x[1];
		}
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
	CACurse::delwin(patternWindow);
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
void CA::playNote(int i,char x,int startNote, int velocity,int scale)
{
	message.data[0] = 0x90;  // MIDI note-on message (requires to data bytes)
	message.data[1] = 60;
	message.data[2] = velocity;   // MIDI note-on message: Key velocity (100 = loud)
	message.data[3] = 0;     // Unused parameter

	int keyNote = startNote;
	//checks if cell is alive then plays midi
	if (i == 45 && x == '#')
	{
		//setting note to play
		message.data[1] =keyNote;
		//plaing the midi
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

//WIP
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


vector<int> CA::emotValues(int emot)
{
	srand(time(NULL));
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 65535);
	int c=48,cS=49,d=50,dS=50,e=64,f=65,fS=42,g=43,gS=44,a=45,aS=46,b=35;// setting lowest octave for all notes, B is one lowest for anger
//C	C#	D	D#	E	F	F#	G	G#	A	A#	B



	vector<int> emotVars = {22,1,200,c,0};//{patternCode,emotion,tempo,key,velocity,major/minor(1/0)}

	if (emot == 1)//happy
	{
		emotVars = {dis(gen),1,rand() % 200 +50,e,50,1};
	}
	else if (emot == 2)//sad
	{
		emotVars = {dis(gen),2,rand() % 50 +250,f,50,0 };
	}
	else if (emot ==3)//angry
	{
		emotVars = {dis(gen),3,rand() % 150 + 100,b,75,1};
	}
	else if (emot == 4)//fear
	{
		emotVars = {dis(gen),4,rand() % 150 + 100,dS,75,0};
	}

	return emotVars;

}




