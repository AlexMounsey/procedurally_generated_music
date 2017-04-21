using namespace std;
#include "CA.h"
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
void CA::exit()
{
	UI::showMessage(mainWindow, "Bye", ":)");

}
int main(int argc, char *argv[])
{
	CA::getInstance().start();
	return 0;
}
void CA::mainMenu()
{
	char *menuItems[] = {"PLAY Music","Play Fully custom","EXIT" };
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
			playCustom();
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
	int emot;
	/*string binary = std::bitset<8>(stoi(patternCode)).to_string();
	char *ruleSet = (char*)binary.c_str();*/
	emot = stoi(UI::showInputMessage(mainWindow, "Enter emotion", "Choose(1-4) 1=Joy, 2=Sadness, 3=Anger, 4=Fear/Suspense"));
	playPattern(CA::emotValues(emot));
}
void CA::playCustom()
{
	string speed, patternCustom, key, velocity, scale;

	speed =UI::showInputMessage(mainWindow, "Enter speed", "Please enter speed, 50=fast 250=slow: ");
	patternCustom =UI::showInputMessage(mainWindow, "Enter Pattern Code", "Please enter pattern number (0-255):");
	key =UI::showInputMessage(mainWindow, "Enter Key", "Enter starting Key(24-107) e.g midC=60:");
	velocity = UI::showInputMessage(mainWindow, "Enter velocity", "Enter velocity(how hard keys are hit)(0-100):");
	scale = UI::showInputMessage(mainWindow, "Enter Scale", "Major=0 or Minor=1");

	if (patternCustom == "" || speed == "" || key == "" || velocity == ""  || scale == "")
	{
		UI::showMessage(mainWindow, "error", "Parameter missing, using defaults");
		speed = "500";
		patternCustom = "2345";
		key = "60";
		velocity = "75";
		scale = "0";
	}
	//{patternCode,emotion,tempo,key,velocity,major/minor(1/0)}
	vector<int> emotVars = { stoi(patternCustom),5,stoi(speed),stoi(key),stoi(velocity),stoi(scale) };
	playPattern(emotVars);
	refreshBackground();
	mainMenu();
}
void CA::playPattern(vector<int> emotVars) {

	int nCells = 100, choice = 0, nSteps = 1000;
	int patternCode = emotVars[0], emot = emotVars[1], speed = emotVars[2], key = emotVars[3], velocity = emotVars[4], scale = emotVars[5];
	string disppp = to_string(patternCode);
	string ruleSet = bitset<16>(patternCode).to_string();
	const char *dispat = disppp.c_str();
	m_flag = midiOutOpen(&device, midiport, 0, 0, CALLBACK_NULL);
	if (m_flag != MMSYSERR_NOERROR) {
		printf("Error opening MIDI Output.\n");
	}

	string x(nCells+2, ' ');
	string x_old(nCells + 2, ' ');
	string x_older(nCells + 2, ' ');
	//creates lvlOfCheck number of previous lines to be used in monitor
	string check(7, ' ');
	vector<string> check1;
	vector<string> check2;
	for (int i = 0; i < m_lvlOfCheck; i++)
	{
		check1.push_back(check);
		check2.push_back(check);
	}
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

	//seed cell in the middle in "alive" state
	x.at(nCells/2) = '#';

	//repeat for each row user asked for
	for (int j = 1; j <= nSteps; j++)
	{
		check2 = check1;
		check1[0] = x_old.substr(m_startCell,7);
		x_older = x_old;
		x_old = x;

		// update checker
		for (int i = m_lvlOfCheck-1; i >= 1; --i)
		{
			check1[i] = check1[i - 1];
		}

		for (int i = 1; i <= nCells; i++)
		{
			
			ruleSet = std::bitset<16>(patternCode).to_string();

			//define each possible rule in the neighborhood
			m_rules[15] = (x_old[i - 1] == ' ' && x_old.at(i) == ' ' && x_old[i + 1] == ' ' && x_older.at(i) == ' ');
			m_rules[14] = (x_old[i - 1] == '#' && x_old.at(i) == ' ' && x_old[i + 1] == ' ' && x_older.at(i) == ' ');
			m_rules[13] = (x_old[i - 1] == ' ' && x_old.at(i) == '#' && x_old[i + 1] == ' ' && x_older.at(i) == ' ');
			m_rules[12] = (x_old[i - 1] == ' ' && x_old.at(i) == ' ' && x_old[i + 1] == '#' && x_older.at(i) == ' ');
			m_rules[11] = (x_old[i - 1] == ' ' && x_old.at(i) == ' ' && x_old[i + 1] == ' ' && x_older.at(i) == '#');
			m_rules[10] = (x_old[i - 1] == '#' && x_old.at(i) == '#' && x_old[i + 1] == ' ' && x_older.at(i) == ' ');//
			m_rules[9] = (x_old[i - 1] == '#' && x_old.at(i) == ' ' && x_old[i + 1] == '#' && x_older.at(i) == ' ');//
			m_rules[8] = (x_old[i - 1] == '#' && x_old.at(i) == ' ' && x_old[i + 1] == ' ' && x_older.at(i) == '#');//
			m_rules[7] = (x_old[i - 1] == ' ' && x_old.at(i) == '#' && x_old[i + 1] == '#' && x_older.at(i) == ' ');//
			m_rules[6] = (x_old[i - 1] == ' ' && x_old.at(i) == '#' && x_old[i + 1] == ' ' && x_older.at(i) == '#');//
			m_rules[5] = (x_old[i - 1] == ' ' && x_old.at(i) == ' ' && x_old[i + 1] == '#' && x_older.at(i) == '#');//
			m_rules[4] = (x_old[i - 1] == '#' && x_old.at(i) == '#' && x_old[i + 1] == '#' && x_older.at(i) == ' ');//
			m_rules[3] = (x_old[i - 1] == '#' && x_old.at(i) == ' ' && x_old[i + 1] == '#' && x_older.at(i) == '#');
			m_rules[2] = (x_old[i - 1] == '#' && x_old.at(i) == '#' && x_old[i + 1] == ' ' && x_older.at(i) == '#');
			m_rules[1] = (x_old[i - 1] == ' ' && x_old.at(i) == '#' && x_old[i + 1] == '#' && x_older.at(i) == '#');
			m_rules[0] = (x_old[i - 1] == '#' && x_old.at(i) == '#' && x_old[i + 1] == '#' && x_older.at(i) == '#');
			//loop through each binary digit int he user defined ruleset
			for (int a = 0; a < 16; a++)
			{
				//if binary digit is a 0, dont use rule
				if (ruleSet.at(a) == '0')
				{
					m_rules[a] = false;
				}
			}
			//check if character in old generate satisfies rule and set character in new array to "alive"
			if (m_rules[0] || m_rules[1] || m_rules[2] || m_rules[3] || m_rules[4] || m_rules[5] || m_rules[6] || m_rules[7]||m_rules[8] || m_rules[9] || m_rules[10] || m_rules[11] || m_rules[12] || m_rules[13] || m_rules[14] || m_rules[15])
			{
				x.at(i) = '#';
			}
			//otherwise, if rules are not satisfied, set new character to "dead"
			else
			{
				x.at(i) = ' ';
			}

			 //if key is pressed, end pattern loop
			if (CACurse::wgetch(patternWindow) != ERR  && CACurse::wgetch(patternWindow) != 10)
			{
				choice = displayChangeMenu();
				string g;
				switch (choice)
				{
				case 1:
					g = UI::showInputMessage(patternWindow, "Enter emotion", "Choose(1-4) 1=Joy, 2=Sadness, 3=Anger, 4=Fear/Suspense");
					if (g == "")
					{
						g = to_string(rand() % 4 + 1);
					}
					emot = stoi(g);
					
					emotVars=emotValues(emot);
					patternCode = emotVars[0], speed = emotVars[2], key = emotVars[3], velocity = emotVars[4], scale = emotVars[5];
					nSteps += 100;
					break;

				case 2:
					UI::showMessage(patternWindow, "Change pattern Code", "Change pattern Code ");
					patternCode = genPattern();
					break;

				case 3:
					nSteps = 10;
					break;
				}

				//redraw window to clear popups
				x.at(nCells / 2) = '#';
				disppp = to_string(patternCode);
				dispat = disppp.c_str();
				CACurse::resize_term(40, 90);
				patternTitle = UI::titleBox();
				CACurse::mvwprintw(patternTitle, 1, 16, "%s", dispat);
				CACurse::wrefresh(patternTitle);
			}

			if ((std::adjacent_find(check1.begin(), check1.end(), std::not_equal_to<string>()) == check1.end()) || (check1 == check2))
			{
				patternCode = genPattern();
				//redraw window to clear popups
				disppp = to_string(patternCode);
				dispat = disppp.c_str();
				CACurse::resize_term(40, 90);
				patternTitle = UI::titleBox();
				CACurse::mvwprintw(patternTitle, 1, 16, "%s", dispat);
				CACurse::wrefresh(patternTitle);
			}
			playNote(i, x.at(i), key, velocity,scale,emot); // checks if cell is alive and plays a note

			//////visualisation for testing, uncomment to see first 15 line of pattern
			//for (int i = 1; i <= nCells; i++)
			//{
			//	CACurse::mvwprintw(patternWindow, j + 1, i, "%c", x[i]);

			//}
		}
		napms(speed);
	}
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
void CA::playNote(int i,char x,int startNote, int velocity,int scale,int emot)
{
	m_message.data[0] = 0x90;  // MIDI note-on message (requires to data bytes)
	m_message.data[1] = 60;
	m_message.data[2] = velocity;   // MIDI note-on message: Key velocity (100 = loud)
	m_message.data[3] = 0;     // Unused parameter

	if (scale == 0)//setting minor of major scales
	{
		memcpy(key, Mn, sizeof(key));
	}
	else {
		memcpy(key, Mj, sizeof(key));
	}
	int keyNote = startNote;
	//checks if cell is alive then plays midi
	if (i == m_startCell && x == '#')
	{
		//setting note to play
		m_message.data[1] = keyNote;
		//plaing the midi
		m_flag = midiOutShortMsg(device, m_message.word);
	}
	else {
		for (int j = 0; j < 7; j++)
		{
			if (i == m_startCell+1 + j && x == '#'&& emot !=2) {
				m_message.data[1] = keyNote + key[j];
				m_flag = midiOutShortMsg(device, m_message.word);
			}
			else if (i == m_startCell+1 + j && x == '#'&& emot == 2 && i % 2==0 )
			{
				m_message.data[1] = keyNote + key[j];
				m_flag = midiOutShortMsg(device, m_message.word);
			}
		}
	}
}
int CA::displayChangeMenu()
{
	char *menuItems[] = { "Change Emotion", "Change CA Pattern", "Exit"};
	int choice = 0;
	choice = UI::showChoicesMenu("Changes", menuItems, 3);
	CACurse::wrefresh(mainWindow);
	return choice;
}
int CA::genPattern()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 65535);

	return dis(gen);
}
vector<int> CA::emotValues(int emot)
{
	srand(time(NULL));
		int c = 36, cS = 37, d = 38, dS = 39, e = 40, f = 41, fS = 42, g = 43, gS = 44, a = 45, aS = 46, b = 35;// setting lowest octave for all notes, B is one lowest for anger
	vector<int> emotVars = { 22,1,200,c,0 };//{patternCode,emotion,tempo,key,velocity,major/minor(1/0)}

	if (emot == 1)//Joy 
	{
		e += 12 * (2);
		emotVars = { genPattern(),1,rand() % 150 + 150,e,30,1 };
	}
	else if (emot == 2)//Sadness
	{
		f += 12 * (rand() % 4);
		emotVars = { genPattern(),2,rand() % 150 + 400,f,30,0 };
	}
	else if (emot ==3)//Anger
	{
		b += 12 * (rand() % 3);
		emotVars = { genPattern(),3,rand() % 150 + 100,b,75,1 };
	}
	else if (emot == 4)//Fear/Suspense
	{
		dS += 12 * (rand() % 5 + 1);
		emotVars = { genPattern(),4,rand() % 150 + 100,dS,75,0 };
	}

	return emotVars;

}
//WIP
void CA::playdrum(int note)
{
	messageDrum.data[0] = 0x99;  // MIDI note-on message (requires to data bytes)
	messageDrum.data[1] = note;    // MIDI note-on message: Key number (60 = middle C)
	messageDrum.data[2] = 100;   // MIDI note-on message: Key velocity (100 = loud)
	messageDrum.data[3] = 0;     // Unused parameter


	m_flag = midiOutShortMsg(device, messageDrum.word);

}