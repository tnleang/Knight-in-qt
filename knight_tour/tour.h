#ifndef KNIGHT_TOUR_TOUR_H
#define KNIGHT_TOUR_TOUR_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <ctime>


#include "whereiam.h"
#include "priorityArrayQueue.h"
#include "mystacklinkedlist.h"


/*
 *      Tools
 * 1. stack of the step in the size of 64(the number of square in 8x8 board)
 * 2. priority queue of move to determine where to go next
 * 3. stack of priority queue in each level
 * 4. board 8x8 of whereIAm
 */


/*  persudcode
 *
 *
 *      At the nth square
 *      Let (n + 1)th square be the path of step that the knight has to go next
 *          if (n + 1)th is the adjacent to nth
 *          if (n + 1)th is still unvisit
 *          if (n + 1)th has the minimum number of wayouts
 *
 *   loop ( step < 64)
 *      1. reject -> go back 1 step
 *      2. next -> go to the next adjecent in priority queue
 *      3. accept -> at the 64th step
 *                   return the solution of the knight's tour (the stack of step)
 *      4. forward -> in the adjecent, there exists of wayouts
 *                    as long as there is a wayouts keep going to the next level
 *
 *
 */

class knightTour
{
public:
    knightTour();
    ~knightTour();
    knightTour(const knightTour &other);
    knightTour& operator =(const knightTour &other);

    void print()const;
    void clearBoard();
    double getTimeRun() const;
    bool setFirstPos (int row, int col);
    bool setLastPos(int row, int col);
    void findTour(); //with stack
    void findTourViaQueue(); //with priority queue

    //check if the tour is closed
    bool isClosedTour();

    //return the set of the next move of the current one
    //bruce-force
    queue<move,int> nextMove(const whereIAm &currentPos);

    //return the number of possible waysout
    int getWaysOut (const whereIAm &currentPos);

    //============= EXTRA CREDIT =============================
    //return the set of the next move of the current one
    //That determines which one to use first
    //warnsdorff's rule
    queue<move,int> nextPriorityMove(const whereIAm &currentPos);
    void findTourBetweenTwoPoint();
    void findAllClosedTour();

private:
    int **board;
    move first_pos, last_pos;
    MyStack<move> step;
    double totalTime;

    void nukem();
    void copy(const knightTour &other);
};



knightTour::knightTour()
{
    board = new int*[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
        board[i] = new int[BOARD_SIZE];

    //inialize the board with zero
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = 0;

}

knightTour::~knightTour()
{
    nukem();
}

knightTour::knightTour(const knightTour &other)
{
    copy(other);
}

knightTour& knightTour::operator =(const knightTour &other)
{
    if (this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}


void knightTour::print()const
{
    std::cout << std::endl;
    for(int i = 7; i >= 0; --i)
    {
        for(int j = 0; j < 8; ++j)
            std::cout<<"|"<<std::setw(3)<<board[i][j]<<std::setw(4)<<_COL[j]<<ROW[i];
        std::cout<<"|"<<std::endl<<std::setw(73)<<std::setfill('-')<<"-"<<std::setfill(' ')<<std::endl;
    }
}

double knightTour::getTimeRun() const
{
    return totalTime;
}

bool knightTour::setFirstPos (int row, int col)
{
    //clearBoard();
    first_pos.position.row = row;
    first_pos.position.level = 1;
    first_pos.position.col = col;
    first_pos.wayOut = getWaysOut(first_pos.position);
    board[first_pos.position.row][first_pos.position.col] = first_pos.position.level;
    return isValidMove(first_pos.position.row , first_pos.position.col);
}

bool knightTour::setLastPos(int row,  int col)
{
    last_pos.position.row = row;
    last_pos.position.level = 64;
    last_pos.position.col = col;
    return isValidMove(last_pos.position.row , last_pos.position.col);
}

void knightTour::clearBoard()
{
    //fill the board with zero
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = 0;
    step.clear();
}

bool knightTour::isClosedTour()
{
    for(int i = 0; i < 8; i++)
        if(last_pos.position.row + MOVE_ROW[i] == first_pos.position.row &&
           last_pos.position.col + MOVE_COL[i] == first_pos.position.col)
            return true;
    return false;
}

void knightTour::nukem()
{
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
        delete[] board[i];
    delete[] board;
}

void knightTour::copy(const knightTour &other)
{
    first_pos.position.col = other.first_pos.position.col;
    first_pos.position.row = other.first_pos.position.row;
    first_pos.position.level = other.first_pos.position.level;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = other.board[i][j];
}

int knightTour::getWaysOut (const whereIAm &currentPos)
{
    int wayOut = 0;
    for (int j = 0; j < POSSIBLE_MOVE; j++)
    {
        //move throught every knight's moves and see if it is possible
        whereIAm way(currentPos.row + MOVE_ROW[j], currentPos.col + MOVE_COL[j],currentPos.level + 1);
        if (isAvailible(way,board))
        {
            wayOut++;
        }
    }
    return wayOut;
}



//Bruce force
queue<move,int> knightTour::nextMove(const whereIAm &currentPos)
{
    queue<move> nextMoves(8);
    for (int i = 0; i < POSSIBLE_MOVE; i++)
    {
        int row = currentPos.row + MOVE_ROW[i];
        int col = currentPos.col + MOVE_COL[i];
        move next(row,col,currentPos.level + 1);
        next.wayOut = getWaysOut(next.position);
        if (isAvailible(next.position, board))
            nextMoves.enqueue(next);
    }
    return nextMoves;
}



/*  persudcode
 *
 *   loop ( step < 64)
 *      1. backtrack -> go back 1 step
 *      2. forward ->
 *          1. next -> go to the next adjecent in priority queue
 *          2. accept -> at the 64th step
 *                   return the solution of the knight's tour (the stack of step)
 *          3. forward -> in the adjecent, there exists of wayouts
 *                    as long as there is a wayouts keep going to the next level
 *
 *
 */
void knightTour::findTour()
{
    clock_t start = clock();
    MyStack< queue<move> > nextStep(64);
    queue<move> temp;
    move next;

    step.push(first_pos);
    nextStep.push( nextPriorityMove(step.peek().position));
    board[step.peek().position.row][step.peek().position.col] = step.peek().position.level;


    while (step.size() <= LAST_STEP)
    {
            //reject -> go back 1 step
            //backtracking
        if (nextStep.peek().empty())
        {
            board[step.peek().position.row][step.peek().position.col] = 0;
            nextStep.pop();
            step.pop();
        }

            //forward -> in the adjecent, there exists of wayouts
            // next -> go to the next adjecent in priority queue
        else
        {
            temp = nextStep.pop();
            next = temp.dequeue();
            nextStep.push(temp);
            step.push(next);
            board[step.peek().position.row][step.peek().position.col] = next.position.level;
            //accept -> at the 64th step
            if (step.peek().position.level == 64)
            {
                last_pos = step.peek();
                break;
            }
            nextStep.push(nextPriorityMove(step.peek().position));
        }
    }
    totalTime = (clock() - start) * 1.0/ CLOCKS_PER_SEC;
}

void knightTour::findTourViaQueue()
{
    clock_t start = clock();
    queue< queue<move>,int > nextStep(64);
    queue<move> temp;
    move next;

    step.push(first_pos);
    nextStep.enqueue( nextMove(step.peek().position),64 - step.peek().position.level);
    board[step.peek().position.row][step.peek().position.col] = step.peek().position.level;
    while (step.size() <= LAST_STEP)
    {
        std::cout << step.peek().position.level;
        //reject -> go back 1 step
        //backtracking
        if (nextStep.peek().empty()) {
            std::cout << " backtrack -> " << std::endl;
            board[step.peek().position.row][step.peek().position.col] = 0;
            nextStep.dequeue();
            step.pop();
        }

            //forward -> in the adjecent, there exists of wayouts
            // next -> go to the next adjecent in priority queue
        else
        {
            std::cout << " forward -> " << std::endl;
            next = nextStep.peek().dequeue();
            step.push(next);
            board[step.peek().position.row][step.peek().position.col] = next.position.level;

            //accept -> at the 64th step
            if (step.peek().position.level == 64)
            {
                last_pos = step.peek();
                break;
            }
            nextStep.enqueue(nextMove(step.peek().position), 64 - step.peek().position.level);
        }
    }
    totalTime = (clock() - start) * 1.0/ CLOCKS_PER_SEC;
}






//===========================================================
//                  EXTRA CREDIT
//===========================================================

/*  persudcode
 *
 *  warnsdorff's rule:
 *      At the nth square
 *      Let (n + 1)th square be the path of step that the knight has to go next
 *          if (n + 1)th is the adjacent to nth
 *          if (n + 1)th is still unvisited
 *          if (n + 1)th has the minimum number of wayouts
 *
 */
queue<move,int> knightTour::nextPriorityMove(const whereIAm &currentPos)
{
    queue<move,int> nextMoves(8);
    for (int i = 0; i < POSSIBLE_MOVE; i++)
    {
        int row = currentPos.row + MOVE_ROW[i];
        int col = currentPos.col + MOVE_COL[i];
        move next(row,col,currentPos.level + 1);
        next.wayOut = getWaysOut(next.position);
        if (isAvailible(next.position, board))
            nextMoves.enqueue(next , next.wayOut);

    }
    return nextMoves;
}


void knightTour::findTourBetweenTwoPoint()
{
    clock_t start = clock();
    MyStack<move> step;
    MyStack< queue<move> > nextStep(64);
    queue<move> temp;
    move next;

    step.push(first_pos);
    nextStep.push( nextPriorityMove(step.peek().position));
    board[step.peek().position.row][step.peek().position.col] = step.peek().position.level;
    while (step.size() <= LAST_STEP)
    {
//        std::cout << step.peek().position.level
//                  << "(" << step.peek().position.col << ","<< step.peek().position.row << ")"<<std::endl;
            //reject -> go back 1 step
            //backtracking
        if (nextStep.peek().empty()) {
            //std::cout << "backtrack -> " << std::endl;
            board[step.peek().position.row][step.peek().position.col] = 0;
            nextStep.pop();
            step.pop();
        }

            //forward -> in the adjecent, there exists of wayouts
            // next -> go to the next adjecent in priority queue
        else
        {
            //std::cout << "forward -> " << std::endl;
            temp = nextStep.pop();
            next = temp.dequeue();
            nextStep.push(temp);
            step.push(next);
            board[step.peek().position.row][step.peek().position.col] = next.position.level;

            //accept -> at the 64th step and at the last step is at the wanted position
            if (step.peek().position.level == 64 &&
                    (step.peek().position.row == last_pos.position.row &&
                     step.peek().position.col == last_pos.position.col))
                break;

            nextStep.push(nextPriorityMove(step.peek().position));
        }
    }
    totalTime = (clock() - start) * 1.0 / CLOCKS_PER_SEC;
}

void knightTour::findAllClosedTour()
{
    size_t count = 0;
    clock_t start = clock();
    MyStack< queue<move> > nextStep(64);
    queue<move> temp;
    move next;

    step.push(first_pos);
    nextStep.push( nextPriorityMove(step.peek().position));
    board[step.peek().position.row][step.peek().position.col] = step.peek().position.level;

    while (!step.empty())
    {
        //reject -> go back 1 step
        //backtracking
        if (nextStep.peek().empty())
        {
            //std::cout << "backtrack -> " << std::endl;
            board[step.peek().position.row][step.peek().position.col] = 0;
            nextStep.pop();
            step.pop();
        }

            //forward -> in the adjecent, there exists of wayouts
            // next -> go to the next adjecent in priority queue
        else
        {
            //std::cout << "forward -> " << std::endl;
            temp = nextStep.pop();
            next = temp.dequeue();
            nextStep.push(temp);
            step.push(next);
            board[step.peek().position.row][step.peek().position.col] = next.position.level;
            //accept -> at the 64th step
            if (step.peek().position.level == 64)
            {
                last_pos = step.peek();
                if(isClosedTour())
                {
                    print();
                    std::cout << ++count << " closed tours" << std::endl;
                }
            }
            nextStep.push(nextPriorityMove(step.peek().position));
        }
    }
    totalTime = (clock() - start) * 1.0/ CLOCKS_PER_SEC;
}



#endif // KNIGHT_TOUR_TOUR_H
