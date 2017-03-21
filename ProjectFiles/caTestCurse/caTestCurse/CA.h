#pragma once


#ifndef CA_H
#define CA_H

#include "curses.h"
#include "CACurse.h"
#include "UI.h"
#include <string>
#include <vector>
#include <mmsystem.h>


class CA
{
public:


	bool rules[7]; //array of possible neighbor configurations
	WINDOW *mainWindow;


	static CA& getInstance();
	~CA();

	void setUp();
	void start();
	void welcomeScreen();
	void refreshBackground();
	void mainMenu();
	void playThree();
	void genThree();
	void genFive();
	void displayPattern(int nSteps, char* ruleSet, char* patternCode);

	void playPattern(int nSteps, char * ruleSet, char * patternCode);

	void playFive();

	void playProp();

	void exit();

	void stuff();



};

#endif /* CA_H */
