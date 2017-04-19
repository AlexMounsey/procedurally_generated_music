#pragma once


#ifndef CA_H
#define CA_H

#include "curses.h"
#include "CACurse.h"
#include "UI.h"
#include <string>
#include <time.h> 
#include <random>
#include <vector>
//for vector checking
#include <algorithm>
#include <functional> 

#include <Windows.h>
#include <mmsystem.h>
#include <iostream>

#pragma comment(lib, "Winmm.lib")


class CA
{
private:
	// variable which is both an integer and an array of characters:
	union { unsigned long word; unsigned char data[4]; } message;
	union { unsigned long word; unsigned char data[4]; } messageDrum;
	int midiport = 0;       // select which MIDI output port to open
	int flag;           // monitor the status of returning functions
	HMIDIOUT device;    // MIDI device interface for sending MIDI output
	int fullCounter = 0;
	int emptyCounter = 0;
	int key[7] = { 2,4,5,7,9,11,12 };
	const int Mj[7] = { 2,4,5,7,9,11,12};		//positions of major
	const int Mn[7] = {2,3,5,7,8,11,12};		//positions of minor
	const int lvlOfCheck = 3;
	const int startCell = 45;
	bool rules[15]; //array of possible neighbor configurations
public:
	WINDOW *mainWindow;
	static CA& getInstance();
	~CA();

	void setUp();
	void start();
	void welcomeScreen();
	void refreshBackground();
	void mainMenu();
	void playCustom();
	void playPattern(vector<int> emotVars);
	void playNote(int i, char x, int startNote, int velocity, int scale, int emot);
	void exit();
	bool monitor(int i, char x, char xOld);
	void playdrum(int note);
	int displayChangeMenu();
	int genPattern();
	vector<int> emotValues(int emot);
	void playEmot();
};

#endif /* CA_H */
