#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

void game_name();
void game_board(string num_to_disp[9], int score_p1, int score_p2_cpu, int score_tie, int mode);
void win_conditions(string num_to_disp[9],bool &win);
int game_input(string num_to_disp[9],string mark,string input_num);
void final_score_multiplayer(int score_p1, int score_p2_cpu);
void ai_strategy(string num_to_disp[9]);
int ai_attack_check(string num_to_disp[9]);
int ai_defense_check(string num_to_disp[9]);
void final_score_cpu(int score_p1, int score_p2_cpu);

int main()
{
    string display[9]={"1","2","3","4","5","6","7","8","9"}; //defines the main array that is displayed to mark position
    bool win_cond= false;
    int game_mode;
    string exit;
    system("color F3");
    game_name(); //used setw command to bring the text in center.
    cout << endl;
    cout << "Enter the mode you want to play.\nMulti player (Press 1)\nVS CPU (Press 2)\nMode:";
    cin>> game_mode;
    cout << endl;

    if (game_mode == 1) //multi-player game starts
    {
        int score_p1=0, score_p2=0, score_tie=0, play_again=0;
        do // initial loop for repeated games
        {
            int player=1, turns=0, return_input=0;
            string mark, input_num;
            win_cond=false;
            string control[9]={"1","2","3","4","5","6","7","8","9"}; // array used to empty initial array for repeat
            for (int i=0; i<9; i++) // loop used to empty it
            {
                display[i]=control[i];
            }
            do // loop to change players, take their inputs and checking win conditions
            {
                game_board(display,score_p1,score_p2,score_tie,game_mode); //displaying and updating  game board
                win_conditions(display,win_cond); // checking win conditions
                if (win_cond==true || turns==9) // breaking loop if one player won or turns are 9, meaning a tie
                {
                    break;
                }
                if (player%2!=0) //switching between players
                {
                    player = 1;
                    mark = "X";
                }
                else if (player%2==0)
                {
                    player = 2;
                    mark = "O";
                }
                do // to check if input provided by the user falls under the requirements (validating input)
                {
                    cout << "Player " <<player<< ", enter number of the position you want mark: ";
                    cin >> input_num;
                    cout << endl;
                    return_input=game_input(display,mark,input_num);
                }
                while (return_input!=0);
                player++;
                turns++;
            }
            while (win_cond!=true && turns<=9);

            if (win_cond==true && mark== "X") //updates scores
            {
                score_p1++;
            }
            else if (win_cond==true && mark == "O")
            {
                score_p2++;
            }
            else if (win_cond!=true && turns==9)
            {
                score_tie++;
            }
            game_board(display,score_p1,score_p2,score_tie,game_mode); //updating scores on game board visible to user

            if (win_cond==true && mark== "X") //the player who won that game
            {
                cout << "\nPlayer 1 won."<< endl;
            }
            else if (win_cond==true && mark == "O")
            {
                cout<< "\nPlayer 2 won."<< endl;
            }
            else if (win_cond!=true && turns==9)
            {
                cout << "\nIt's a tie." <<endl;
            }
        cout << "\nDo you want to play again?\nYes (Press 1)\nNo (Press 2)"; //option to play again
        cin >>play_again;
        }
        while (play_again==1);
        cout << endl;
        final_score_multiplayer(score_p1,score_p2); // deduces the final winner
}
 //vs CPU part
    else if (game_mode == 2)
    {
        int
        score_p1=0, score_CPU=0, score_tie=0, play_again=0;
        do
        {
        int player=1, turns=0, return_input=0;
        string mark, input_num;
        win_cond=false;
        string control[9]={"1","2","3","4","5","6","7","8","9"}; // array used to empty initial array for repeat
        for (int i=0; i<9; i++) // loop used to empty array of X and O marks
        {
            display[i]=control[i];
        }
        do
        {
            game_board(display,score_p1,score_CPU,score_tie,game_mode); //displaying game board
            mark = "X";//
                do // to check if input provided by the user falls under the requirements (Validating input)
                {
                    cout<<"Enter the position you want to mark: ";
                    cin>>input_num;
                    cout << endl;
                    return_input=game_input(display,mark,input_num);
                }
                while (return_input!=0);
                turns++;  //end of players turn
                win_conditions(display,win_cond); //checks win condition for player
                if (win_cond==true || turns==9) //if win is true then breaks out of loop
                {
                    break; // Loop breaks
                }
                mark = "O";
                if(ai_attack_check(display) == -1) // If there is no situation for attack, program moves to defense.
                {
                    if(ai_defense_check(display) == -1) // If there is no situation for defense, program moves to strategic moves.
                    {
                        ai_strategy(display);
                    }
                }
                turns++;
                game_board(display,score_p1,score_CPU,score_tie,game_mode); // updating game board after CPU move
                win_conditions(display,win_cond); //checks if CPU won
                if (win_cond==true || turns==9)
                {
                    break;
                }
            }
            while (win_cond!=true && turns<=9); //turns for checking tie conditions

            if (win_cond==true && mark== "X") //updates scores
            {
                score_p1++;
            }
            else if (win_cond==true && mark == "O")
            {
                score_CPU++;
            }
            else if (win_cond!=true && turns==9)
            {
                score_tie++;
            }
            game_board(display,score_p1,score_CPU,score_tie,game_mode); //updating scores on game board visible to user

            if (win_cond==true && mark== "X") //the player who won that game
            {
                cout << "\nYou won."<< endl;
            }
            else if (win_cond==true && mark == "O")
            {
                cout<< "\nCPU won."<< endl;
            }
            else if (win_cond!=true && turns==9)
            {
                cout << "\nIt's a tie." <<endl;
            }
        cout << "\nDo you want to play again?\nYes (Press 1)\nNo (Press 2)"; //option to play again
        cin >>play_again;
        }
        while (play_again == 1);
        cout << endl;
        final_score_cpu(score_p1,score_CPU);// deduces the final winner
    }
    else
    {
        cout << "Invalid input.\nGame will now exit" ;
    }
    cout << endl<< endl;

    cout << "\n\n\n";
    cout << setw (65)<< "CS 100 Project" << endl;
    cout << setw (95)<< "Made By: Balaj Khalid (2021-10-0024) and Shehsawar Ali (2021-10-0070)" << endl;
    cout << setw (78)<< "Dated: Wednesday 13th, December 2017" << endl;
    cout << "\n\n\n";
    do
    {
        cout << "Press \"q\" to exit.";
        cin>> exit;
    } while (exit!="q");

}

void game_board(string num_to_disp[9], int score_p1, int score_p2_cpu, int score_tie, int mode)
{
    system("cls"); //used to update screen output
    system("color F3"); //changes color
    if (mode==1) // displaying multi-player essentials
    {
        cout<< "Mode: Multi player."<< endl<< endl;
        cout << "Player one (X)     Player two (O)\n\n";
        cout << "Scores:\tPlayer one:" << score_p1 << "\tPlayer two:" << score_p2_cpu << "\tTie:" << score_tie << endl << endl;
    }
    else if (mode==2) //displaying vs CPU essentials
    {
        cout<< "Mode: vs CPU."<< endl<< endl;
        cout << "Player one (X)     CPU (O)\n\n";
        cout << "Scores:\tPlayer one:" << score_p1 << "\tCPU:" << score_p2_cpu << "\tTie:" << score_tie << endl<< endl;
    }
    int height_board = 9; //defines boards dimensions
    int width_board = 30;
    for (int i=0; i<height_board;i++) //printing board
    {
       if (i==1 || i==4 || i==7) //printing lines with number positions
        {
            for (int j=0; j<width_board; j++)
            {

                if (j == 5)
                {
                    cout << num_to_disp[i-1];
                }
                else if (j == 14)
                {
                    cout << num_to_disp[i];
                }
                else if (j == 23)
                {
                    cout << num_to_disp[i+1];
                }
                if (j == 9)
                {
                    cout << "|";
                }
                else if (j == 18)
                {
                    cout << "|";
                }
                else
                {
                    cout << " ";
                }
            }
        }
        else if (i==2 || i==5) // printing lines with ___|_____|_____
        {
            for (int j=0; j<width_board; j++)
            {

                if (j == 10)
                {
                    cout << "|";
                }
                else if (j == 20)
                {
                    cout << "|";
                }
                else
                {
                    cout << "_";
                }
            }
        }
        else //printing |   |
        {
            for (int j=0; j<width_board; j++)
            {

                if (j == 10)
                {
                    cout << "|";
                }
                else if (j == 20)
                {
                    cout << "|";
                }
                else
                {
                    cout << " ";
                }
            }
        }
    cout << "\n" ;
    }
} //end

void win_conditions(string num_to_disp[9],bool &win)
{
        for (int i=0; i<9;i+=3)
        {
            if (num_to_disp[i]==num_to_disp[i+1] && num_to_disp[i+1]==num_to_disp[i+2]) //horizontal win condition
            {
                win = true;
            }
        }
        for (int i=0; i<9;i+=1)
        {
            if (num_to_disp[i]==num_to_disp[i+3] && num_to_disp[i+3]==num_to_disp[i+6]) //vertical win condition
            {
                win = true;
            }
        }
            if (num_to_disp[0]==num_to_disp[4] && num_to_disp[4]==num_to_disp[8]) //first diagonal win condition
            {
            win = true;
            }
            if (num_to_disp[2]==num_to_disp[4] && num_to_disp[4]==num_to_disp[6]) //second diagonal win condition
            {
            win = true;
            }
}

int game_input(string num_to_disp[9],string mark, string input_num)
{
        string control[9]={"1","2","3","4","5","6","7","8","9"}; //to validate input
        int error_input=0, correct_input=0;
        if (input_num.length()>1) //checking for error i.e. numbers like 25 or -2
        {
            error_input=-1;
        }
        if (error_input==0) // if no error then making changes in array
        {
            for (int i=0; i<9; i++)
            {
                if (input_num == control[i] && num_to_disp[i]!="X" && num_to_disp[i]!="O") // added and conditions for "X" and of "O" so it doesn't mark X and O again if already marked.
                {
                    num_to_disp[i]=mark;
                    correct_input=1;
                }

            }
            if (correct_input==1) //if input is marked then return 0 otherwise display error and take input again
                {
                    return 0;
                }
            else // solve error in case if an alphabet or special character is entered
                {
                    cout << "Invalid input.\n\n";
                    return -1;
                }
        }
        else // returning error of double number or negative ones
            {
                    cout << "Invalid input.\n\n";
                    return -1;
            }
}

void final_score_multiplayer(int score_p1, int score_p2_cpu) //comparing the number of wins to output series winner
{
    if (score_p1>score_p2_cpu)
    {
        cout<< "Player 1 has won the series! Congratulations"<< endl;
    }
    else if (score_p2_cpu>score_p1)
    {
        cout<< "Player 2 has won the series! Congratulations"<< endl;
    }
    else if (score_p1==score_p2_cpu)
    {
        cout << "Series is tie between the two players" << endl;
    }
}

// ARTIFICIAL INTELLIGENCE

int ai_defense_check(string num_to_disp[9])
{
    //To stop user from making his final move (three consecutive marks)
    //below are combinations of different moves for each row

     if(num_to_disp[0] == "X" && num_to_disp[1] == "X" && num_to_disp[2] == "3") //Row1
    {num_to_disp[2] = "O"; return 0;}
    else if(num_to_disp[1] == "X" && num_to_disp[2] == "X"  && num_to_disp[0] == "1")
    {num_to_disp[0] = "O"; return 0;}
    else if(num_to_disp[0] == "X" && num_to_disp[2] == "X"  && num_to_disp[1] == "2")
    {num_to_disp[1] = "O"; return 0;}

    else if(num_to_disp[3] == "X" && num_to_disp[4] == "X"  && num_to_disp[5] == "6") // Row 2
    {num_to_disp[5] = "O"; return 0;}
    else if(num_to_disp[4] == "X" && num_to_disp[5] == "X"  && num_to_disp[3] == "4")
    {num_to_disp[3] = "O"; return 0;}
    else if(num_to_disp[3] == "X" && num_to_disp[5] == "X"  && num_to_disp[4] == "5")
    {num_to_disp[4] = "O"; return 0;}

    else if(num_to_disp[6] == "X" && num_to_disp[7] == "X" && num_to_disp[8] == "9") // Row 3
    {num_to_disp[8] = "O"; return 0;}
    else if(num_to_disp[7] == "X" && num_to_disp[8] == "X" && num_to_disp[6] == "7")
    {num_to_disp[6] = "O"; return 0;}
    else if(num_to_disp[6] == "X" && num_to_disp[8] == "X" && num_to_disp[7] == "8")
    {num_to_disp[7] = "O"; return 0;}

    else if(num_to_disp[0] == "X" && num_to_disp[3] == "X" && num_to_disp[6] == "7") // Column 1
    {num_to_disp[6] = "O"; return 0;}
    else if(num_to_disp[3] == "X" && num_to_disp[6] == "X" && num_to_disp[0] == "1")
    {num_to_disp[0] = "O"; return 0;}
    else if(num_to_disp[0] == "X" && num_to_disp[6] == "X" && num_to_disp[3] == "4")
    {num_to_disp[3] = "O"; return 0;}

    else if(num_to_disp[1] == "X" && num_to_disp[4] == "X" && num_to_disp[7] == "8") // Column 2
    {num_to_disp[7] = "O"; return 0;}
    else if(num_to_disp[4] == "X" && num_to_disp[7] == "X" && num_to_disp[1] == "2")
    {num_to_disp[1] = "O"; return 0;}
    else if(num_to_disp[1] == "X" && num_to_disp[7] == "X" && num_to_disp[4] == "5")
    {num_to_disp[4] = "O"; return 0;}

    else if(num_to_disp[2] == "X" && num_to_disp[5] == "X" && num_to_disp[8] == "9") // Column 3
    {num_to_disp[8] = "O"; return 0;}
    else if(num_to_disp[5] == "X" && num_to_disp[8] == "X" && num_to_disp[2] == "3")
    {num_to_disp[2] = "O"; return 0;}
    else if(num_to_disp[2] == "X" && num_to_disp[8] == "X" && num_to_disp[5] == "6")
    {num_to_disp[5] = "O"; return 0;}

    else if(num_to_disp[0] == "X" && num_to_disp[4] == "X" && num_to_disp[8] == "9") // Diagonal 1
    {num_to_disp[8] = "O"; return 0;}
    else if(num_to_disp[4] == "X" && num_to_disp[8] == "X" && num_to_disp[0] == "1")
    {num_to_disp[0] = "O"; return 0;}
    else if(num_to_disp[0] == "X" && num_to_disp[8] == "X" && num_to_disp[4] == "5")
    {num_to_disp[4] = "O"; return 0;}

    else if(num_to_disp[2] == "X" && num_to_disp[4] == "X" && num_to_disp[6] == "7") // Diagonal 2
    {num_to_disp[6] = "O"; return 0;}
    else if(num_to_disp[4] == "X" && num_to_disp[6] == "X" && num_to_disp[2] == "3")
    {num_to_disp[2] = "O"; return 0;}
    else if(num_to_disp[2] == "X" && num_to_disp[6] == "X" && num_to_disp[4] == "5")
    {num_to_disp[4] = "O"; return 0;}

    else if(num_to_disp[0] == "X" && num_to_disp[2] == "X" && num_to_disp[7] == "X" && num_to_disp[1] == "O" && num_to_disp[4] == "O")
    {num_to_disp[8] = "O";}
    else{return -1;}
}

int ai_attack_check(string num_to_disp[9])
{
    //To make, whenever possible, the final move and win the game.

     if(num_to_disp[0] == "O" && num_to_disp[1] == "O" && num_to_disp[2] == "3") //Row1
    {num_to_disp[2] = "O"; return 0;}
    else if(num_to_disp[1] == "O" && num_to_disp[2] == "O"  && num_to_disp[0] == "1")
    {num_to_disp[0] = "O"; return 0;}
    else if(num_to_disp[0] == "O" && num_to_disp[2] == "O"  && num_to_disp[1] == "2")
    {num_to_disp[1] = "O"; return 0;}

    else if(num_to_disp[3] == "O" && num_to_disp[4] == "O"  && num_to_disp[5] == "6") // Row 2
    {num_to_disp[5] = "O"; return 0;}
    else if(num_to_disp[4] == "O" && num_to_disp[5] == "O"  && num_to_disp[3] == "4")
    {num_to_disp[3] = "O"; return 0;}
    else if(num_to_disp[3] == "O" && num_to_disp[5] == "O"  && num_to_disp[4] == "5")
    {num_to_disp[4] = "O"; return 0;}

    else if(num_to_disp[6] == "O" && num_to_disp[7] == "O" && num_to_disp[8] == "9") // Row 3
    {num_to_disp[8] = "O"; return 0;}
    else if(num_to_disp[7] == "O" && num_to_disp[8] == "O" && num_to_disp[6] == "7")
    {num_to_disp[6] = "O"; return 0;}
    else if(num_to_disp[6] == "O" && num_to_disp[8] == "O" && num_to_disp[7] == "8")
    {num_to_disp[7] = "O"; return 0;}

    else if(num_to_disp[0] == "O" && num_to_disp[3] == "O" && num_to_disp[6] == "7") // Column 1
    {num_to_disp[6] = "O"; return 0;}
    else if(num_to_disp[3] == "O" && num_to_disp[6] == "O" && num_to_disp[0] == "1")
    {num_to_disp[0] = "O"; return 0;}
    else if(num_to_disp[0] == "O" && num_to_disp[6] == "O" && num_to_disp[3] == "4")
    {num_to_disp[3] = "O"; return 0;}

    else if(num_to_disp[1] == "O" && num_to_disp[4] == "O" && num_to_disp[7] == "8") // Column 2
    {num_to_disp[7] = "O"; return 0;}
    else if(num_to_disp[4] == "O" && num_to_disp[7] == "O" && num_to_disp[1] == "2")
    {num_to_disp[1] = "O"; return 0;}
    else if(num_to_disp[1] == "O" && num_to_disp[7] == "O" && num_to_disp[4] == "5")
    {num_to_disp[4] = "O"; return 0;}

    else if(num_to_disp[2] == "O" && num_to_disp[5] == "O" && num_to_disp[8] == "9") // Column 3
    {num_to_disp[8] = "O"; return 0;}
    else if(num_to_disp[5] == "O" && num_to_disp[8] == "O" && num_to_disp[2] == "3")
    {num_to_disp[2] = "O"; return 0;}
    else if(num_to_disp[2] == "O" && num_to_disp[8] == "O" && num_to_disp[5] == "6")
    {num_to_disp[5] = "O"; return 0;}

    else if(num_to_disp[0] == "O" && num_to_disp[4] == "O" && num_to_disp[8] == "9") // Diagonal 1
    {num_to_disp[8] = "O"; return 0;}
    else if(num_to_disp[4] == "O" && num_to_disp[8] == "O" && num_to_disp[0] == "1")
    {num_to_disp[0] = "O"; return 0;}
    else if(num_to_disp[0] == "O" && num_to_disp[8] == "O" && num_to_disp[4] == "5")
    {num_to_disp[4] = "O"; return 0;}

    else if(num_to_disp[2] == "O" && num_to_disp[4] == "O" && num_to_disp[6] == "7") // Diagonal 2
    {num_to_disp[6] = "O"; return 0;}
    else if(num_to_disp[4] == "O" && num_to_disp[6] == "O" && num_to_disp[2] == "3")
    {num_to_disp[2] = "O"; return 0;}
    else if(num_to_disp[2] == "O" && num_to_disp[6] == "O" && num_to_disp[4] == "3")
    {num_to_disp[4] = "O"; return 0;}

    else{return -1;}
}

void ai_strategy(string num_to_disp[9])
{
    //Algorithms for the CPU to follow common Tic-Tac-Toe tricks


   if(num_to_disp[4] == "5")   //Taking center at first opportunity
    {num_to_disp[4] = "O";}

    else if(num_to_disp[4] == "O" && num_to_disp[2] == "3") //Strategic move 1a
    {num_to_disp[2] = "O";}
    else if(num_to_disp[4] == "O" && num_to_disp[2] == "O" && num_to_disp[0] == "1" && num_to_disp[1] == "2" && num_to_disp[8] == "9")
    {num_to_disp[0] = "O";}
    else if(num_to_disp[4] == "O" && num_to_disp[2] == "O" && num_to_disp[0] == "1" && num_to_disp[5] == "6" && num_to_disp[8] == "9")
    {num_to_disp[8] = "O";}



    else if(num_to_disp[4] == "O" && num_to_disp[2] == "X" && num_to_disp[6] == "7") // Strategic move 1b
    {num_to_disp[0] = "O";}
    else if(num_to_disp[4] == "O" && num_to_disp[2] == "X" && num_to_disp[6] == "O" &&  num_to_disp[0]== "1")
    {
        if(num_to_disp[8] == "9" && num_to_disp[3] == "4")
        {num_to_disp[0] == "O";}
    }
    else if(num_to_disp[4] == "O" && num_to_disp[2] == "X" && num_to_disp[6] == "O" &&  num_to_disp[0]== "1")
    {
     if(num_to_disp[8] == "9" && num_to_disp[7] == "8")
     {num_to_disp[0] == "O";}
    }


    else if(num_to_disp[4]== "X" && num_to_disp[2] == "3") //strategic move 1c
    {num_to_disp[2] = "O";}
    else if(num_to_disp[4]== "X" && num_to_disp[2] == "O" && num_to_disp[6] == "7")
    {num_to_disp[6] == "O";}
    else if(num_to_disp[4]== "X" && num_to_disp[2] == "O" && num_to_disp[6] == "O")
    {
        if(num_to_disp[5] == "6" && num_to_disp[7]== "8" && num_to_disp[8] == "9")
        {
            num_to_disp[8] == "9";
        }
        else if(num_to_disp[0] == "1" && num_to_disp[1] == "2" && num_to_disp[3] == "4")
        {
            num_to_disp[0] == "O";
        }
    }

    else
    {
        bool approval =  false; // For scenarios where random moves are suitable no strategies are required.
        int x;
        while(approval == false)
        {
        x = (rand() % 10);
        if(num_to_disp[x] != "X" && num_to_disp[x] != "O")
        {approval = true;}}
        num_to_disp[x] = "O";
    }

}

void final_score_cpu(int score_p1, int score_p2_cpu) //comparing the number of wins to output series winner
{
    if (score_p1>score_p2_cpu)
    {
        cout<< "Player 1 has won the series! Congratulations"<< endl;
    }
    else if (score_p2_cpu>score_p1)
    {
        cout<< "CPU has won the series! Congratulations"<< endl;
    }
    else if (score_p1==score_p2_cpu)
    {
        cout << "Series is tie between player 1 and CPU" << endl;
    }
}

void game_name() //made to display game name and without for loops because reversing cursor was not covered during the course
{
    cout << setw(65) << "Welcome to" <<endl<<endl;
    cout << setw(85) << "****** *** ****   *****   *     ****   ***** **** ****" <<endl;
    cout << setw(85) << "  *     *  *        *    * *    *        *   *  * *   " <<endl;
    cout << setw(85) << "  *     *  *        *   *   *   *        *   *  * *** " <<endl;
    cout << setw(85) << "  *     *  *        *  *******  *        *   *  * *   " <<endl;
    cout << setw(85) << "  *    *** ****     * *       * ****     *   **** ****" <<endl;
}
