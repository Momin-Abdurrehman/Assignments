#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <thread>
#include <iomanip> // For formatting
#include <chrono>
using namespace std;

void display_menu();
void waitForKeyPress(); 
int toss_rand();
void select_gametype(int &overs);
void toss(int &batORbowl);
void select_user_team(string user_team[11]);
void select_comp_team(string comp_team[11]);
void scoreboard(int i, string pak_player_names[11], int balls, int wickets, int score, int totalscore);
void instructions();
void copy(string x[11], string y[11]);
void player_turn();
void computer_turn();
void decide_winner();
void loading();

string pak_player_names[11] = {"Babar Azam", "Mohammad Rizwan", "Fakhar Zaman", "Iftikhar Ahmed", "Shadab Khan", "Imad Wasim", "Shaheen Afridi", "Haris Rauf", "Naseem Shah", "Mohammad Nawaz", "Usama Mir"};
string eng_player_names[11] = {"Jos Buttler", "Dawid Malan", "Alex Hales", "Moeen Ali", "Liam Livingstone", "Ben Stokes", "Sam Curran", "Chris Woakes", "Adil Rashid", "Mark Wood", "Chris Jordan"};
string aus_player_names[11] = {"Aaron Finch", "David Warner", "Steve Smith", "Glenn Maxwell", "Marcus Stoinis", "Mitchell Marsh", "Pat Cummins", "Mitchell Starc", "Adam Zampa", "Josh Hazlewood", "Matthew Wade"};
string ind_player_names[11] = {"Rohit Sharma", "Virat Kohli", "KL Rahul", "Suryakumar Yadav", "Rishabh Pant", "Hardik Pandya", "Ravindra Jadeja", "Jasprit Bumrah", "Bhuvneshwar Kumar", "Yuzvendra Chahal", "Mohammed Shami"};
string nz_player_names[11] = {"Kane Williamson", "Martin Guptill", "Devon Conway", "Glenn Phillips", "James Neesham", "Mitchell Santner", "Tim Southee", "Trent Boult", "Lockie Ferguson", "Ish Sodhi", "Tom Latham"};
string wi_player_names[11] = {"Kieron Pollard", "Chris Gayle", "Nicholas Pooran", "Shimron Hetmyer", "Andre Russell", "Jason Holder", "Dwayne Bravo", "Sunil Narine", "Sheldon Cottrell", "Oshane Thomas", "Evin Lewis"};
string afg_player_names[11] = {"Mohammad Nabi", "Rashid Khan", "Mujeeb Ur Rahman", "Hazratullah Zazai", "Rahmanullah Gurbaz", "Najibullah Zadran", "Gulbadin Naib", "Asghar Afghan", "Hamid Hassan", "Karim Janat", "Naveen-ul-Haq"};
string sa_player_names[11] = {"Quinton de Kock", "Temba Bavuma", "Aiden Markram", "Rassie van der Dussen", "David Miller", "Dwaine Pretorius", "Kagiso Rabada", "Anrich Nortje", "Tabraiz Shamsi", "Lungi Ngidi", "Heinrich Klaasen"};
string sri_player_names[11] = {"Kusal Perera", "Danushka Gunathilaka", "Avishka Fernando", "Dhananjaya de Silva", "Dasun Shanaka", "Wanindu Hasaranga", "Dushmantha Chameera", "Lahiru Kumara", "Nuwan Pradeep", "Kusal Mendis", "Isuru Udana"};
string ban_player_names[11] = {"Tamim Iqbal", "Shakib Al Hasan", "Mushfiqur Rahim", "Mahmudullah", "Soumya Sarkar", "Liton Das", "Mustafizur Rahman", "Taskin Ahmed", "Mehidy Hasan", "Mohammad Saifuddin", "Afif Hossain"};

int batORbowl;
int target = 0;  // Store the target score
bool user_won = false;  // Determine the winner
int overs;
int totalBalls;

int comp_score[10];
int user_score[10];
int team1_scores[10];
int team2_scores[10];
string user_team[11];
string comp_team[11];

int main()
{
	srand(static_cast<unsigned>(time(0))); // Ensure randomness

	while (true) {
		display_menu();
		waitForKeyPress();
	}

	return 0;
}

void display_menu() {
	cout<<"\n";
	system("clear");
	cout << "============================================\n";
	cout << " \033[7;33m              HAND CRICKET 2024        \033[0m   \n";
	cout << "============================================\n";
	cout << "1. PLAY 🏏\n";
	cout << "2. INSTRUCTIONS 📜\n";
	cout << "3. EXIT ❌\n";
	cout << "============================================\n";
	cout << "Choose an option to begin: ";

	int choice;
	cin >> choice;

	switch(choice) {
		case 1:
			select_gametype(overs);
			totalBalls = overs * 6;
			select_user_team(user_team);
			select_comp_team(comp_team);
			toss(batORbowl);
			if (batORbowl == 1) { 
				player_turn(); 
				computer_turn(); 
			} else if(batORbowl==2){ 
				computer_turn(); 
				player_turn(); 
			}
			decide_winner();
			break;
		case 2:
			instructions();
			break;
		case 3:
			cout << "Exiting... Goodbye! 👋\n";
			exit(0); // Exit the program
		default:
			cout << "Invalid choice! Please select a valid option. 🔴\n";
	}

	// Ask to display the menu again or exit
	char endChoice;
	cout << "Do you want to display the menu again? (y/n): ";
	cin >> endChoice;
	if (endChoice == 'n' || endChoice == 'N') {
		cout << "Exiting... Goodbye! 👋\n";
		exit(0); // Exit the program
	}
}

void select_gametype(int &overs)
{
	system("clear");
	cout<<"Select Game Mode\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
		<<"\n"
		<<"1. Blitz (quick 2 over match)\n"
		<<"2. T 5 (5 overs)\n"
		<<"3. Super Over\n"
		<<"4. Custom\n"
		<<"5. Go Back to Main Menu\n\n"
		<<"Select your choice: ";
	int choice;
	cin >>choice;

	switch(choice)
	{
		case 1:
			overs = 2;
			break;
		case 2:
			overs = 5;
			break;
		case 3:
			overs = 1;
			break;
		case 4:
			system("clear");
			cout<<"Overs: ";
			cin>> overs;
			break;
		default:
			loading();
			display_menu();
	}
}

void toss(int &batORbowl) {
	system("clear");
	cout << "Time for the toss!" << endl
		 << "1. Heads" << endl << "2. Tails " << endl << "Option: ";

	int head_tails;
	cin >> head_tails;

	bool toss = toss_rand();  //randomly generate 1 or 0 and decide on that basis
	if(toss) {
		cout << "You won the toss!!" << endl;
		cout << endl << "Would you like to bat first or bowl first?"
			 << endl << "1. Bat" << endl << "2. Bowl" << endl << "Select an option: ";
		cin >> batORbowl;
	} else {
		cout << "Opponent won the toss." << endl;
		bool comp_decide = toss_rand();
		batORbowl = comp_decide ? 1 : 2;
	}
}

void computer_turn() {
	int player_score = 0;
	int wickets = 0, balls = 0, score = 0, total_score = 0, i = 0;

	cout << "It's your turn to bowl! 🎳\n";

	while (wickets != 10 && balls < totalBalls) {  // Limit according to overs selected
		scoreboard(i, user_team, balls, wickets, score, total_score);

		do {
			cout << "\nSelect your option (1-6): ";
			cin >> score;
		} while (score < 1 || score > 6);

		int comp_guess = rand() % 6 + 1;  // Random computer score (1-6)

		cout << "Computer selected score: " << comp_guess << endl;

		balls++;  // Increment balls every turn

		if (comp_guess == score) {  // Case for OUT
			cout << "The umpire signals \"OUT\"! ❌\n";
			comp_score[i] = player_score;
			wickets++;
			i++;  // Next player
			player_score = 0;  // Reset player score
		} else {
			player_score += comp_guess;
			total_score += comp_guess;
		}
		scoreboard(i, user_team, balls, wickets, score, total_score);

		if (target > 0 && total_score > target) {
			cout << "\nComputer wins! 🏆\n";
			return;
		}
	}

	cout << "\nEND of INNINGS!!\n";
	if (target == 0) {
		target = total_score + 1;
		cout << "TARGET is: " << target << " 🏏\n\n\n";
	} else {
		cout << "Computer's total score: " << total_score << " 🏏\n";
		if (total_score < target && target > 0) {
			user_won = true;
		} else if(total_score > target && target > 0) {
			user_won = true;
		}
	}
}

void player_turn() {
	int score, random_no;
	int total_score = 0, wickets = 0, balls = 0;

	cout << "Your batting turn! 🏏\n";

	for (int i = 0; i < 11 && wickets < 10 && balls < totalBalls; i++) {
		cout << user_team[i] << " is batting... 🏃‍♂️\n";

		while (true) {
			random_no = rand() % 6 + 1;  // Random computer guess
			do {
				cout << "Enter a score between 1 and 6: ";
				cin >> score;
			} while (score < 1 || score > 6);

			balls++;  // Increment balls

			if (score == random_no) {  // Case for OUT
				cout << "OUT! ❌\n";
				user_score[i] = total_score;
				wickets++;
				break;  // Move to the next player
			} else {
				total_score += score;
				cout << "Current score: " << total_score << " 🏏\n";
			}

			scoreboard(i, user_team, balls, wickets, score, total_score);

			if (target > 0 && total_score > target) {
				user_won = true;
				return;
			}
		}
	}

	cout << "\nEnd of INNINGS! Total score is: " << total_score << " 🏏\n";
	if (target == 0) {
		target = total_score + 1;
		cout << "Target: " << target << endl;
	} else {
		if (total_score < target) {
			user_won = false;
		} else {
			user_won = true;
		}
	}
}

void select_comp_team(string comp_team[11]) {
	int choose;
	do {
		system("clear");
		cout << "------------Select computer team------------\n";
		cout << "1. Pakistan Cricket Team\n";
		cout << "2. England Cricket Team\n";
		cout << "3. Australian Cricket Team\n";
		cout << "4. Indian Cricket Team\n";
		cout << "5. New Zealand Cricket Team\n";
		cout << "6. West Indies Cricket Team\n";
		cout << "7. Afghanistan Cricket Team\n";
		cout << "8. South African Cricket Team\n";
		cout << "9. Srilanka Cricket Team \n";
		cout << "10. Bangladesh Cricket Team \n\n";
		cout << "Select an option: ";
		cin >> choose;
		switch (choose) {
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

void select_user_team(string user_team[11]) {
	int choose;
	do {
		system("clear");
		cout << "------------Select your team------------\n";
		cout << "1. Pakistan Cricket Team\n";
		cout << "2. England Cricket Team\n";
		cout << "3. Australian Cricket Team\n";
		cout << "4. Indian Cricket Team\n";
		cout << "5. New Zealand Cricket Team\n";
		cout << "6. West Indies Cricket Team\n";
		cout << "7. Afghanistan Cricket Team\n";
		cout << "8. South African Cricket Team\n";
		cout << "9. Srilanka Cricket Team \n";
		cout << "10. Bangladesh Cricket Team \n\n";
		cout << "Select an option: ";
		cin >> choose;
		switch (choose) {
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

void scoreboard(int i, string pak_player_names[11], int balls, int wickets, int score, int totalscore) {
	// Convert balls to overs
	int overs = balls / 6;
	int remaining_balls = balls % 6;
	system("clear");

	cout << "----------------- SCOREBOARD -----------------" << endl;
	cout << "🏏 Player: " << pak_player_names[i] << endl;
	cout << "Overs: " << overs << "." << remaining_balls << endl;
	cout << "Wickets: " << wickets <<  endl;
	cout << "Current Score: " << score  << endl;
	cout << "Total Score: " << totalscore << endl;
	cout << "--------------------------------------------" << endl;
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

int toss_rand() {
	// Generate a random number (0 or 1)
	return rand() % 2;
}

void copy(string x[11], string y[11]) {
	for (int i = 0; i < 11; i++) {
		x[i] = y[i];
	}
}

void decide_winner() {
	if (user_won) {
		cout << "Congratulations! You won the game! 🏆\n";
	} else {
		cout << "Computer wins the game! 🏆\n";
	}
}

void loading(){
cout << "Loading";
for (int i = 0; i < 3; i++) {
	cout << ".";
	this_thread::sleep_for(chrono::milliseconds(500));
	
}
}