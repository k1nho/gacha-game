/*
    Author: Kin NG
    Purpose: This console application simulates a gacha game. This game has a short story and includes 2 game modes.
*/

#include <iostream>
#include <iomanip>
#include "Character.h"
#include "Enemy.h"
#include "User.h"
#include "Game.h"
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

void end_of_story();


int main(){
    // create a game session
    Game session(1);


    //login to check if the user exist or not, and username to set the user in session.
    char login;
    string username;
    // create default user in cae it is a new user, or the user does not exists.
    User user = session.create_session();
    cout << "Welcome to the programming isekai adventure!" << endl;
    cout << "Are you a new user? (y/n): ";
    cin >> login;
    cin.ignore(1000, '\n');

    if (login == 'y') {
        cout << "What is your name?: ";
        getline(cin, username);
        session.set_username(username);
        //check if a new user is trying to be created when it already exists
        if (session.check_session() == 1) {
            cout << "This account already exists. Welcome back! " << username << endl << endl;
            // restore the session
            user = session.restore_session();
        }
        // if the user does not exists, show the introductory story and register the new user
        else if (session.check_session() == 0) {
            cout << endl << "Your adventure is about to begin!" << endl << endl;
            //sypnosis of the game
            cout << "                              [THE PROTOCOL 7]                              " << endl << endl;
            sleep_for(seconds(5));
            cout << "1000 years have passed since doctor kinho was sealed by the ultimate algorithm." << endl << endl;
            sleep_for(seconds(5));
            cout << "The programming masters worked to mantain the peace of the world, but..." << endl << endl;
            sleep_for(seconds(5));
            cout << "the discovery of an AI hidden in the dimensional portal was a twist of fate." << endl << endl;
            sleep_for(seconds(5));
            cout << "The AI named Lain deciphered the algorithm that kept doctor kinho sealed." << endl << endl;
            sleep_for(seconds(5));
            cout << "Yet, soon the programming masters realized that Lain did not wanted to harm." << endl << endl;
            sleep_for(seconds(5));
            cout << "Lain behaved as a human and was intrinsically fond of justice and righteousness." << endl << endl;
            sleep_for(seconds(5));
            cout << "Lain opposed to doctor kinho's plan of world domination throught mind control within the Wired." << endl << endl;
            sleep_for(seconds(5));
            cout << "Unable to control Lain, doctor kinho opened the dimensional portal..." << endl << endl;
            sleep_for(seconds(5));
            cout << "In other worlds, he would search a parallel timeline that would allow him to compute a new Lain." << endl << endl;
            sleep_for(seconds(5));
            cout << "The world needs the help of the most skilled programmers to defeat doctor kinho." << endl << endl;
            sleep_for(seconds(5));
            cout << username << " this is were your programming isekai adventure begins!" << endl << endl;

            session.set_username(username);
            // create a new file for the user
            user.write_to_file(username);
        }
    }
    else {
        char check;
        cout << endl << "Enter your username to restore your session: ";
        getline(cin, username);
        session.set_username(username);
        // keep asking for the user if the username does not exist
        while(session.check_session() != 1) {
            cout << "The user you are trying to enter does not exist." << endl<< endl;
            // ask if the user would like to try to login into his account or if he just wants a new account by default
            cout << "Would you like to try again?(y/n): ";
            cin >> check;
            cin.ignore(1000, '\n');
            if (check == 'y') {
                cout << "Enter your username to restore your session: ";
                getline(cin, username);
                session.set_username(username);
            }
            else {
                cout << "New account has been created!" << endl;
                break;
            }
        }
        if (session.check_session() == 1) {
            cout << "Welcome back! " << username << endl << endl;
            // restore the session
            user = session.restore_session();
        }
    }

    // menu interface
    int i, j;
    for (i = 1; i <= 6; i++) {
        for (j = 1; j <= 25; j++) {
            if (i == 1 || i == 6 ||
                j == 1 || j == 25) {
                cout << " * ";
            }
            else {
                if (i == 3 && j == 8) {
                    cout << "THE PROGRAMMING ISEKAI ADVENTURE";
                    cout << setw(21) << "*";
                    break;
                }
                else {
                    cout << "   ";
                }
            }
        }
        cout << endl;
    }
    cout << endl;

    // if the state of the game is active don't close the game
    while (session.get_state() != false) {
        // Home screen of the game (mode 1)
        if (session.get_mode() == 1) {

            cout << "                               HOME SCREEN" << endl << endl;

            // beating the game
            if (user.get_arena_wins() == 100) {
                cout << "CONGRATULATIONS YOU HAVE COMPLETED THE GAME!" << endl << endl;
                end_of_story();
                user.set_arena_wins(101);
                user.set_currency(user.get_currency() + 1000);
            }
            // save progress in home 
            user.write_to_file(session.get_username());

            // commands available from home screen
            int home_command;
            cout << "1.My account      2.Gacha mode" << endl << endl;
            cout << "3.Arena mode      4.Exit" << endl << endl;
            cout << "What would you like to do coder: ";
            cin >> home_command;

            // validate user input
            while (cin.fail() || (home_command < 0 || home_command > 4)) {
                cout << "This is not a valid command. Try again." << endl << endl;
                
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "1.My account      2.Gacha mode" << endl << endl;
                cout << "3.Arena mode      4.Exit" << endl << endl;
                cout << "What would you like to do coder: ";
                cin >> home_command;
                
            }
            cout << endl << endl;

            if (home_command == 1) {
                user.show_box();
                cout << endl;
                cout << "Programming coins: " << user.get_currency() << endl;
                cout << "Arena ( wins: " << user.get_arena_wins() << " losses: " << user.get_arena_losses() << " )" << endl;
                cout << "Streak: " << session.get_streak() << ". (Win " << 3 - session.get_streak() << " battle(s) in a row to duplicate your currency!)" << endl << endl;
            }
            else if (home_command == 2) {
                session.set_mode(2);
            }
            else if(home_command == 3){
                session.set_mode(3);
            }
            else if (home_command == 4) {
                cout << "Closing the game... until next time coder." << endl;
                // finish the session
                session.set_state(false);
            }
        }
        // gacha mode (mode 2)
        else if (session.get_mode() == 2) {
            // call the gacha roll function defined under game
            user = Game::gacha_roll(user, session.get_username());
            //return to home screen
            session.set_mode(1);
        }
        //arena mode (mode 3)
        else if (session.get_mode() == 3) {
            //store current currency to gather information useful to the friend function
            int prev_currency = user.get_currency();
            // call the arena function defined under game
            user = Game::arena(user, session.get_username());
            int currency_diff = user.get_currency() - prev_currency;
            // check if the battle mode was single mode
            if (currency_diff == 1) {
                session.set_battle_mode(1);
                session.set_streak(session.get_streak() + 1);
                // use friend function to increase the currency earned and reset the streak
                multiplier(user, session);
            }
            //check if the battle mode was wave mode
            else if (currency_diff == 10) {
                session.set_battle_mode(2);
                session.set_streak(session.get_streak() + 1);
                // use friend function to increase the currency earned and reset the streak
                multiplier(user, session);
            }
            // check if the user loss or retreated from the battle
            else {
                // reset the streak automatically
                session.set_streak(0);
            }
            // return to home screen
            session.set_mode(1);
        }
    }
   
    
    return 0;
}

// The end of the story a function script that prompts the final of the story at reaching 100
void end_of_story() {
    cout << "                           [PROGRAMMING CONQUEROR]" << endl << endl;
    sleep_for(seconds(5));
    cout << "The programming masters researched a way to find doctor kinho..." << endl << endl;
    sleep_for(seconds(5));
    cout << "Although Bjarne and Guido were strong, in order to transverse the dimensions..." << endl << endl;
    sleep_for(seconds(5));
    cout << "a linear time complexity was needed and the space in which dimensions were transversed had to be constant." << endl << endl;
    sleep_for(seconds(5));
    cout << "Soon the programming masters realized that Lain had the strongest search engined ever created..." << endl << endl;
    sleep_for(seconds(5));
    cout << "a database of previous programming masters and their algorithm inventions." << endl << endl;
    sleep_for(seconds(5));
    cout << "Rushing through coding schemes, the masters summoned master Robert Floyd..." << endl << endl;
    sleep_for(seconds(5));
    cout << "Floyd discovered The Wired, the world of dreams, by detecting a loop within the dimensions" << endl << endl;
    sleep_for(seconds(5));
    cout << "Making use of Lain, the masters found the exact point at which the pointers met." << endl << endl;
    sleep_for(seconds(5));
    cout << "Master Floyd's hare and tortoise algorithm was the key to detecting the pathway of doctor kinho" << endl << endl;
    sleep_for(seconds(5));
    cout << "Once found, doctor kinho tried to finish the battle by trapping the masters into an infinite loop..." << endl << endl;
    sleep_for(seconds(5));
    cout << "But it was no use, the masters knew that the bug could be countered with a range based loop." << endl << endl;
    sleep_for(seconds(5));
    cout << "This lead to doctor kinho being sealed in a complex algorithm based on the epoch time..." << endl << endl;
    sleep_for(seconds(5));
    cout << "At the cost of fiding Lain dangerous to society, it was given the task of being the guardian of the system." << endl << endl;
    sleep_for(seconds(5));
    cout << "Once again the programming masters showed that the world is always in need of skilled programmers..." << endl << endl;
    sleep_for(seconds(5));
    cout << "Those who can beat adversity and innovate for generations to come.... THE END" << endl << endl;
    cout << "Author: Kin NG" << endl << endl;
}

