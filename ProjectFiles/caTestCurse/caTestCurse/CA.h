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
	int notestate = 0;  // keeping track of when the note is on or off
	int velocity = 100; // MIDI note velocity parameter value
	int midiport;       // select which MIDI output port to open
	int flag;           // monitor the status of returning functions
	HMIDIOUT device;    // MIDI device interface for sending MIDI output
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

	void playNote(int note);

	void stuff();



};

#endif /* CA_H */
