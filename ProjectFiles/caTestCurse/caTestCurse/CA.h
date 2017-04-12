#pragma once


#ifndef CA_H
#define CA_H

#include "curses.h"
#include "CACurse.h"
#include "UI.h"
#include <string>
#include <vector>
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
	int velocity; // MIDI note velocity parameter value
	int midiport = 0;       // select which MIDI output port to open
	int flag;           // monitor the status of returning functions
	HMIDIOUT device;    // MIDI device interface for sending MIDI output
	int key[7] = { 2,4,5,7,9,11,12 };
	int Mj[7] = { 2,4,5,7,9,11,12 };		//positions of major
	int Mn[7] = {2,1,2,2,1,3,1};		//positions of minor
	bool rules[7]; //array of possible neighbor configurations
public:


	
	WINDOW *mainWindow;


	static CA& getInstance();
	~CA();

	void setUp();
	void start();
	void welcomeScreen();
	void refreshBackground();
	void mainMenu();
	void playThree();

	//void playPattern(int * emotVar, char * emot);

	void playPattern(int nSteps, char * ruleSet, char * patternCode, int speed, char * emot);

	void playFive();

	void playProp();

	void exit();

	//void playNote(int note);

	void playNote(int i, char x);

	void playdrum(int note);

	int displayChangeMenu();

	int* emotValues(string emot);

	void playEmot();



};

#endif /* CA_H */
