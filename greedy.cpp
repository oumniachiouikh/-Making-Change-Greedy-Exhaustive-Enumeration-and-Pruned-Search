#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {

    // List of available coins, ordered from largest to smallest
    vector<int> coins = {500, 200, 100, 50, 20, 10, 5};

    // Amount of change: 12.35 euros = 1235 cents
    int amount = 1235;

    cout << fixed << setprecision(2);
    cout << "Amount to return: " << amount / 100.0 << " euros\n\n";

    int remaining = amount;
    int totalCoins = 0;

    // Greedy algorithm
    for (int coin : coins) {

        // Number of coins of this value
        int number = remaining / coin;

        if (number > 0) {

            cout << number
                 << " coin(s) of "
                 << coin / 100.0
                 << " euros\n";

            totalCoins += number;

            // Calculate the remaining amount
            remaining = remaining % coin;
        }

        // Stop if the whole amount has been returned
        if (remaining == 0) {
            break;
        }
    }

    cout << "\nTotal number of coins: "
         << totalCoins << endl;

    if (remaining != 0) {
        cout << "It is impossible to make the exact change.\n";
    } else {
        cout << "Change successfully calculated.\n";
    }

    return 0;
}