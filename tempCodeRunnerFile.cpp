#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <thread>
using namespace std;


void display_menu();
void waitForKeyPress(); 
int toss_rand();
void toss();
void select_user_team(string user_team[11]);
void select_comp_team(string comp_team[11]);
void scoreboard(int i, string pak_player_names[11], int balls, int wickets, int score, int totalscore);
void instructions();
void copy(string x[11], string y[11]);
void player_turn();
void computer_turn();

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

int batORbowl;

int comp_score[10];
int user_score[10];
int team1_scores[10];
int team2_scores[10];
string user_team[11];
string comp_team[11];

int main()
{
     srand(static_cast<unsigned>(time(0))); //cant include in function to ensure randomness
    
        display_menu();
        waitForKeyPress();
    
    
}


void display_menu()                          //MENU
{
    cout << "HAND CRICKET 2024"
         <<endl
         <<endl
         <<"1. PLAY\n"
         <<"2. INSTRUCTIONS\n"
         <<"3. EXIT\n"
         <<endl
         <<"Choose an option to begin: ";

         int choice;
         cin>>choice;

         switch(choice)
         {
            case 1:
                select_user_team( user_team); select_comp_team(comp_team);
				void toss();
                if(batORbowl ==1){player_turn(); computer_turn();}
                if(batORbowl ==2){computer_turn();player_turn(); }
                break;
            case 2: instructions();
            case 3:
                 return;
            default: 
                cout<<"";
         }
       

}


void toss(int &batORbowl) //it will return the toss to the play function
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

        int bat_bowl;   //toss won, u bowl first = 2
        cin >> bat_bowl;

      
        
    }
    else if(!toss)
    {
        cout<<"opponent won the toss."<<endl;
        bool comp_decide = toss_rand();
        if(comp_decide){batORbowl= 2;}          //toss lost, computer  bats first
        else if(!comp_decide){batORbowl =1;}    //toss lost, computer bowls first
    }

    


}


void computer_turn()
{
    int player_score;
   int wickets = 0;
    int score=0;
    int total_score = 0;
    int comp_guess;
    int i= 0;
    int balls =0;
    cout<<"Its your turn to bowl! \n";
    do{
        

      
        
        scoreboard( i,  user_team,  balls,  wickets,  score,  total_score);
        do {cout<<endl<<"Select your option(1-6) : "; cin>>score;}while(score <1 || score>6);
        int comp_guess = rand()%7;
        
         cout<<endl;
        
         cout<< "Computer selected score: "<< comp_guess; cout<<endl;

        if( comp_guess == score)  //case for OUT
        {   
            cout<< "The umpire signals \"OUT\"\n";
            comp_score[i] = player_score;
            wickets++;
            i++;
            player_score = 0;

            
        }

        else
        {
            player_score += score;
            total_score += score;
        }
        scoreboard( i,  user_team,  balls,  wickets,  score,  total_score);
    }while(wickets != 10);
cout<<endl<<"All out!! Target is "<<total_score + 1<<endl;
}

void player_turn()
{
    int score;
	int total_score = 0;
	int wickets = 0;
	
	char arr[11] = { 'a','b','c' };
	for (int i = 0;i < 11 ; i++) {
		//2sec break code to e entered/
		cout << arr[i] << " at batting" << endl;


		while (true) {
			int random_no = rand() % 7;
			cout << "enter a score between 1 and 6:";
			cin >> score;
			if (score < 1 || score>6)
				cout << "enter a number between 1 and 6" << endl;
			if (score == random_no) {
				score = 0;
				cout << "out!" << endl;
				wickets++;
				break;
			
			}
			else {
				total_score += score;
				cout << "current score: " << total_score << endl;
			}
		}
	}
	cout << "All out! Total score is: " << total_score << endl;
	cout << "Target: " << total_score + 1 << endl;

}

void select_comp_team(string comp_team[11])
{
int choose;
		do{
			cout << "------------Select computer team------------\n";
			cout << "1. Pakistan Cricket Team\n";
			cout << "2. England Cricket Team\n";
			cout << "3. Australian Cricket Team\n";
			cout << "4. Indian Cricket Team\n";
			cout << "5.New Zealand Cricket Team\n";
			cout << "6.West Indies Cricket Team\n";
			cout << "7.Afghanistan Cricket Team\n";
			cout << "8.South African Cricket Team\n";
			cout << "9.Srilanka Cricket Team \n";
			cout << "10.Bangladesh Cricket Team \n";
			cout << "Select an option\n";
			cin >> choose;
			switch (choose){
			case 1:
				copy(comp_team, pak_player_names);
				break;
			case 2:
				copy(comp_team, eng_player_names);
				break;
			case 3:
				copy(comp_team, aus_player_names);
				break;
			case 4:
				copy(comp_team, ind_player_names);
				break;
			case 5:
				copy(comp_team, nz_player_names);
				break;
			case 6:
				copy(comp_team, wi_player_names);
				break;
			case 7:
				copy(comp_team, afg_player_names);
				break;
			case 8:
				copy(comp_team, sa_player_names);
				break;
			case 9:
				copy(comp_team, sri_player_names);
				break;
			case 10:
				copy(comp_team, ban_player_names);
				break;
			default:
				cout << "Please select an appropriate option\n";
				break;
			}
		} while (choose > 10 || choose < 1);
	}

void select_user_team(string user_team[11]){
int choose;
		do{
			cout << "------------Select your team------------\n";
			cout << "1. Pakistan Cricket Team\n";
			cout << "2. England Cricket Team\n";
			cout << "3. Australian Cricket Team\n";
			cout << "4. Indian Cricket Team\n";
			cout << "5.New Zealand Cricket Team\n";
			cout << "6.West Indies Cricket Team\n";
			cout << "7.Afghanistan Cricket Team\n";
			cout << "8.South African Cricket Team\n";
			cout << "9.Srilanka Cricket Team \n";
			cout << "10.Bangladesh Cricket Team \n";
			cout << "Select an option\n";
			cin >> choose;
			switch (choose){
			case 1:
				copy(user_team, pak_player_names);
				break;
			case 2:
				copy(user_team, eng_player_names);
				break;
			case 3:
				copy(user_team, aus_player_names);
				break;
			case 4:
				copy(user_team, ind_player_names);
				break;
			case 5:
				copy(user_team, nz_player_names);
				break;
			case 6:
				copy(user_team, wi_player_names);
				break;
			case 7:
				copy(user_team, afg_player_names);
				break;
			case 8:
				copy(user_team, sa_player_names);
				break;
			case 9:
				copy(user_team, sri_player_names);
				break;
			case 10:
				copy(user_team, ban_player_names);
				break;
			default:
				cout << "Please select an appropriate option\n";
				break;
			}
		} while (choose > 10 || choose < 1);
	}



void scoreboard(int i, string pak_player_names[11], int balls, int wickets, int score, int totalscore)
{
cout<<" -------SCOREBOARD------- "<< endl;
cout <<"Player name: " << pak_player_names[i] << endl;
cout<< "Balls played: " << balls << endl;
cout<<"Balls : " <<balls << endl;
cout<<"	Wickets: " <<wickets << endl;
cout<<"Score: " <<score << endl;
cout<<"Total score: " << totalscore << endl; 
} 



   


void waitForKeyPress() {
    cout << "Press any key to continue...\n";
    system("read -n1"); // Waits for any key press
}

void instructions() {
    cout << "INSTRUCTIONS:\n\n";
    cout << "1. This is a hand cricket game where you select scores (1-6).\n";
    cout << "2. If your score matches the opponent's guess, the player is OUT.\n";
    cout << "3. You and the computer take turns batting and bowling.\n";
    cout << "4. The team with the highest score wins.\n";
}

int toss_rand(){


    // Generate a random number (0 or 1)
    return  rand() % 2;
}

void copy(string x[11], string y[11])
{
    for (int i = 0; i < 11; i ++)
    {
        x[i] = y[i];
    }
}