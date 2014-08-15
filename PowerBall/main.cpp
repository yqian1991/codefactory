//
//  PowerBall.cpp
//
//  Created by Leonardo Rocha on 11/29/13.
//  Copyright (c) 2013 Leonardo Rocha. All rights reserved.
//

#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

//Function Protoypes
void setSeed();                         //This will set the seed for the random numbers
int randomWhiteNumber();                //This will get a random number 1-59
int randomRedNumber();                  //This will get a random number 1-35
bool checkArray(int [], int, int);      //This will check to see if a random number has already been found
int displayMenu();                      //This will display the intro menu and let the user buy tickets
int won(int, bool);                     //This function determines how much money a ticket won
//global constants
const int SIZE = 6;                     //This is the number of balls per ticket
const int MAX_WHITE = 58;               //This is the range of the white balls
const int MAX_RED = 34;                 //This is the range of the red balls
const int waysToWin = 9;

int main(int argc, const char * argv[])
{
    int tickets = displayMenu();        //Welcome screen lets you buy tickets
    int spending = tickets * 2;         //Charges you for the tickets
    int randomTickets[tickets][SIZE];   //Ticket number holders
    int randomPowerNumber[SIZE];        //Power ball numbers
    int arrayHolder[SIZE];              //Temporary ticket holder
    int ballCounter = 0;                //Keeps track of winning balls in a ticket
    bool redBall;                       //Keeps track if the red ball matches
    int cashWon = 0;                    //Cash won Accumalator
    int lost = 0;
    int winningTickets[waysToWin];
    setSeed();                          //Sets random seed

    /*
     The next set of instructions will randomly generates the first 5 white balls and the last ball is the red ball
                                White balls are 1-59 and the red ball are 1-35
     */

    cout<<"Powerballs: ";
    for(int i = 0; i<SIZE; i++)
    {
        randomPowerNumber[i] = randomWhiteNumber();                   //Randomly generates a number 1-59
        while(checkArray(randomPowerNumber, i, randomPowerNumber[i])) //If random number is in use generate another random number
        {
            randomPowerNumber[i] = randomWhiteNumber();               //Randomly generates a number 1-59
        }
        if(i == (SIZE - 1))                                           //If the increment is the last one it is the red ball
        {
            randomPowerNumber[i] = randomRedNumber();                 //So it generates a number 1-35
        }
        cout<<"["<<randomPowerNumber[i]<<"] ";                        //This displays the number at current increment
    }
    cout<<endl;

    cout<<"Your tickets\n";


    /*
     The following code is a nested loop the first loop indicates the ticket we are at
     the second loop indicates the number we are at in the current ticket.
     The number of tickets is user defined. The main purpose of the code is to generate random numbers
     for a ticket to simulate quick picks.
     */
    for(int i = 0; i < tickets; i++)
    {
        ballCounter = 0;                //This counter keeps track of all the numbers that match the white power balls
        redBall = false;                //This boolean variable keeps track if you have a redball match
        for(int j = 0; j < SIZE; j++)
        {
            arrayHolder[j] = randomWhiteNumber();               //This will generates a random number 1-59 at current location
            while(checkArray(arrayHolder, j, arrayHolder[j]))   //If number generated is in use enter while loop
            {
                arrayHolder[j] = randomWhiteNumber();           //Generate a random number for current location
            }
            if(j == (SIZE - 1))                                 //If current location is the red ball generate a number 1-35
            {
                arrayHolder[j] = randomRedNumber();
            }else{
                if(checkArray(randomPowerNumber, (SIZE-1), arrayHolder[j]))       //If current number generated is a white ball
                    ballCounter++;                                         //Check to see if the number is a powerball number if
            }                                                              //it matches increment ball counter
            randomTickets[i][j] = arrayHolder[j];                          //Stores number in ticket
            cout<<"["<<randomTickets[i][j]<<"] ";                          //Display number to screen
        }

        cout<<"\nWhiteballs match : "<<ballCounter<<" ";     //This displays the number of white balls that match the powerballs
                                                             //White balls

        //This checks to see if the tickets redball matches the powerballs redball
        if(arrayHolder[SIZE - 1] == randomPowerNumber[SIZE-1])
        {
            cout<<"The red ball matches too!";
            redBall = true;
        }

        cashWon += won(ballCounter, redBall);       //This adds the cash won from the ticket to your cash fund


        //The following else if statements just keeps track of how many tickets of each level actually won
        if(ballCounter == 5 && redBall)
            winningTickets[0]++;
        else if(ballCounter == 5)
            winningTickets[1]++;
        else if(ballCounter == 4 && redBall)
            winningTickets[2]++;
        else if(ballCounter == 4)
            winningTickets[3]++;
        else if(ballCounter == 3 && redBall)
            winningTickets[4]++;
        else if(ballCounter == 3)
            winningTickets[5]++;
        else if(ballCounter == 2 && redBall)
            winningTickets[6]++;
        else if(ballCounter == 1 && redBall)
            winningTickets[7]++;
        else if(redBall)
            winningTickets[8]++;
        else
            lost++;
        cout<<endl;
    }
    //The folling code outputs to the user the number of tickets that won and display the number of losing tickets
    cout<<"You have "<<winningTickets[0]<<" tickets that is a grand prize winner"<<endl;
    cout<<"You have "<<winningTickets[1]<<" tickets winning $1,000,000"<<endl;
    cout<<"You have "<<winningTickets[2]<<" tickets winning $10,000"<<endl;
    cout<<"You have "<<winningTickets[3] + winningTickets[4]<<" tickets winning $100"<<endl;
    cout<<"You have "<<winningTickets[5] + winningTickets[6]<<" tickets winning $7"<<endl;
    cout<<"You have "<<winningTickets[7] + winningTickets[8]<<" tickets winning $4"<<endl;
    cout<<"You have "<<lost<<" losing tickets"<<endl;

    //The following code outputs how much money you spent and how much money you won
    cout<<"You spent $"<<spending<<endl;
    cout<<"You won $"<<cashWon<<endl;
}

/****************************************************************************
 *                          displayMenu()                                   *
 *    The displayMenu function outputs intro menu to screen and it allows   *
 *    The user to buy 1 to 250000 tickets                                   *
 ***************************************************************************/
int displayMenu()
{
    int tickets;
    cout<<"Powerball Simulator\n";
    cout<<"5 White Balls will be random generated and the last ball is red\n";
    cout<<"Each ticket cost $2\nEnter how many ticket will you like to buy: ";
    cin>>tickets;

    while((tickets <= 0 || tickets > 250000))
    {
        cout<<"Please enter a number between 1-1000: ";
        cin>>tickets;
    }
    return tickets;
}

/****************************************************************************
 *                          setSeed()                                       *
 *    The set Seed function sets the seed for the rand function             *
 ***************************************************************************/

void setSeed()
{
    long seed;
    seed = time(0);
    unsigned int sseed = static_cast<unsigned int>(seed);
    srand(sseed);
}

/****************************************************************************
 *                          randomWhiteNumber()                             *
 *    The function will generate a number 1-59 and return the number        *
 ***************************************************************************/

int randomWhiteNumber()
{
    int randomVar = (rand() % MAX_WHITE)+1;
    return randomVar;
}

/****************************************************************************
 *                          randomRedNumber()                               *
 *    The function will generate a number 1-35 and return the number        *
 ***************************************************************************/
int randomRedNumber()
{
    int randomVar = (rand() % MAX_RED)+1;
    return randomVar;
}

/****************************************************************************
 *                              checkArray()                                *
 *    This function will search through array[] for a number if  the number *
 *    is found then return true if it is not found return false             *
 ***************************************************************************/
bool checkArray(int array[], int size, int number)
{
    bool has = false;
    for(int i = 0; i< size; i++)
    {
        if(array[i] == number)
        {
            has = true;
        }
    }
    return has;
}
/****************************************************************************
 *                              won()                                       *
 *    This functions compare the number of balls that match in a ticket     *
 *    and returns the amount of cash the ticket is worth                    *
 ***************************************************************************/
int won(int ballCount, bool redBall)
{
    int cash = 0;
    switch(ballCount)
    {
        case 5:
            if(redBall)
                cash = 70000000;
            else
                cash = 1000000;
            break;
        case 4:
            if(redBall)
                cash = 10000;
            else
                cash = 100;
            break;
        case 3:
            if(redBall)
                cash = 100;
            else
                cash = 7;
            break;
        case 2:
            if(redBall)
                cash = 7;
            else
                cash = 0;
            break;
        case 1:
            if(redBall)
                cash = 4;
            else
                cash = 0;
            break;
        default:
            if(redBall)
                cash = 4;
            else
                cash =0;
            break;
    }
    return cash;
}
