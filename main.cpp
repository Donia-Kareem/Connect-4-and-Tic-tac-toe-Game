#include <iostream>
#include <string>
#include "GameConnect4AndTICTAC.h"
using namespace std ;
int main() {
    string choice,ex;
    Player* players[2];
    players[0] = new Player (1, 'X');
    cout<<"If You Want Pyramid Tic-Tac-Toe Game enter 1\n If You Want Four-in-a-row Game enter 2\n ";
    cin>>ex;
    if (ex == "1"){
        cout << "Welcome to FCA first  Game. :)\n";
        cout << "Press 1 if you want to play with computer:\n ";
        cin >> choice;
        if (choice != "1")
            players[1] = new Player (2, 'o');
        else
            //Player pointer points to child
            players[1] = new RandomPlayer ('o', 5);
        GameManager gm (new my_triangle , players);
        gm.run();
    }
    else if (ex == "2"){
        cout << "Welcome to FCA second  Game. :)\n";
        cout << "Press 1 if you want to play with computer:\n ";
        cin >> choice;
        if (choice != "1")
            players[1] = new Player (2, 'o');
        else
            //Player pointer points to child
            players[1] = new RandomPlayer ('o', 7);
        GmMngr gem  (new  Connect4Board(), players);
        gem.run_gm2();
    }
    else
        cout<<"YOU OPTION FALSE \n";
    system ("pause");
}