#include <ncurses.h>
#include <iostream>
#include <string.h>
#include <locale.h>
#include <algorithm>
#include <random>
#include "timercpp.h"
#define sizex 15
#define sizey 15

bool finished = false;
int arr[sizey*sizex];
int finisharr[sizey*sizex];
double timetoplay = 0;
int moves = 0;
int n = sizeof(arr)/sizeof(arr[0]);
int k;
bool debug = false;

bool isMultipleof (int val, int mult)  
{  
	while ( val > 0 )  
		val = val - mult;  
	
	if ( val == 0 )  
		return false;  
	
	return true;  
} 

void refreshboard()
{
	printw("╭");
	if(sizex*sizey > 9 && sizex*sizey <= 99)
	{
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
	} else
	{
		for(int i=0;i<sizex-1;i++)
		{
			printw("───┬");
		}
		printw("───╮\n");
		for(int i=0;i<sizey-1;i++)
		{
			for(int j=0;j<sizex+1;j++)
			{
				printw("│   ");
			}
			printw("\n├───");
			for(int j=0;j<sizex-1;j++)
			{
				printw("┼───");
			}
			printw("┤\n");
		}
		for(int j=0;j<sizex+1;j++)
		{
			printw("│   ");
		}
		printw("\n╰");
		for(int i=0;i<sizex-1;i++)
		{
			printw("───┴");
		}
		printw("───╯\n");
		int xcount = 0;
		for(int i=1;i<sizey*2;i+=2)
		{
			for(int j=1;j<sizex*4;j+=4)
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
	
	move(sizey*2+1, 0);
	printw("Moves: %d\n", moves);
	if (debug)
	{
		printw("\n");
		for(int i=0;i<sizex*sizey;i++)
		{
			printw("%i ",arr[i]);
		}
		printw("\n");
		for(int i=0;i<sizex*sizey;i++)
		{
			printw("%i ",finisharr[i]);
		}
	}
}

void refreshTime()
{
	move(sizey*2+2, 0);
	printw("Time: %f\n", timetoplay);
	refresh();
}

bool kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return true;
    } else {
        return false;
    }
}

int main(int argc, char ** argv)
{
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
	keypad(stdscr, TRUE);
	curs_set(0);
	for(int i=1;i<sizex*sizey+1;i++)
	{
		arr[i-1] = i;
	}
	arr[sizex*sizey-1] = 0;
	srand(time(NULL));
	for(int i=0;i<10000;i++)
	{
		switch (rand() % 4+1)
		{
			// numbered cases correspond to arrow keys, ex. w -> up arrow
			case 1:
			{
				int *itr = std::find(arr, arr + n, 0);
				if(std::distance(arr, itr) <= sizex*sizey-sizex-1)
				{
					std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) + sizex]);
				}
			}
			break;
			case 2:
			{
				int *itr = std::find(arr, arr + n, 0);
				if(std::distance(arr, itr) >= sizex)
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
	for(int i=1;i<sizex*sizey+1;i++)
	{
		finisharr[i-1] = i;
	}
	finisharr[sizex*sizey-1] = 0;
	Timer t = Timer();
	t.setInterval([&]() {
    	timetoplay += 0.001;
	}, 1);
	refreshboard();
	refresh();
	while (1)
	{
		if(finished == false && kbhit())
		{
			k = getch();
			if(k != 0)
			{
				switch (k)
				{
					// numbered cases correspond to arrow keys, ex. w -> up arrow
					case 'w':
					case 259:
					{
						int *itr = std::find(arr, arr + n, 0);
						if(std::distance(arr, itr) <= sizex*sizey-sizex-1)
						{
							std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) + sizex]);
							moves += 1;
							erase();
							refreshboard();
							refresh();
						}
					}
					break;
					case 's':
					case 258:
					{
						int *itr = std::find(arr, arr + n, 0);
						if(std::distance(arr, itr) >= sizex)
						{
							std::swap(arr[std::distance(arr, itr)], arr[std::distance(arr, itr) - sizex]);
							moves += 1;
							erase();
							refreshboard();
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
							refreshboard();
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
							refreshboard();
							refresh();
						}
					}
					break;
					case 32: //space bar
					debug = true;
					erase();
					refreshboard();
					refresh();
					break;
					case 'q':
					endwin();
					default:
					break;
				}
			}
		} else
		{
			refreshTime();
		}
		if(std::equal(arr, arr+n, finisharr))
		{
			finished = true;
			t.stop();
		}
	}
}
