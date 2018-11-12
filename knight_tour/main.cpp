#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

#include "tour.h"

using namespace std;

const char __COL[8] = {'A','B','C','D','E','F','G','H'};


int main(int argc, char *argv[])
{
    char col[8] = {'A','B','C','D','E','F','G','H'};
    int row[8] = {1,2,3,4,5,6,7,8};
    cout<<setw(49)<<setfill('-')<<"-"<<setfill(' ')<<endl;
    for(int i = 7; i >= 0; --i)
    {
        for(int j = 0; j < 8; ++j)
            cout<<"|"<<setw(4)<<col[j]<<row[i];
        cout<<"|"<<endl<<setw(49)<<setfill('-')<<"-"<<setfill(' ')<<endl;
    }

    int intRow = 1; //default for debugging
    int intCol = 0; //default for debugging
    string input;
    knightTour tour;
    char command;
    cout << "[P]rint    One point tour via [S]tack    One point tour via [Q]ueue   [T]wo points tour    [A]ll possible tour    e[X]it :";
    cin >> command;
    while (toupper(command) != 'X')
    {
        switch(toupper(command))
        {
            case ('P'):
                break;
            case ('A'):
            case ('S'):
            case ('Q'):
                do {
                    cout << "Insert the first position: ";
                    cin.ignore(255, '\n');
                    cin >> input;
                    intRow = (int) (input[1]) - '0';
                    for (int i = 0; i < 8; i++)
                        if (toupper(input[0]) == __COL[i])
                            intCol = i;
                    tour.clearBoard();
                    //cout << "First position at (" << intCol << "," << intRow << ")" << endl;
                }while(intRow < 1 || intRow > 8 || intCol < 0 || intCol >= 8);
                tour.setFirstPos(intRow - 1, intCol);


                if(toupper(command) == 'Q')     //with priority queue
                    tour.findTourViaQueue();
                else if(toupper(command) == 'S')//with stack
                    tour.findTour();
                else if(toupper(command) == 'A')
                    tour.findAllClosedTour();
                break;


            case ('T'):
                do {
                    cout << "Insert the first position: ";
                    cin.ignore(255, '\n');
                    cin >> input;
                    intRow = (int) (input[1]) - '0';
                    for (int i = 0; i < 8; i++)
                        if (toupper(input[0]) == __COL[i])
                            intCol = i;
                    tour.clearBoard();
                    //cout << "First position at (" << intCol << "," << intRow << ")" << endl;
                }while(intRow < 1 || intRow > 8 || intCol < 0 || intCol >= 8);
                tour.setFirstPos(intRow - 1, intCol);

                do {
                    cout << "Insert the last position: ";
                    cin.ignore(255, '\n');
                    cin >> input;
                    intRow = (int) (input[1]) - '0';
                    for (int i = 0; i < 8; i++)
                        if (toupper(input[0]) == __COL[i])
                            intCol = i;
                    //cout << "Last position at (" << intCol << "," << intRow << ")" << endl;
                }while(intRow < 1 || intRow > 8 || intCol < 0 || intCol >= 8);
                tour.setLastPos(intRow - 1, intCol);
                tour.findTourBetweenTwoPoint();
            break;

        }
        tour.print();
        if (tour.isClosedTour())
            cout << "It is a closed tour" << endl;
        else
            cout << "It is not a closed tour" << endl;
        cout << "Time run: " << tour.getTimeRun() << " second(s)" << endl;
        cout << "\n\n-------------------------------------------------------------" << endl;
        cout << "[P]rint    One point tour via [S]tack    One point tour via [Q]ueue   [T]wo points tour    [A]ll possible tour    e[X]it :";
        cin >> command;
    }
    return 0;
}

