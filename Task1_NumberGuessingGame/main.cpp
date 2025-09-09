#include <iostream>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()

using namespace std;

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Generate a random number between 1 and 100
    int number = rand() % 100 + 1;
    int guess;

    cout << "🎯 Guess the number between 1 and 100: ";

    // Game loop
    while (true) {
        cin >> guess;

        if (guess > number) {
            cout << "⬆ Too high! Try again: ";
        } 
        else if (guess < number) {
            cout << "⬇ Too low! Try again: ";
        } 
        else {
            cout << "🎉 Congratulations! You guessed the correct number.\n";
            break;
        }
    }

    return 0;
}