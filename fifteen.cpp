#include <ncurses.h>
#include <iostream>
#include <string.h>
#include <locale.h>
#include <algorithm>
#include <random>
#include <vector>

const int sizex = 5;
const int sizey = 5;
int arr[sizey*sizex];
int n = sizeof(arr)/sizeof(arr[0]);
int k;

void refreshboard()
{
	printw("╭");
	for(int i=0;i<sizey-1;i++)
	{
		printw("──┬");
	}
	printw("──╮\n");
	for(int i=0;i<sizey-1;i++)
	{
		for(int j=0;j<sizex+1;j++)
		{
			printw("│  ");
		}
		printw("\n├──");
		for(int j=0;j<sizex-1;j++)
		{
			printw("┼──");
		}
		printw("┤\n");
	}
	for(int j=0;j<sizex+1;j++)
	{
		printw("│  ");
	}
	printw("\n╰");
	for(int i=0;i<sizey-1;i++)
	{
		printw("──┴");
	}
	printw("──╯\n");
	int xcount = 0;
	for(int i=1;i<sizey*2;i+=2)
	{
		for(int j=1;j<sizex*3;j+=3)
		{
			move(i,j);
			if(arr[xcount] != 0)
			{
				printw("%d", arr[xcount]);
			}
			xcount++;
		}
	}
}
/*
const string lcorner = "╭";
const string rcorner = "╮";
const string flat = "─";
const string t = "┬";
const string upt = "┴";
const string cross = "┼";
const string ulcorner;
const string urcorner;
*/

int main()
{
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	for(int i=0;i<sizex*sizey;i++)
	{
		arr[i] = i;
	}
	std::random_device rd;
  	std::mt19937 g(rd());
	std::shuffle(std::begin(arr), std::end(arr), g);
	refreshboard();
	refresh();
	while (1)
	{
		k = getch();
		switch (k)
		{
			case 'w':
			{
			int *itr = std::find(arr, arr + n, 0);
			std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) + sizex]);
			erase();
			refreshboard();
			refresh();
			}
			break;
			case 's':
			{
			int *itr = std::find(arr, arr + n, 0);
			std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) - sizex]);
			erase();
			refreshboard();
			refresh();
			}
			break;
			case 'a':
			{
			int *itr = std::find(arr, arr + n, 0);
			std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) + 1]);
			erase();
			refreshboard();
			refresh();
			}
			break;
			case 'd':
			{
			int *itr = std::find(arr, arr + n, 0);
			std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) - 1]);
			erase();
			refreshboard();
			refresh();
			}
			break;
			case 'q':
			endwin();
			default:
			break;
		}
	}
}