#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

vector<int> coins = {500, 200, 100, 50, 20, 10, 5};   // in cents
long long nbSolutions = 0;   // number of solutions found
long long nbCalls = 0;       // number of recursive calls (measures the work)
bool verbose = true;         // print the first solutions

// S[k] = number of coins of value coins[k] chosen so far
void solve(int i, int remaining, vector<int>& S) {
    nbCalls++;

    // Stop condition 1: the whole amount is returned -> a solution
    if (remaining == 0) {
        nbSolutions++;
        if (verbose && nbSolutions <= 10) {
            cout << "Solution " << nbSolutions << ": ";
            int total = 0;
            for (size_t k = 0; k < coins.size(); k++) {
                if (S[k] > 0) {
                    cout << S[k] << "x" << coins[k] / 100.0 << "  ";
                    total += S[k];
                }
            }
            cout << "(" << total << " coins)\n";
        }
        return;
    }

    // Stop condition 2: no more coin types -> no solution on this branch
    if (i >= (int)coins.size()) return;

    // Try every possible number of coins of type i: 0 .. remaining / coins[i]
    for (int j = 0; j <= remaining / coins[i]; j++) {
        S[i] = j;
        solve(i + 1, remaining - j * coins[i], S);
    }
    S[i] = 0;   // undo before going back up
}

int main() {
    int amount = 1235;   // 12.35 euros
    vector<int> S(coins.size(), 0);

    cout << "Amount: " << amount / 100.0 << " euros\n\n";
    solve(0, amount, S);
    cout << "\nTotal number of solutions: " << nbSolutions << "\n";
    cout << "Recursive calls: " << nbCalls << "\n\n";

    // Table for the complexity curve
    verbose = false;
    cout << "amount(cents)  solutions      calls        time(ms)\n";
    for (int a = 200; a <= 1600; a += 200) {
        nbSolutions = 0;
        nbCalls = 0;
        fill(S.begin(), S.end(), 0);
        auto t0 = chrono::steady_clock::now();
        solve(0, a, S);
        auto t1 = chrono::steady_clock::now();
        double ms = chrono::duration<double, milli>(t1 - t0).count();
        cout << setw(10) << a << setw(12) << nbSolutions
             << setw(12) << nbCalls << setw(14) << fixed
             << setprecision(3) << ms << "\n";
    }
    return 0;
}