#include <ncurses.h>
#include <iostream>
#include <string.h>
#include <locale.h>
#include <algorithm>
#include <random>
#include <vector>

bool isMultipleof (int n, int mult)  
{  
	while ( n > 0 )  
		n = n - mult;  
	
	if ( n == 0 )  
		return false;  
	
	return true;  
}  

void refreshboard(int sizey, int sizex, int * arr, int moves)
{
	printw("╭");
	for(int i=0;i<sizex-1;i++)
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
	for(int i=0;i<sizex-1;i++)
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
	move(sizey*2+1, 0);
	printw("Moves: %d", moves);
}

int main(int argc, char ** argv)
{
	const int sizey = 4;
	const int sizex = 4;
	int arr[sizey*sizex];
	int moves = 0;
	int n = sizeof(arr)/sizeof(arr[0]);
	int k;
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
	std::swap(arr[0], arr[15]);
	srand(time(NULL));
	for(int i=0;i<10000;i++)
	{
		switch (rand() % 4+1)
		{
			case 1:
			{
			int *itr = std::find(arr, arr + n, 0);
			if(std::distance(arr, itr) <= 12)
			{
				std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) + sizex]);
			}
			}
			break;
			case 2:
			{
			int *itr = std::find(arr, arr + n, 0);
			if(std::distance(arr, itr) >= 4)
			{
				std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) - sizex]);
			}
			}
			break;
			case 3:
			{
			int *itr = std::find(arr, arr + n, 0);
			if(isMultipleof(std::distance(arr, itr)+1, sizex))
			{
				std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) + 1]);
			}
			}
			break;
			case 4:
			{
			int *itr = std::find(arr, arr + n, 0);
			if(isMultipleof(std::distance(arr, itr), sizex))
			{
				std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) - 1]);
			}
			}
			break;
		}
	}
	refreshboard(sizey, sizex, arr, moves);
	refresh();
	while (1)
	{
		k = getch();
		switch (k)
		{
			case 'w':
			case 259:
			{
			int *itr = std::find(arr, arr + n, 0);
			if(std::distance(arr, itr) <= 12)
			{
				std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) + sizex]);
				moves += 1;
				erase();
				refreshboard(sizey, sizex, arr, moves);
				refresh();
			}
			}
			break;
			case 's':
			case 258:
			{
			int *itr = std::find(arr, arr + n, 0);
			if(std::distance(arr, itr) >= 4)
			{
				std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) - sizex]);
				moves += 1;
				erase();
				refreshboard(sizey, sizex, arr, moves);
				refresh();
			}
			}
			break;
			case 'a':
			case 260:
			{
			int *itr = std::find(arr, arr + n, 0);
			if(isMultipleof(std::distance(arr, itr)+1, sizex))
			{
				std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) + 1]);
				moves += 1;
				erase();
				refreshboard(sizey, sizex, arr, moves);
				refresh();
			}
			}
			break;
			case 'd':
			case 261:
			{
			int *itr = std::find(arr, arr + n, 0);
			if(isMultipleof(std::distance(arr, itr), sizex))
			{
			std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) - 1]);
			moves += 1;
			erase();
			refreshboard(sizey, sizex, arr, moves);
			refresh();
			}
			}
			break;
			case 'q':
			endwin();
			default:
			break;
		}
	}
}
