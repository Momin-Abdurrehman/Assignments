#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()


void display_menu();
void waitForKeyPress(); 
int toss_rand();
int toss();

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
     srand(static_cast<unsigned>(time(0))); //cant include in function to ensure randomness
    
        toss();
        waitForKeyPress();
        system("clear");
    
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

int toss() //it will return the toss to the play function
{
    
    cout<<"Time for the toss!"
        <<endl
        <<"Press-->"<<endl<<"\t1. for Heads"<< endl<<"\t2 for tails "<<endl<<"Option: " ;//Head is 1 and tails is 0

    int head_tails;
    cin>>head_tails;

    bool toss = toss_rand();  //randomly generate 1 or 0 and decide on that basis
    if(toss)
    {
        cout<<"u won the toss!!"<<endl;
        cout<<endl<<"Would you like to bat first or bowl first?"
            <<endl<<"1. Bat"<<endl<<"2. Bowl"<<endl<<"Select an option: ";

        int bat_bowl;
        cin >> bat_bowl;

        if(bat_bowl == 1){ return 1;}      //toss won, u bat first = 1
        else if(bat_bowl ==2){return 2;}   //toss won, u bowl first = 2
        
    }
    else if(!toss)
    {
        cout<<"opponent won the toss."<<endl;
        bool comp_decide = toss_rand();
        if(comp_decide){return 3;}          //toss lost, computer  bats first
        else if(!comp_decide){return 4;}    //toss lost, computer bowls first
    }

    


}







/*
void Score_board();    //team1 and team 2 array will keep updating with every turn     

void computer_turn();
*/


                                                          //this will make program look better
void waitForKeyPress() {
    cout << "Press any key to continue...\n";
    system("read -n1"); // Waits for any key press
}



int toss_rand(){


    // Generate a random number (0 or 1)
    return  rand() % 2;
}