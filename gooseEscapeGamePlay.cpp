#include <iostream>
#include <cmath>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActor.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

const int DIM1=60;
const int DIM2=40;
const int WALL_LENGTH=10;
const int SAFEZONE_SIZE=10;

const int HUMAN=5;
const int GOOSE=6;
const int WALL=7;
const int SAFEZONE=8;

int game_board[DIM1][DIM2]={0};
/*
    This file is all about the game world.  You will modify this to add
    functionality to your game, first to get it working, and later to make
    it fun.
    
    If you add or modify functions, be sure to update the prototypes in the
    gooseEscapeGamePlay.hpp file.
*/

extern Console out;

/*
With graphics, screens are given an x,y coordinate system with the origin
in the upper left corner.  So it means the coordinate axes are:
---------------->   x direction
|
|
|
|
|
V

y direction 
*/
	
/*
	Print the game world
	
    The purpose of this function is to update the console to reflect the
    current state of the game board. It works by calling the terminal_put(...)
    function once for each of the game board elements, and then calling
    terminal_refresh() once after all elements have been put. Note that empty
    spaces do not need to be drawn.
*/
// function header

player_location(int game_board[DIM1][DIM2])
{
	const int ROW=2, COL=2;
	game_board[ROW][COL]=HUMAN;
}

monster_location(int game_board[DIM1][DIM2])
{
	const int ROW=38, COL=2;
	game_board[ROW][COL]=GOOSE;
}

wall_location(int game_board[DIM1][DIM2])
{
	const int COL=31;
	
	for (int count=15; count<WALL_LENGTH; count++)
	game_board[count][COL]=WALL;
}

safezone_location(int game_board[DIM1][DIM2], int x_location_on_board, 
				  int y_location_on_board)
{
	const int COL=40;
	
	for (int count=15; count<SAFEZONE_SIZE; count++)
	game_board[count][COL]=SAFEZONE;
}


void world_print (game_board[][]...)
{
	int x_location_on_board=0, y_location_on_board=0;
	
	for (int row_count=0, row_count<DIM2, row_count++)
	{
		for (int col_count=0, col_count<DIM2, col_count++)
		{
			int value=game_board[row_count][col_count];
			
			x_location_on_board=col_count;
			y_location_on_board=row_count;
			
			if (value==HUMAN)
			{
				terminal_put(int x_location_on_board,int y_location_on_board, PLAYER_CHAR);
			}
			
			else if (value==GOOSE)
			{
				terminal_put(int x_location_on_board,int y_location_on_board, MONSTER_CHAR);
			}
					
			else if (value==WALL)
			{
				terminal_put(int x_location_on_board,int y_location_on_board, WALL_CHAR);
			}
					
			else 
			{
				terminal_put(x_location_on_board,y_location_on_board, WIN_CHAR);
			}
		}
	}
				
	// after putting items on the game board, refresh the terminal to see the items
	terminal_refresh();
}

/*
    Do something when the goose captures the player

    At the moment the function just checks to see if the player and the goose
    are in the same location.  If you want to attack or do something else, this
    function would need to change.  For example, maybe the two touch each other
    and then fight.  You could use the health that is given in the Actor class,
    and update it.  Fight, run, use weapons, it is up to you!
*/

bool captured(Actor const & player, Actor const & monster)
{
    return (player.get_x() == monster.get_x() 
         && player.get_y() == monster.get_y());
}

/*
    Move the player to a new location based on the user input
    
    All key presses start with "TK_" then the character.  So "TK_A" is the A
    key that was pressed.  At the moment, only the arrow keys are used,
    but feel free to add more keys that allow the player to do something else
    like pick up a power up.
    
    A look-up table might be useful.

    Going further: You could decide to learn about switch statements
*/
void movePlayer(int key, Actor & player, /* game board array and any other parameters */)
{
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -1;
    else if (key == TK_DOWN)
        yMove = 1;
    else if (key == TK_LEFT)
        xMove = -1;
    else if (key == TK_RIGHT)
        xMove = 1;
        
    if (player.can_move(xMove, yMove) 
      && /* new location on game board */ != SHALL_NOT_PASS)
        player.update_location(xMove, yMove);
}

/*
    What other functions do you need to make the game work?  What can you add
    to the basic functionality to make it more fun to play?
*/

