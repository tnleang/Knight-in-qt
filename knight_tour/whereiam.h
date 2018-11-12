#ifndef WHEREIAM_H
#define WHEREIAM_H


#include <iostream>
#include <cstdlib>

const int BOARD_SIZE = 8;
const int POSSIBLE_MOVE = 8;


const char _COL[8] = {'A','B','C','D','E','F','G','H'};
const int ROW[8] = {1,2,3,4,5,6,7,8};
const int LAST_STEP = BOARD_SIZE * BOARD_SIZE;

//clockwise move
const int MOVE_ROW[POSSIBLE_MOVE] = {2,1,-1,-2,-2,-1,1,2};
const int MOVE_COL[POSSIBLE_MOVE] = {1,2,2,1,-1,-2,-2,-1};

//counter clockwise
//const int MOVE_ROW[POSSIBLE_MOVE] = {2,1,-1,-2,-2,-1,1,2};
//const int MOVE_COL[POSSIBLE_MOVE] = {-1,-2,-2,-1,1,2,2,1};


struct whereIAm
{
    int row, col;
    int level; // nth step

    whereIAm()
    {
        row = -1;
        col = -1;
        level = -1;
    }

    whereIAm(int r, int c, int lv)
    {
        row = r;
        col = c;
        level = lv;
    }
};


struct move
{
    whereIAm position;
    int wayOut;

    move() : position()
    {
        wayOut = 0;
    }
    move(int row, int col, int level) : position(row,col,level)
    {

    }

};




/*==============================================================
 *
 *  HELPER FUNCTIONS
 *
 *==============================================================*/

//check for the boundary of the board
bool isValidMove (int row, int col)
{
    return ( (row >= 0 && col>= 0) &&
             (row < BOARD_SIZE && col < BOARD_SIZE) );
}

//check for the boundary and the availibilty in the spot
bool isAvailible ( const whereIAm &pos , int **board)
{
    return ( isValidMove(pos.row,pos.col) && board[pos.row][pos.col] == 0);
}



#endif // WHEREIAM_H
