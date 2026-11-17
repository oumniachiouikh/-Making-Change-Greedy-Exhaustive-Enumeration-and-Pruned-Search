#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <climits>

using namespace std;

vector<int> coins = {500, 200, 100, 50, 20, 10, 5};   // in cents, descending
int best = INT_MAX;          // fewest coins found so far
long long nbCalls = 0;       // number of recursive calls
bool verbose = true;

// S[k] = number of coins of value coins[k]; used = coins chosen so far
void solve(int i, int remaining, int used, vector<int>& S) {
    nbCalls++;

    // CUT 1: already as many coins as the best solution -> cannot improve
    if (used >= best) return;

    // Stop condition: amount fully returned -> it improves the best
    if (remaining == 0) {
        best = used;
        if (verbose) {
            cout << "Improving solution (" << used << " coins): ";
            for (size_t k = 0; k < coins.size(); k++)
                if (S[k] > 0) cout << S[k] << "x" << coins[k] / 100.0 << "  ";
            cout << "\n";
        }
        return;
    }

    // No more coin types -> dead end
    if (i >= (int)coins.size()) return;

    // CUT 2: even with the largest remaining coin, we need at least
    // ceil(remaining / coins[i]) more coins. If that cannot improve, stop.
    int minMore = (remaining + coins[i] - 1) / coins[i];
    if (used + minMore >= best) return;

    // Try the largest counts first: good solutions are found early,
    // so the cuts become effective sooner
    for (int j = remaining / coins[i]; j >= 0; j--) {
        S[i] = j;
        solve(i + 1, remaining - j * coins[i], used + j, S);
    }
    S[i] = 0;   // undo (backtracking)
}

int main() {
    int amount = 1235;   // 12.35 euros
    vector<int> S(coins.size(), 0);

    cout << "Amount: " << amount / 100.0 << " euros\n\n";
    solve(0, amount, 0, S);
    cout << "\nBest number of coins: " << best << "\n";
    cout << "Recursive calls: " << nbCalls << "\n\n";

    // Table to compare with the version without cut
    verbose = false;
    cout << "amount(cents)  best coins      calls        time(ms)\n";
    for (int a = 200; a <= 1600; a += 200) {
        best = INT_MAX;
        nbCalls = 0;
        fill(S.begin(), S.end(), 0);
        auto t0 = chrono::steady_clock::now();
        solve(0, a, 0, S);
        auto t1 = chrono::steady_clock::now();
        double ms = chrono::duration<double, milli>(t1 - t0).count();
        cout << setw(10) << a << setw(12) << best
             << setw(14) << nbCalls << setw(14) << fixed
             << setprecision(3) << ms << "\n";
    }
    return 0;
}