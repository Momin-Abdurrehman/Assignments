#include <iostream>
#include <ncurses.h>

void display_menu();
void waitForKeyPress();

using namespace std;
string pak_player_names[11] ={"Babar Azam","Mohammad Rizwan","Fakhar Zaman","Iftikhar Ahmed","Shadab Khan","Imad Wasim","Shaheen Afridi","Haris Rauf","Naseem Shah","Mohammad Nawaz","Usama Mir"};
string eng_player_names[11]= {"Jos Buttler","Dawid Malan","Alex Hales","Moeen Ali","Liam Livingstone","Ben Stokes","Sam Curran","Chris Woakes","Adil Rashid","Mark Wood","Chris Jordan"};
string aus_player_names[11];
string ind_player_names[11];
string nz_player_names[11];
string wi_player_names[11];     //ill update the other teams later
string afg_player_names[11];    
string sa_player_names[11];
string sri_player_names[11];
string ban_player_names[11];

int player1_score;
int player2_score;
int team1_scores[10];
int team2_scores[10];

int main()
{
    while(true) {
        display_menu();
        void waitForKeyPress();
        system("clear");
        }
    
}

/*
void display_menu()                          //MENU
{
    cout << "HAND CRICKET 2024"
         <<endl
         <<endl
         <<"1. PLAY"
         <<"2. INSTRUCTIONS"
         <<"3. EXIT\n"
         <<endl
         <<"Choose an option to begin: ";

         int choice;
         cin>>choice;

         switch(choice)
         {
            case 1:(toss function)(play function);
            case 2: (instructions function);
            case 3: return;
            default: cout<<"";
         }
       

}
*/

void toss(); //it will return the toss to the play function
void Score_board();    //team1 and team 2 array will keep updating with every turn         



/*                                                                  //this will make program look better
void waitForKeyPress() {
    initscr();          // Initialize ncurses mode
    noecho();           // Disable echoing of key presses
    cbreak();           // Disable line buffering

    printw("Press any key to go to the Main Menu...\n");
    refresh();          // Refresh the screen to display the message
    getch();            // Wait for a key press

    endwin();           // End ncurses mode
}
*/
