#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <thread>
#include <iomanip> // For formatting
#include <chrono>
using namespace std;

enum difficulty_level { easy, normal, hard };

difficulty_level current_difficulty_level;
void difficulty();
void display_menu();
void waitForKeyPress();
int toss_rand();
void select_gametype(int& overs);
void toss(int& batORbowl);
void select_user_team(string user_team[11]);
void select_comp_team(string comp_team[11]);
void scoreboard(int i, string pak_player_names[11], int balls, int wickets, int score, int totalscore);
void instructions();
void copy(string x[11], string y[11]);
void player_turn();
void computer_turn();
void decide_winner();
void loading();

string pak_player_names[11] = { "Babar Azam", "Mohammad Rizwan", "Fakhar Zaman", "Iftikhar Ahmed", "Shadab Khan", "Imad Wasim", "Shaheen Afridi", "Haris Rauf", "Naseem Shah", "Mohammad Nawaz", "Usama Mir" };
string eng_player_names[11] = { "Jos Buttler", "Dawid Malan", "Alex Hales", "Moeen Ali", "Liam Livingstone", "Ben Stokes", "Sam Curran", "Chris Woakes", "Adil Rashid", "Mark Wood", "Chris Jordan" };
string aus_player_names[11] = { "Aaron Finch", "David Warner", "Steve Smith", "Glenn Maxwell", "Marcus Stoinis", "Mitchell Marsh", "Pat Cummins", "Mitchell Starc", "Adam Zampa", "Josh Hazlewood", "Matthew Wade" };
string ind_player_names[11] = { "Rohit Sharma", "Virat Kohli", "KL Rahul", "Suryakumar Yadav", "Rishabh Pant", "Hardik Pandya", "Ravindra Jadeja", "Jasprit Bumrah", "Bhuvneshwar Kumar", "Yuzvendra Chahal", "Mohammed Shami" };
string nz_player_names[11] = { "Kane Williamson", "Martin Guptill", "Devon Conway", "Glenn Phillips", "James Neesham", "Mitchell Santner", "Tim Southee", "Trent Boult", "Lockie Ferguson", "Ish Sodhi", "Tom Latham" };
string wi_player_names[11] = { "Kieron Pollard", "Chris Gayle", "Nicholas Pooran", "Shimron Hetmyer", "Andre Russell", "Jason Holder", "Dwayne Bravo", "Sunil Narine", "Sheldon Cottrell", "Oshane Thomas", "Evin Lewis" };
string afg_player_names[11] = { "Mohammad Nabi", "Rashid Khan", "Mujeeb Ur Rahman", "Hazratullah Zazai", "Rahmanullah Gurbaz", "Najibullah Zadran", "Gulbadin Naib", "Asghar Afghan", "Hamid Hassan", "Karim Janat", "Naveen-ul-Haq" };
string sa_player_names[11] = { "Quinton de Kock", "Temba Bavuma", "Aiden Markram", "Rassie van der Dussen", "David Miller", "Dwaine Pretorius", "Kagiso Rabada", "Anrich Nortje", "Tabraiz Shamsi", "Lungi Ngidi", "Heinrich Klaasen" };
string sri_player_names[11] = { "Kusal Perera", "Danushka Gunathilaka", "Avishka Fernando", "Dhananjaya de Silva", "Dasun Shanaka", "Wanindu Hasaranga", "Dushmantha Chameera", "Lahiru Kumara", "Nuwan Pradeep", "Kusal Mendis", "Isuru Udana" };
string ban_player_names[11] = { "Tamim Iqbal", "Shakib Al Hasan", "Mushfiqur Rahim", "Mahmudullah", "Soumya Sarkar", "Liton Das", "Mustafizur Rahman", "Taskin Ahmed", "Mehidy Hasan", "Mohammad Saifuddin", "Afif Hossain" };

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
	cout << "\n";
	system("clear"); // Clear the console for a clean display

	// Top border
	cout << "\033[1;32m============================================================\033[0m\n";

	// Title with background color and bold yellow text
	cout << "\033[1;7;33m                  🏏 HAND CRICKET 2024 🏏                  \033[0m\n";

	// Divider line
	cout << "\033[1;32m============================================================\033[0m\n";

	// Subheading with a fun tagline
	cout << "\033[1;36m             🎉 READY TO SMASH THE FIELD? 🎉              \033[0m\n";
	cout << "\033[1;32m============================================================\033[0m\n";

	// Menu options with emojis and color
	cout << "\033[1;36m  1. \033[1;33mPLAY \033[0m\033[1;37m🏏 (Start your cricket adventure!)\033[0m\n";
	cout << "\033[1;36m  2. \033[1;33mINSTRUCTIONS \033[0m\033[1;37m📜 (Learn how to play!)\033[0m\n";
	cout << "\033[1;36m  3. \033[1;33mEXIT \033[0m\033[1;37m❌ (Leave the game)\033[0m\n";

	// Bottom border
	cout << "\033[1;32m============================================================\033[0m\n";

	// Prompt to choose an option
	cout << "\033[1;37mChoose an option to begin: \033[0m";


	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		select_gametype(overs);
		difficulty();
		totalBalls = overs * 6;
		select_user_team(user_team);
		select_comp_team(comp_team);
		toss(batORbowl);
		if (batORbowl == 1) {
			player_turn();
			loading();
			computer_turn();
		}
		else if (batORbowl == 2) {
			computer_turn();
			loading();
			player_turn();
		}
		decide_winner();
		break;
	case 2:
		instructions();
		break;
	case 3:
		cout << "Exiting... Goodbye! \n";
		exit(0); // Exit the program
	default:
		cout << "Invalid choice! Please select a valid option. \n";
	}

	// Ask to display the menu again or exit
	char endChoice;
	cout << "Do you want to display the menu again? (y/n): ";
	cin >> endChoice;
	if (endChoice == 'n' || endChoice == 'N') {
		// Exiting message with a warm color tone
		cout << "\033[1;33mExiting... \033[1;31mGoodbye! \033[0m\n";

		exit(0); // Exit the program
	}
}

void select_gametype(int& overs)
{
	system("clear"); // Clear the screen

	// Title with bold and colorful border
	cout << "\033[1;32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n";
	cout << "\033[1;33m               SELECT GAME MODE               \033[0m\n";
	cout << "\033[1;32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n\n";

	// Game mode options with emojis and colors
	cout << "\033[1;36m  1. \033[1;33mBlitz \033[1;37m- \033[1;34mQuick 2 over match\033[0m\n";
	cout << "\033[1;36m  2. \033[1;33mT 5 \033[1;37m- \033[1;34m5 overs\033[0m\n";
	cout << "\033[1;36m  3. \033[1;33mSuper Over \033[1;37m- \033[1;34mOne over each\033[0m\n";
	cout << "\033[1;36m  4. \033[1;33mCustom \033[1;37m- \033[1;34mCreate your own match!\033[0m\n";
	cout << "\033[1;36m  5. \033[1;33mGo Back to Main Menu \033[0m\n\n";

	// Bottom border
	cout << "\033[1;32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n";

	// Prompt for selection
	cout << "\033[1;37mSelect your choice: \033[0m";




	int choice;
	cin >> choice;

	switch (choice)
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
		cout << "Overs: ";
		cin >> overs;
		break;
	default:
		loading();
		display_menu();
	}
}

void toss(int& batORbowl) {
	system("clear");
	// Time for the toss with colorful and neat design
	cout << "\033[1;34m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n";
	cout << "\033[1;33m           ⚡ Time for the toss! ⚡           \033[0m\n";
	cout << "\033[1;34m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n\n";

	// Toss options with attractive colors
	cout << "\033[1;36m 1. \033[1;32mHeads\033[0m\n";
	cout << "\033[1;36m 2. \033[1;32mTails\033[0m\n";

	// Prompt with a fun design
	cout << "\033[1;37mOption: \033[1;34m________\033[0m\n";


	int head_tails;
	cin >> head_tails;

	bool toss = toss_rand();  //randomly generate 1 or 0 and decide on that basis
	if (toss) {
		// Winning the toss message with colorful and neat design
		cout << "\033[1;32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n";
		cout << "\033[1;33m            🎉 You won the toss!! 🎉           \033[0m\n";
		cout << "\033[1;32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n\n";

		// Question with colorful options
		do{
		cout << "\033[1;36mWould you like to bat first or bowl first?\033[0m\n\n";
		cout << "\033[1;34m 1. \033[1;32mBat\033[0m\n";
		cout << "\033[1;34m 2. \033[1;32mBowl\033[0m\n";

		// Prompt for selection with a neat line
		cout << "\033[1;37mSelect an option: \033[1;34m________\033[0m\n";

		cin >> batORbowl;}while(batORbowl!= 1 || 2);
	}
	else {
		// Opponent winning the toss with a dramatic and colorful design
		cout << "\033[1;31mOh no! \033[1;37mOpponent won the toss... \033[1;33mBetter luck next time! \033[0m\n";
		loading();
		bool comp_decide = toss_rand();
		batORbowl = comp_decide ? 1 : 2;
	}
}

void computer_turn() {
    int player_score = 0;
    int wickets = 0, balls = 0, score = 0, total_score = 0, i = 0;
    int random_chance;
    int probability = 0;

    switch (current_difficulty_level) { // using a switch to update probability factor based on difficulty level chosen by user
    case easy:
        probability = 7; break;
    case normal:
        probability = 5; break;
    case hard:
        probability = 3; break;
    }
    cout << "\033[1;32mIt's your turn to bowl! \033[0m\n";
	loading();

    while (wickets != 10 && balls < totalBalls) {  // Limit according to overs selected
        scoreboard(i, user_team, balls, wickets, score, total_score);

        do {
            cout << "\033[1;34m\nSelect your option (1-6): \033[0m";
            cin >> score;
        } while (score < 1 || score > 6);

        int comp_guess = rand() % 6 + 1;  // Random computer score (1-6)

        cout << "Computer selected score: " << comp_guess << endl;

        balls++;  // Increment balls every turn

        random_chance = rand() % 10 + 1;// generates random number to compare with probability factor

        if (comp_guess == score && random_chance <= probability) {  // Case for OUT
            cout << "\033[1;31mThe umpire signals \033[1;37m\"OUT\" \033[0m\033[1;31m! \033[0m\n";
            comp_score[i] = player_score;
            wickets++;
            i++;  // Next player
            player_score = 0;  // Reset player score
        }
        else {
            player_score += comp_guess;
            total_score += comp_guess;
        }
        scoreboard(i, user_team, balls, wickets, score, total_score);

        if (target > 0 && total_score > target) {
            cout << "\nComputer wins! \n";
            return;
        }
    }

    cout << "\033[1;31m\nEND of INNINGS!! \033[0m\n";
    if (target == 0) {
        target = total_score + 1;
        cout << "TARGET is: " << target << " \n\n\n";
    }
    else {
        cout << "Computer's total score: " << total_score << " \n";
        if (total_score < target && target > 0) {
            user_won = true;
        }
        else if (total_score > target && target > 0) {
            user_won = true;
        }
    }
}

void player_turn() {
    int score, random_no, random_chance;
    int total_score = 0, wickets = 0, balls = 0;
    int probability = 0;

    switch (current_difficulty_level) { // using a switch to update probability factor based on difficulty level chosen by user
    case easy:
        probability = 3; break;
    case normal:
        probability = 5; break;
    case hard:
        probability = 7; break;
    }
    cout << "\033[1;34mIts your turn to BAT! \033[0m\n";
	loading();

    for (int i = 0; i < 11 && wickets < 10 && balls < totalBalls; i++) {
        cout << "\033[1;34m" << user_team[i] << "\033[0m \033[1;32mis batting... \033[0m\n";

        while (true) {
            random_no = rand() % 6 + 1;  // Random computer guess
            random_chance = rand() % 10 + 1; // random chance between 1-10 for comparing with probability factor
            do {
                cout << "Enter a score between 1 and 6: ";
                cin >> score;
            } while (score < 1 || score > 6);

            balls++;  // Increment balls

            if (score == random_no && random_chance <= probability) {  // Case for OUT
                cout << "OUT! \n";
                user_score[i] = total_score;
                wickets++;
                break;  // Move to the next player
            }
            else {
                total_score += score;
                cout << "Current score: " << total_score << " \n";
            }

            scoreboard(i, user_team, balls, wickets, score, total_score);

            if (target > 0 && total_score > target) {
                user_won = true;
                return;
            }
        }
    }

    cout << "\033[1;31m\nEnd of INNINGS! \033[1;33mTotal score is: \033[1;32m" << total_score << " \033[0m\n";
    if (target == 0) {
        target = total_score + 1;
        cout << "Target: " << target << endl;
    }
    else {
        if (total_score < target) {
            user_won = false;
        }
        else {
            user_won = true;
        }
    }
}

void select_comp_team(string comp_team[11]) {
	int choose;
	do {
		system("clear");
		// Title with bold and colorful border
		cout << "\033[1;32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n";
		cout << "\033[1;33m        ------------Select Computer Team------------        \033[0m\n";
		cout << "\033[1;32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n\n";

		// Table header
		cout << "\033[1;36m  +----+------------------------------------------+\033[0m\n";
		cout << "\033[1;36m  | No |              Team Name                 |\033[0m\n";
		cout << "\033[1;36m  +----+------------------------------------------+\033[0m\n";

		// Table rows with team names
		cout << "\033[1;36m  | 1  | Pakistan Cricket Team                 |\033[0m\n";
		cout << "\033[1;36m  | 2  | England Cricket Team                  |\033[0m\n";
		cout << "\033[1;36m  | 3  | Australian Cricket Team               |\033[0m\n";
		cout << "\033[1;36m  | 4  | Indian Cricket Team                   |\033[0m\n";
		cout << "\033[1;36m  | 5  | New Zealand Cricket Team              |\033[0m\n";
		cout << "\033[1;36m  | 6  | West Indies Cricket Team              |\033[0m\n";
		cout << "\033[1;36m  | 7  | Afghanistan Cricket Team              |\033[0m\n";
		cout << "\033[1;36m  | 8  | South African Cricket Team            |\033[0m\n";
		cout << "\033[1;36m  | 9  | Sri Lanka Cricket Team                |\033[0m\n";
		cout << "\033[1;36m  | 10 | Bangladesh Cricket Team               |\033[0m\n";

		// Bottom border
		cout << "\033[1;36m  +----+------------------------------------------+\033[0m\n";

		// Prompt for selection
		cout << "\033[1;37mSelect an option: \033[1;34m____\033[0m\n";



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
		// Title with bold and colorful border
		cout << "\033[1;32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n";
		cout << "\033[1;33m        ------------Select your Team------------        \033[0m\n";
		cout << "\033[1;32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n\n";

		// Table header
		cout << "\033[1;36m  +----+------------------------------------------+\033[0m\n";
		cout << "\033[1;36m  | No |              Team Name                 |\033[0m\n";
		cout << "\033[1;36m  +----+------------------------------------------+\033[0m\n";

		// Table rows with team names
		cout << "\033[1;36m  | 1  | Pakistan Cricket Team                 |\033[0m\n";
		cout << "\033[1;36m  | 2  | England Cricket Team                  |\033[0m\n";
		cout << "\033[1;36m  | 3  | Australian Cricket Team               |\033[0m\n";
		cout << "\033[1;36m  | 4  | Indian Cricket Team                   |\033[0m\n";
		cout << "\033[1;36m  | 5  | New Zealand Cricket Team              |\033[0m\n";
		cout << "\033[1;36m  | 6  | West Indies Cricket Team              |\033[0m\n";
		cout << "\033[1;36m  | 7  | Afghanistan Cricket Team              |\033[0m\n";
		cout << "\033[1;36m  | 8  | South African Cricket Team            |\033[0m\n";
		cout << "\033[1;36m  | 9  | Sri Lanka Cricket Team                |\033[0m\n";
		cout << "\033[1;36m  | 10 | Bangladesh Cricket Team               |\033[0m\n";

		// Bottom border
		cout << "\033[1;36m  +----+------------------------------------------+\033[0m\n";

		// Prompt for selection
		cout << "\033[1;37mSelect an option: \033[1;34m____\033[0m\n";

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

	cout << "\033[1;36m| \033[1;37m" << setw(15) << left << "Player"
		<< "\033[1;36m | \033[1;33m" << setw(35) << left << pak_player_names[i] << "\033[1;36m |\033[0m\n";
	cout << "\033[1;32m------------------------------------------------------------\033[0m\n";

	// Overs row
	cout << "\033[1;36m| \033[1;37m" << setw(15) << left << "Overs"
		<< "\033[1;36m | \033[1;33m" << setw(35) << left << overs << "." << remaining_balls << "\033[1;36m |\033[0m\n";
	cout << "\033[1;32m------------------------------------------------------------\033[0m\n";

	// Wickets row
	cout << "\033[1;36m| \033[1;37m" << setw(15) << left << "Wickets"
		<< "\033[1;36m | \033[1;33m" << setw(35) << left << wickets << "\033[1;36m |\033[0m\n";
	cout << "\033[1;32m------------------------------------------------------------\033[0m\n";

	// Current Score row
	cout << "\033[1;36m| \033[1;37m" << setw(15) << left << "Current Score"
		<< "\033[1;36m | \033[1;33m" << setw(35) << left << score << "\033[1;36m |\033[0m\n";
	cout << "\033[1;32m------------------------------------------------------------\033[0m\n";

	// Total Score row
	cout << "\033[1;36m| \033[1;37m" << setw(15) << left << "Total Score"
		<< "\033[1;36m | \033[1;33m" << setw(35) << left << totalscore << "\033[1;36m |\033[0m\n";
	cout << "\033[1;32m============================================================\033[0m\n";
}


void waitForKeyPress() {
	cout << "Press any key to continue...\n";
	system("read -n1"); // Waits for any key press
}

void instructions() {
	// Title with a blue border
	cout << "\033[1;34m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n";
	cout << "\033[1;34m                  INSTRUCTIONS                        \033[0m\n";
	cout << "\033[1;34m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n\n";

	// Instructions in blue with a neat design
	cout << "\033[1;36m1. \033[1;34mThis is a hand cricket game where you select scores (1-6).\033[0m\n";
	cout << "\033[1;36m2. \033[1;34mIf your score matches the opponent's guess, the player is OUT.\033[0m\n";
	cout << "\033[1;36m3. \033[1;34mYou and the computer take turns batting and bowling.\033[0m\n";
	cout << "\033[1;36m4. \033[1;34mThe team with the highest score wins.\033[0m\n";

	// Bottom border in blue
	cout << "\033[1;34m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n";

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
		cout << "Congratulations! You won the game! \n";
	}
	else {
		cout << "Computer wins the game! \n";
	}
}

void loading() {
	cout << "Loading";
	for (int i = 0; i < 3; i++) {
		cout << ".";
		this_thread::sleep_for(chrono::milliseconds(500));

	}
}

// function for difficulty level
void difficulty(){
	system("clear");
	int option;
	cout << "-----Difficulty levels-----\n";
	cout << "1.Easy\n2.Normal\n3.Hard\n";
	cout << "Select option from 1-3\n";
	cin >> option;
	switch (option){
	case 1:
		current_difficulty_level = easy;
		cout << "You selected difficulty level: Easy\n";
		break;
	case 2:
		current_difficulty_level = normal;
		cout << "You selected difficulty level: Normal\n";
		break;
	case 3:
		current_difficulty_level = hard;
		cout << "You selected difficulty level: Hard\n";
		break;
	default:
		cout << "Invalid input. Setting difficulty level as easy\n";
		current_difficulty_level = easy;
		break;
	}
}