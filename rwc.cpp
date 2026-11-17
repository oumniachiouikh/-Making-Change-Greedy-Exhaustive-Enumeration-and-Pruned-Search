#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
#include <algorithm>

using namespace std;

// ------------------------------------------------------------
// Display a solution
// ------------------------------------------------------------
void displaySolution(const vector<int>& coins,
                     const vector<int>& solution,
                     int totalCoins)
{
    cout << "\nBest solution found:\n";

    for (int i = 0; i < (int)coins.size(); i++)
    {
        if (solution[i] > 0)
        {
            cout << solution[i]
                 << " coin(s) of "
                 << fixed << setprecision(2)
                 << coins[i] / 100.0
                 << " euros\n";
        }
    }

    cout << "Total number of coins: "
         << totalCoins << endl;
}


// ------------------------------------------------------------
// Recursive algorithm with cuts
// ------------------------------------------------------------
void recursiveWithCut(
    const vector<int>& coins,
    int index,
    int remaining,
    vector<int>& currentSolution,
    int currentNumberOfCoins,
    int& bestNumberOfCoins,
    vector<int>& bestSolution)
{
    // --------------------------------------------------------
    // STOP CONDITION 1:
    // Exact amount has been reached.
    // --------------------------------------------------------
    if (remaining == 0)
    {
        // We found a better solution
        if (currentNumberOfCoins < bestNumberOfCoins)
        {
            bestNumberOfCoins = currentNumberOfCoins;
            bestSolution = currentSolution;

            cout << "\nImproved solution found: "
                 << bestNumberOfCoins
                 << " coins\n";
        }

        return;
    }

    // --------------------------------------------------------
    // STOP CONDITION 2:
    // We have used all coin types.
    // --------------------------------------------------------
    if (index >= (int)coins.size())
    {
        return;
    }

    // --------------------------------------------------------
    // CUT 1:
    //
    // If the current solution already uses as many coins
    // as the best solution, continuing cannot improve it.
    // --------------------------------------------------------
    if (currentNumberOfCoins >= bestNumberOfCoins)
    {
        return;
    }

    // --------------------------------------------------------
    // CUT 2:
    //
    // Calculate an optimistic lower bound.
    //
    // The largest remaining coin is coins[index].
    // Even in the best possible case, we need at least:
    //
    // ceil(remaining / coins[index])
    //
    // additional coins.
    // --------------------------------------------------------
    int minimumAdditionalCoins =
        (remaining + coins[index] - 1) / coins[index];

    if (currentNumberOfCoins + minimumAdditionalCoins
        >= bestNumberOfCoins)
    {
        return;
    }

    // --------------------------------------------------------
    // Try all possible numbers of coins of coins[index].
    //
    // j = 0, 1, 2, ..., maximum possible number
    // --------------------------------------------------------
    int maximumNumber =
        remaining / coins[index];

    for (int j = 0; j <= maximumNumber; j++)
    {
        // Add j coins of the current denomination
        currentSolution[index] = j;

        // Calculate the new remaining amount
        int newRemaining =
            remaining - j * coins[index];

        // Recursive call with the next denomination
        recursiveWithCut(
            coins,
            index + 1,
            newRemaining,
            currentSolution,
            currentNumberOfCoins + j,
            bestNumberOfCoins,
            bestSolution
        );

        // Remove the choice before trying the next one
        currentSolution[index] = 0;
    }
}


// ------------------------------------------------------------
// Main
// ------------------------------------------------------------
int main()
{
    // Coins in decreasing order
    // Values are expressed in cents
    vector<int> coins =
    {
        500,  // 5.00 €
        200,  // 2.00 €
        100,  // 1.00 €
        50,   // 0.50 €
        20,   // 0.20 €
        10,   // 0.10 €
        5     // 0.05 €
    };

    // 12.35 € = 1235 cents
    int amount = 1235;

    // Current candidate solution
    vector<int> currentSolution(coins.size(), 0);

    // Best solution found so far
    vector<int> bestSolution(coins.size(), 0);

    // Start with infinity
    int bestNumberOfCoins = INT_MAX;

    cout << fixed << setprecision(2);

    cout << "========================================\n";
    cout << "   MAKES CHANGE - RECURSIVE WITH CUT\n";
    cout << "========================================\n\n";

    cout << "Amount: "
         << amount / 100.0
         << " euros\n\n";

    cout << "Searching for the best solution...\n";

    // Start recursive search
    recursiveWithCut(
        coins,
        0,                  // Start with first coin
        amount,             // Remaining amount
        currentSolution,    // Current solution
        0,                  // Number of coins currently used
        bestNumberOfCoins,  // Best number found
        bestSolution        // Best combination
    );

    // --------------------------------------------------------
    // Display final result
    // --------------------------------------------------------
    cout << "\n========================================\n";
    cout << "              FINAL RESULT\n";
    cout << "========================================\n";

    if (bestNumberOfCoins == INT_MAX)
    {
        cout << "No exact solution exists.\n";
    }
    else
    {
        displaySolution(
            coins,
            bestSolution,
            bestNumberOfCoins
        );
    }

    return 0;
}