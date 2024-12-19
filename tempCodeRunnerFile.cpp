#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <thread>
#include <iomanip> // For formatting
#include <chrono>
using namespace std;

void display_menu(sf::RenderWindow &window);
void waitForKeyPress();
int toss_rand();
void select_gametype(int &overs, sf::RenderWindow &window);
void toss(int &batORbowl, sf::RenderWindow &window);
void select_user_team(string user_team[11], sf::RenderWindow &window);
void select_comp_team(string comp_team[11], sf::RenderWindow &window);
void scoreboard(int i, string pak_player_names[11], int balls, int wickets, int score, int totalscore, sf::RenderWindow &window);
void show_instructions(sf::RenderWindow &window);
void copy(string x[11], string y[11]);
void player_turn(sf::RenderWindow &window);
void computer_turn(sf::RenderWindow &window);
void decide_winner(sf::RenderWindow &window);
void loading(sf::RenderWindow &window);

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

    sf::RenderWindow window(sf::VideoMode(800, 600), "Hand Cricket 2024");

    while (window.isOpen()) {
        display_menu(window);
        waitForKeyPress();
    }

    return 0;
}

void display_menu(sf::RenderWindow &window) {
    window.clear();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font\n";
    }

    sf::Text title("HAND CRICKET 2024", font, 50);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(150, 50);

    sf::Text play("1. PLAY 🏏", font, 30);
    play.setFillColor(sf::Color::White);
    play.setPosition(300, 150);

    sf::Text instructions("2. INSTRUCTIONS 📜", font, 30);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(300, 200);

    sf::Text exit("3. EXIT ❌", font, 30);
    exit.setFillColor(sf::Color::White);
    exit.setPosition(300, 250);

    window.draw(title);
    window.draw(play);
    window.draw(instructions);
    window.draw(exit);
    window.display();

    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Num1) {
                select_gametype(overs, window);
                totalBalls = overs * 6;
                select_user_team(user_team, window);
                select_comp_team(comp_team, window);
                toss(batORbowl, window);
                if (batORbowl == 1) { 
                    player_turn(window); 
                    computer_turn(window); 
                } else if(batORbowl == 2){ 
                    computer_turn(window); 
                    player_turn(window); 
                }
                decide_winner(window);
            } else if (event.key.code == sf::Keyboard::Num2) {
                show_instructions(window);
            } else if (event.key.code == sf::Keyboard::Num3) {
                window.close();
            }
        }
    }
}

void select_gametype(int &overs, sf::RenderWindow &window) {
    window.clear();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font\n";
    }

    sf::Text title("Select Game Mode", font, 40);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(150, 50);

    sf::Text blitz("1. Blitz (quick 2 over match)", font, 30);
    blitz.setFillColor(sf::Color::White);
    blitz.setPosition(150, 150);

    sf::Text t5("2. T 5 (5 overs)", font, 30);
    t5.setFillColor(sf::Color::White);
    t5.setPosition(150, 200);

    sf::Text superOver("3. Super Over", font, 30);
    superOver.setFillColor(sf::Color::White);
    superOver.setPosition(150, 250);

    sf::Text custom("4. Custom", font, 30);
    custom.setFillColor(sf::Color::White);
    custom.setPosition(150, 300);

    sf::Text back("5. Go Back to Main Menu", font, 30);
    back.setFillColor(sf::Color::White);
    back.setPosition(150, 350);

    window.draw(title);
    window.draw(blitz);
    window.draw(t5);
    window.draw(superOver);
    window.draw(custom);
    window.draw(back);
    window.display();

    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Num1) {
                overs = 2;
                return;
            } else if (event.key.code == sf::Keyboard::Num2) {
                overs = 5;
                return;
            } else if (event.key.code == sf::Keyboard::Num3) {
                overs = 1;
                return;
            } else if (event.key.code == sf::Keyboard::Num4) {
                window.clear();
                sf::Text customOvers("Overs: ", font, 30);
                customOvers.setFillColor(sf::Color::White);
                customOvers.setPosition(150, 150);
                window.draw(customOvers);
                window.display();
                cin >> overs;
                return;
            } else if (event.key.code == sf::Keyboard::Num5) {
                display_menu(window);
                return;
            }
        }
    }
}

void toss(int &batORbowl, sf::RenderWindow &window) {
    window.clear();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font\n";
    }

    sf::Text title("Time for the toss!", font, 40);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(150, 50);

    sf::Text heads("1. Heads", font, 30);
    heads.setFillColor(sf::Color::White);
    heads.setPosition(150, 150);

    sf::Text tails("2. Tails", font, 30);
    tails.setFillColor(sf::Color::White);
    tails.setPosition(150, 200);

    window.draw(title);
    window.draw(heads);
    window.draw(tails);
    window.display();

    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            int head_tails;
            if (event.key.code == sf::Keyboard::Num1) {
                head_tails = 1;
            } else if (event.key.code == sf::Keyboard::Num2) {
                head_tails = 2;
            }

            bool toss = toss_rand();  //randomly generate 1 or 0 and decide on that basis
            if(toss) {
                sf::Text won("You won the toss!!", font, 30);
                won.setFillColor(sf::Color::Green);
                won.setPosition(150, 250);
                window.draw(won);
                window.display();
                sf::sleep(sf::seconds(2));

                window.clear();
                sf::Text bat("1. Bat", font, 30);
                bat.setFillColor(sf::Color::White);
                bat.setPosition(150, 150);

                sf::Text bowl("2. Bowl", font, 30);
                bowl.setFillColor(sf::Color::White);
                bowl.setPosition(150, 200);

                window.draw(bat);
                window.draw(bowl);
                window.display();

                while (window.waitEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    } else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Num1) {
                            batORbowl = 1;
                            return;
                        } else if (event.key.code == sf::Keyboard::Num2) {
                            batORbowl = 2;
                            return;
                        }
                    }
                }
            } else {
                sf::Text lost("Opponent won the toss.", font, 30);
                lost.setFillColor(sf::Color::Red);
                lost.setPosition(150, 250);
                window.draw(lost);
                window.display();
                sf::sleep(sf::seconds(2));

                bool comp_decide = toss_rand();
                batORbowl = comp_decide ? 1 : 2;
                return;
            }
        }
    }
}

void computer_turn(sf::RenderWindow &window) {
    int player_score = 0;
    int wickets = 0, balls = 0, score = 0, total_score = 0, i = 0;

    window.clear();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font\n";
    }

    sf::Text title("It's your turn to bowl! 🎳", font, 30);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(150, 50);
    window.draw(title);
    window.display();
    sf::sleep(sf::seconds(2));

    while (wickets != 10 && balls < totalBalls) {  // Limit according to overs selected
        scoreboard(i, user_team, balls, wickets, score, total_score, window);

        sf::Text option("Select your option (1-6): ", font, 30);
        option.setFillColor(sf::Color::White);
        option.setPosition(150, 150);
        window.draw(option);
        window.display();

        sf::Event event;
        while (window.waitEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num6) {
                    score = event.key.code - sf::Keyboard::Num0;
                    break;
                }
            }
        }

        int comp_guess = rand() % 6 + 1;  // Random computer score (1-6)

        sf::Text compScore("Computer selected score: " + to_string(comp_guess), font, 30);
        compScore.setFillColor(sf::Color::White);
        compScore.setPosition(150, 200);
        window.draw(compScore);
        window.display();
        sf::sleep(sf::seconds(2));

        balls++;  // Increment balls every turn

        if (comp_guess == score) {  // Case for OUT
            sf::Text out("The umpire signals \"OUT\"! ❌", font, 30);
            out.setFillColor(sf::Color::Red);
            out.setPosition(150, 250);
            window.draw(out);
            window.display();
            sf::sleep(sf::seconds(2));

            comp_score[i] = player_score;
            wickets++;
            i++;  // Next player
            player_score = 0;  // Reset player score
        } else {
            player_score += comp_guess;
            total_score += comp_guess;
        }
        scoreboard(i, user_team, balls, wickets, score, total_score, window);

        if (target > 0 && total_score > target) {
            sf::Text win("Computer wins! 🏆", font, 30);
            win.setFillColor(sf::Color::Green);
            win.setPosition(150, 300);
            window.draw(win);
            window.display();
            sf::sleep(sf::seconds(2));
            return;
        }
    }

    sf::Text end("END of INNINGS!!", font, 30);
    end.setFillColor(sf::Color::Yellow);
    end.setPosition(150, 350);
    window.draw(end);
    window.display();
    sf::sleep(sf::seconds(2));

    if (target == 0) {
        target = total_score + 1;
        sf::Text targetText("TARGET is: " + to_string(target) + " 🏏", font, 30);
        targetText.setFillColor(sf::Color::White);
        targetText.setPosition(150, 400);
        window.draw(targetText);
        window.display();
        sf::sleep(sf::seconds(2));
    } else {
        sf::Text compScore("Computer's total score: " + to_string(total_score) + " 🏏", font, 30);
        compScore.setFillColor(sf::Color::White);
        compScore.setPosition(150, 400);
        window.draw(compScore);
        window.display();
        sf::sleep(sf::seconds(2));

        if (total_score < target && target > 0) {
            user_won = true;
        } else if(total_score > target && target > 0) {
            user_won = true;
        }
    }
}

void player_turn(sf::RenderWindow &window) {
    int score, random_no;
    int total_score = 0, wickets = 0, balls = 0;

    window.clear();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font\n";
    }

    sf::Text title("Your batting turn! 🏏", font, 30);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(150, 50);
    window.draw(title);
    window.display();
    sf::sleep(sf::seconds(2));

    for (int i = 0; i < 11 && wickets < 10 && balls < totalBalls; i++) {
        sf::Text player(user_team[i] + " is batting... 🏃‍♂️", font, 30);
        player.setFillColor(sf::Color::White);
        player.setPosition(150, 150);
        window.draw(player);
        window.display();
        sf::sleep(sf::seconds(2));

               while (true) {
            random_no = rand() % 6 + 1;  // Random computer guess

            sf::Text prompt("Enter a score between 1 and 6: ", font, 30);
            prompt.setFillColor(sf::Color::White);
            prompt.setPosition(150, 250);
            window.draw(prompt);
            window.display();

            cin >> score;
            while (score < 1 || score > 6) {
                sf::Text error("Invalid input! Enter a score between 1 and 6: ", font, 30);
                error.setFillColor(sf::Color::Red);
                error.setPosition(150, 300);
                window.draw(error);
                window.display();
                cin >> score;
            }

            balls++;  // Increment balls

            if (score == random_no) {  // Case for OUT
                sf::Text out("OUT! ❌", font, 30);
                out.setFillColor(sf::Color::Red);
                out.setPosition(150, 350);
                window.draw(out);
                window.display();
                sf::sleep(sf::seconds(2));
                user_score[i] = total_score;
                wickets++;
                break;  // Move to the next player
            } else {
                total_score += score;
                sf::Text current_score("Current score: " + to_string(total_score) + " 🏏", font, 30);
                current_score.setFillColor(sf::Color::White);
                current_score.setPosition(150, 350);
                window.draw(current_score);
                window.display();
                sf::sleep(sf::seconds(2));
            }

            // Display scoreboard
            window.clear();
            scoreboard(i, user_team, balls, wickets, score, total_score, window);
            window.display();

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
void select_user_team(string user_team[11], sf::RenderWindow &window) {
    window.clear();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font\n";
    }

    sf::Text title("Select your team", font, 40);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(150, 50);

    sf::Text pak("1. Pakistan Cricket Team", font, 30);
    pak.setFillColor(sf::Color::White);
    pak.setPosition(150, 150);

    sf::Text eng("2. England Cricket Team", font, 30);
    eng.setFillColor(sf::Color::White);
    eng.setPosition(150, 200);

    sf::Text aus("3. Australian Cricket Team", font, 30);
    aus.setFillColor(sf::Color::White);
    aus.setPosition(150, 250);

    sf::Text ind("4. Indian Cricket Team", font, 30);
    ind.setFillColor(sf::Color::White);
    ind.setPosition(150, 300);

    sf::Text nz("5. New Zealand Cricket Team", font, 30);
    nz.setFillColor(sf::Color::White);
    nz.setPosition(150, 350);

    sf::Text wi("6. West Indies Cricket Team", font, 30);
    wi.setFillColor(sf::Color::White);
    wi.setPosition(150, 400);

    sf::Text afg("7. Afghanistan Cricket Team", font, 30);
    afg.setFillColor(sf::Color::White);
    afg.setPosition(150, 450);

    sf::Text sa("8. South African Cricket Team", font, 30);
    sa.setFillColor(sf::Color::White);
    sa.setPosition(150, 500);

    sf::Text sri("9. Sri Lanka Cricket Team", font, 30);
    sri.setFillColor(sf::Color::White);
    sri.setPosition(150, 550);

    sf::Text ban("10. Bangladesh Cricket Team", font, 30);
    ban.setFillColor(sf::Color::White);
    ban.setPosition(150, 600);

    window.draw(title);
    window.draw(pak);
    window.draw(eng);
    window.draw(aus);
    window.draw(ind);
    window.draw(nz);
    window.draw(wi);
    window.draw(afg);
    window.draw(sa);
    window.draw(sri);
    window.draw(ban);
    window.display();

    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            int choose;
            if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num0 + 10) {
                choose = event.key.code - sf::Keyboard::Num0;
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
                return;
            }
        }
    }
}

void select_comp_team(string comp_team[11], sf::RenderWindow &window) {
    window.clear();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font\n";
    }

    sf::Text title("Select computer team", font, 40);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(150, 50);

    sf::Text pak("1. Pakistan Cricket Team", font, 30);
    pak.setFillColor(sf::Color::White);
    pak.setPosition(150, 150);

    sf::Text eng("2. England Cricket Team", font, 30);
    eng.setFillColor(sf::Color::White);
    eng.setPosition(150, 200);

    sf::Text aus("3. Australian Cricket Team", font, 30);
    aus.setFillColor(sf::Color::White);
    aus.setPosition(150, 250);

    sf::Text ind("4. Indian Cricket Team", font, 30);
    ind.setFillColor(sf::Color::White);
    ind.setPosition(150, 300);

    sf::Text nz("5. New Zealand Cricket Team", font, 30);
    nz.setFillColor(sf::Color::White);
    nz.setPosition(150, 350);

    sf::Text wi("6. West Indies Cricket Team", font, 30);
    wi.setFillColor(sf::Color::White);
    wi.setPosition(150, 400);

    sf::Text afg("7. Afghanistan Cricket Team", font, 30);
    afg.setFillColor(sf::Color::White);
    afg.setPosition(150, 450);

    sf::Text sa("8. South African Cricket Team", font, 30);
    sa.setFillColor(sf::Color::White);
    sa.setPosition(150, 500);

    sf::Text sri("9. Sri Lanka Cricket Team", font, 30);
    sri.setFillColor(sf::Color::White);
    sri.setPosition(150, 550);

    sf::Text ban("10. Bangladesh Cricket Team", font, 30);
    ban.setFillColor(sf::Color::White);
    ban.setPosition(150, 600);

    window.draw(title);
    window.draw(pak);
    window.draw(eng);
    window.draw(aus);
    window.draw(ind);
    window.draw(nz);
    window.draw(wi);
    window.draw(afg);
    window.draw(sa);
    window.draw(sri);
    window.draw(ban);
    window.display();

    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            int choose;
            if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num0 + 10) {
                choose = event.key.code - sf::Keyboard::Num0;
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
                return;
            }
        }
    }
}

void scoreboard(int i, string pak_player_names[11], int balls, int wickets, int score, int totalscore, sf::RenderWindow &window) {
    // Convert balls to overs
    int overs = balls / 6;
    int remaining_balls = balls % 6;
    window.clear();

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font\n";
    }

    sf::Text title("SCOREBOARD", font, 40);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(150, 50);

    sf::Text player("Player: " + pak_player_names[i], font, 30);
    player.setFillColor(sf::Color::White);
    player.setPosition(150, 150);

    sf::Text oversText("Overs: " + to_string(overs) + "." + to_string(remaining_balls), font, 30);
    oversText.setFillColor(sf::Color::White);
    oversText.setPosition(150, 200);

    sf::Text wicketsText("Wickets: " + to_string(wickets), font, 30);
    wicketsText.setFillColor(sf::Color::White);
    wicketsText.setPosition(150, 250);

    sf::Text currentScore("Current Score: " + to_string(score), font, 30);
    currentScore.setFillColor(sf::Color::White);
    currentScore.setPosition(150, 300);

    sf::Text totalScore("Total Score: " + to_string(totalscore), font, 30);
    totalScore.setFillColor(sf::Color::White);
    totalScore.setPosition(150, 350);

    window.draw(title);
    window.draw(player);
    window.draw(oversText);
    window.draw(wicketsText);
    window.draw(currentScore);
    window.draw(totalScore);
    window.display();
}

void waitForKeyPress() {
    cout << "Press any key to continue...\n";
    system("read -n1"); // Waits for any key press
}

void show_instructions(sf::RenderWindow &window) {
    window.clear();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font\n";
    }

    sf::Text title("INSTRUCTIONS", font, 40);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(150, 50);

    sf::Text line1("1. This is a hand cricket game where you select scores (1-6).", font, 30);
    line1.setFillColor(sf::Color::White);
    line1.setPosition(150, 150);

    sf::Text line2("2. If your score matches the opponent's guess, the player is OUT.", font, 30);
    line2.setFillColor(sf::Color::White);
    line2.setPosition(150, 200);

    sf::Text line3("3. You and the computer take turns batting and bowling.", font, 30);
    line3.setFillColor(sf::Color::White);
    line3.setPosition(150, 250);

    sf::Text line4("4. The team with the highest score wins.", font, 30);
    line4.setFillColor(sf::Color::White);
    line4.setPosition(150, 300);

    window.draw(title);
    window.draw(line1);
    window.draw(line2);
    window.draw(line3);
    window.draw(line4);
    window.display();

    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            display_menu(window);
            return;
        }
    }
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

void decide_winner(sf::RenderWindow &window) {
    window.clear();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font\n";
    }

    sf::Text title("GAME RESULT", font, 40);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(150, 50);

    sf::Text result("", font, 30);
    result.setFillColor(sf::Color::White);
    result.setPosition(150, 150);

    if (user_won) {
        result.setString("Congratulations! You won the game! 🏆");
    } else {
        result.setString("Computer wins the game! 🏆");
    }

    window.draw(title);
    window.draw(result);
    window.display();

    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            display_menu(window);
            return;
        }
    }
}

void loading(sf::RenderWindow &window) {
    window.clear();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font\n";
    }

    sf::Text loading("Loading", font, 30);
    loading.setFillColor(sf::Color::White);
    loading.setPosition(150, 150);
    window.draw(loading);
    window.display();

    for (int i = 0; i < 3; i++) {
        sf::Text dot(".", font, 30);
        dot.setFillColor(sf::Color::White);
        dot.setPosition(150 + (i * 10), 150);
        window.draw(dot);
        window.display();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}