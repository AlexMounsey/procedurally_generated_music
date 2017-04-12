#pragma once


#include "curses.h"
#include <string>
using namespace std;

class UI
{
public:

	static WINDOW* setUp(int scrHeight, int scrWidth);
	static void loadColors();
	static int showChoicesMenu(string title, char * menuItems[], int nMenuItems);
	static bool popUpConfirm(char* choice);
	static WINDOW* titleBox();
	static WINDOW* messageFrame();
	static WINDOW* largeMessageFrame();
	static void hitEnter(WINDOW* win);
	static int navigationMenu(WINDOW *win, char* menuItems[], int numMenuItems);
	static void printMenuItems(WINDOW *win, char* menuItems[], int numMenuItems, int highlight);
	static string showInputMessage(WINDOW* parentWindow, string title, string message);
	static void showMessage(WINDOW* parentWindow, string title, string message);
	static void showLargeMessage(WINDOW* parentWindow, string title, string message);
	static int showNavMenu(WINDOW* parentWindow, string title, char* menuItems[], int nMenuItems);

	enum class Color
	{
		None = 0,
		Green_Black = 1,
		Black_Black = 2,
		White_Black=3,
		Black_Green = 4
	};
};