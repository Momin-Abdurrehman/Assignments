#include <iostream>
#include <iomanip> //for setw()
#include <cmath>   //for exponential and log functions               //included all necessary header files
#include <cstdlib> /*  these two for randum number  */
#include <ctime>

// Declaration/function prototype for all the functions
void pattern();
void calculator();
int randnum();
void game();
void pattern2();

using namespace std;

int main()
{
    char choice; // for switching between different tasks
    do
    {
        // Display menu
        cout << "\nMain Menu:\n";
        cout << "1 - Display Pattern\n";
        cout << "2 - Calculator\n";
        cout << "3 - Guessing Game\n";
        cout << "4 - Pattern(using while loop)\n";
        cout << "x - Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) // switch for different tasks
        {
        case '1':
            pattern();
            break;
        case '2':
            calculator();
            break;
        case '3':
            game();
            break;
        case '4':
            pattern2();
            break;
        case 'x':
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    } while (choice != 'x'); // Loop until user chooses to exit by pressing x

    return 0;
}

// DEFINITION OF TASK 1 i.e pattern
void pattern()
{

    int n;
    cout << "Enter the number of rows: "; // taking input from user
    cin >> n;
    cout << endl;
    int counter = 0;

    for (int i = 1; i <= n; i++) // outer loop
    {
        for (int j = n; j > i; j--)
        {
            cout << setw(3) << " "; // printing intital spaces
        }
        for (int j = 1; j <= i; j++)
        {
            cout << setw(3) << j + counter; // printing left side of triangle
        }
        for (int k = (i + counter) - 1; k >= i; k--)
        {
            cout << setw(3) << k; // printing right side pf triangle
        }

        cout << endl;
        counter++; // incrementing the counter
    }
    cout << endl;
}
void calculator()
{
    // DECLARATION OF FUNCTIONS USED IN CALCULATOR
    double add(double, double);
    double subtract(double x, double y);
    double multiply(double x, double y);
    double divide(double x, double y);
    double remainder(double x, double y);
    double exponent(double x, double y);

    char choice;
    int num1 = 0, num2 = 0;

    // DISPLAY MENU

    // IF USER TRIES TO PERFORM ANY CALCULATIONS WIHTOUT ENTERING NUMBERS, display error msg and prompt user to enter new numbers
    do
    {
        cout << "\nFirst Number =  " << num1 << ", "
             << "Second Number = " << num2 << endl
             << "n- Enter new numbers"
             << endl
             << "a- Addition" << endl
             << "s- Subtraction" << endl
             << "m- Multiplication" << endl
             << "d- Division" << endl
             << "r- Remainder" << endl
             << "e- Exponentiation\n"
             << endl
             << "x-Exit program" << endl;
        cout << "\nSelect an option:  ";
        cin >> choice;
        cout << endl;
        if (num1 == 0 && num2 == 0 && choice != 'x')
        {
            do
            {
                cout << "Please enter  two numbers. " << endl;
                cout << "Enter number 1:  ";
                cin >> num1;
                cout << "Enter number 2:  ";
                cin >> num2;
                if (choice == 'n' && num1 != 0 && num2 != 0)
                {
                    choice = ' '; // resetting char choice if user has already entered 2 numbers
                }
                continue;
            } while (num1 == 0 && num2 == 0); // looping so that user enters 2 numbers before proceeding towards calculation
        }

        // using switch for differnet calculations
        switch (choice)
        {
        case 'n':

            cout << "Enter first number: ";
            cin >> num1;
            cout << "Enter second number: ";
            cin >> num2;
            cout << endl;
            cout << "First Number =  " << num1 << ", "
                 << "Second Number = " << num2 << endl
                 << "n- Enter new numbers\n"
                 << endl
                 << "a- Addition" << endl
                 << "s- Subtraction" << endl
                 << "m- Multiplication" << endl
                 << "d- Division" << endl
                 << "r- Remainder" << endl
                 << "e- Exponentiation\n"
                 << endl
                 << "x-Exit program" << endl;
            break;
        case 'a':
            cout << add(num1, num2) << endl;
            break;
        case 's':
            cout << subtract(num1, num2) << endl;
            break;
        case 'm':
            cout << multiply(num1, num2) << endl;
            break;
        case 'd':
            cout << divide(num1, num2) << endl;
            break;
        case 'r':
            cout << remainder(num1, num2) << endl;
            break;
        case 'e':
            cout << exponent(num1, num2) << endl;
            break;
        case 'x':
            break;
        }
    } while (choice != 'x');
}

// DEFINITION OF DIFFERENT ARITHEMATIC FUNCTIONS USED IN CALCULATOR
double add(double x, double y)
{
    cout << "--> The sum of " << x << " and " << y << " is :";
    return x + y;
}

double subtract(double x, double y)
{
    cout << "--> The difference of " << x << " and " << y << " is  :";
    return x - y;
}

double multiply(double x, double y)
{
    cout << "--> The product of " << x << " and " << y << " is :";
    return x * y;
}

double divide(double x, double y)
{
    cout << "--> The division of " << x << " and " << y << " gives:  ";
    return x / y;
}

double remainder(double x, double y)
{
    cout << "--> The remainder of " << x << "/" << y << " is :";
    return fmod(x, y); // using fmod function bcz modulus does not work with double datatype
}

double exponent(double x, double y)
{
    cout << "--> The answer for this operation is: ";
    return pow(x, y);
}

// DEFINITION FOR FUNCTION TO CALCULATE RANDOM NUMBER
int randnum()
{
    srand(static_cast<unsigned int>(time(0)));
    return rand() % 1000 + 1; // Generate random number between 1 and 1000
}

// DEFINITON OF THE TASK 3(GUESSING GAME)
void game()
{
    // declaration and initialization of some variables

    int SecretNumber = randnum(); // generate randum number using example given in lab 5
    int guess;
    int tries = 0;
    int score = 1000;
    int difference;
    do
    {
        cout << "Enter your guess: ";
        cin >> guess;
        if (guess > 1 && guess < 1001)
        {
            if (guess > SecretNumber)
            {
                difference = guess - SecretNumber;
            }
            else
            {
                difference = SecretNumber - guess;
            }

            if (guess == SecretNumber)
            {
                cout << "Correct! You've guessed the number." << endl;
                break; // break if user guess is correct
            }
            else if (difference > 200)
            {
                if (guess > SecretNumber)
                    cout << "Too high." << endl;
                else
                    cout << "Too low." << endl;
            }
            else if (difference > 10)
            {
                if (guess > SecretNumber)
                    cout << "High." << endl;
                else
                    cout << "Low." << endl;
            }
            else if (difference <= 10)
            {
                if (guess > SecretNumber)
                    cout << "Slightly high." << endl;
                else
                    cout << "Slightly low." << endl;
            }
            tries++;

            // SCORING SYSTEM
            if (difference > 500)
            {
                score -= 100;
            }
            else if (difference >= 301)
            {
                score -= 50;
            }
            else if (difference >= 201)
            {
                score -= 30;
            }
            else if (difference >= 101)
            {
                score -= 20;
            }
            else if (difference >= 11)
            {
                score -= 10;
            }
        }
        else // input validation
        {
            cout << "please enter a number from 1-1000. ";
            continue;
        }
    } while (guess != SecretNumber);

    // PENALTIES
    if (tries >= 2 && tries <= 5)
    {
        score -= tries * 10;
    }
    else if (tries >= 6 && tries <= 10)
    {
        score -= tries * 20;
    }
    else if (tries > 10)
    {
        score -= tries * 50;
    }

    if (tries <= 3)
    {
        score += 200;
    }
    else if (tries <= 6)
    {
        score += 100;
    }

    if (score < 0)
    {
        score = 0;
    }

    cout << "Game Over! You guessed the number in " << tries << " attempts." << endl;
    cout << "Your final score is: " << score << endl;
}

void pattern2()
{
    // did the pattern using while loop aswell hence including it in the program.
    int n;
    cout << "Enter the number of rows: ";
    cin >> n;

    int counter = n;
    for (int i = 1; i <= n; i++)
    {

        for (int j = 0; j < counter; j++)
        {
            cout << setw(3) << " ";
        }

        cout << i;

        int dummycounter = i + 1;
        int counter4 = i * 2 - 2;
        if (i >= 2)
        {
            while (dummycounter <= i * 2 - 1)
            {
                cout << setw(3) << dummycounter++;
            }
            while (counter4 >= i)
            {
                cout << setw(3) << counter4--;
            }
        }
        cout << endl;
        counter--;
    }
}
