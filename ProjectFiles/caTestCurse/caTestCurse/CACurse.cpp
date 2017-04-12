

#include "CACurse.h"
#include <string>

WINDOW* CACurse::initscr()
{
	return ::initscr();
}

WINDOW* CACurse::newwin(int nlines, int ncols, int begin_y, int begin_x)
{
	return ::newwin(nlines, ncols, begin_y, begin_x);
}

int CACurse::delwin(WINDOW *win)
{
	return ::delwin(win);
}

int CACurse::resize_term(int lines, int columns)
{
	return ::resize_term(lines, columns);
}

int CACurse::wgetch(WINDOW *win)
{
	return ::wgetch(win);
}

int CACurse::curs_set(int visibility)
{
	return ::curs_set(visibility);
}

int CACurse::noecho()
{
	return ::noecho();
}

int CACurse::echo()
{
	return ::echo();
}

int CACurse::cbreak()
{
	return ::cbreak();
}

int CACurse::mvwprintw(WINDOW *win, int y, int x, char *fmt, ...)
{
	int ret = ERR;

	va_list args;
	va_start(args, fmt);
	::wmove(win, y, x);
	ret = ::vwprintw(win, fmt, args);
	va_end(args);

	return ret;
}

int CACurse::mvwprintwCentered(WINDOW *win, int y, char *fmt, ...)
{
	int ret = ERR;
	int x = (getmaxx(win) / 2) - (strlen(fmt) / 2);


	va_list args;
	va_start(args, fmt);
	::wmove(win, y, x);
	ret = ::vwprintw(win, fmt, args);
	va_end(args);

	return ret;

}

int CACurse::mvprintw(int y, int x, char *fmt, ...)
{
	int ret = ERR;

	va_list args;
	va_start(args, fmt);
	::move(y, x);
	ret = ::mvprintw(y, x, fmt);
	va_end(args);


	return ret;

}


int CACurse::wbox(WINDOW *win, chtype verch, chtype horch)
{
	return ::box(win, verch, horch);
}

int CACurse::wattron(WINDOW *win, int attrs)
{
	return ::wattron(win, attrs);
}

int CACurse::wattroff(WINDOW *win, int attrs)
{
	return ::wattroff(win, attrs);
}

int CACurse::attron(int attrs)
{
	return ::attron(attrs);
}

int CACurse::attroff(int attrs)
{
	return ::attroff(attrs);
}

int CACurse::init_pair(short pair, short f, short b)
{
	return ::init_pair(pair, f, b);
}

int CACurse::start_color()
{
	return ::start_color();
}

int CACurse::wrefresh(WINDOW *win)
{
	return ::wrefresh(win);
}

int CACurse::refresh()
{
	return ::refresh();
}

int CACurse::flash()
{
	return ::flash();
}

void CACurse::endwin()
{
	::endwin();
}

int CACurse::werase(WINDOW *win)
{
	return ::werase(win);
}


int CACurse::wclear(WINDOW *win)
{
	return ::wclear(win);
}



int CACurse::wbkgd(WINDOW *win, chtype ch)
{
	return ::wbkgd(win, ch);
}