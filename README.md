# Making Change: Greedy, Exhaustive and Pruned Search

Practical Work 1 of **UE 7 – Mobility in Smart Cities** (Dynamic Transportation & Exact Solving, Ph. Canalda).

Authors: Oumnia Chiouikh, Malick Diop

## What it does

Solves the "making change" problem for the euro coin system
L = {5, 2, 1, 0.5, 0.2, 0.1, 0.05} and the amount m = 12.35 EUR, using
integer cents (500, 200, ..., 5 and m = 1235) to avoid floating-point errors.

| File | Method | Result for 12.35 EUR |
|---|---|---|
| `greedy.cpp` | Greedy, iterative | 6 coins, ~14 ns |
| `allsolutions.cpp` | Recursive enumeration of all solutions | 266,724 solutions, 12.6 M calls |
| `rwc.cpp` | Recursive search with cuts, counts tried in ascending order | best = 6 coins, 20,936 calls |
| `sib.cpp` | Recursive search with cuts, counts tried in descending order | best = 6 coins, 22 calls |
| `bench.cpp` | Measurement harness (calls, cuts, improvements, timings) | used for the report tables |

Main finding: the order in which choices are explored matters more than the
pruning rule itself. Trying the largest coin counts first finds the optimal
solution on the first branch, so the bound removes almost everything else.

## Build and run

    g++ -O2 -std=c++17 -o greedy greedy.cpp && ./greedy
    g++ -O2 -std=c++17 -o allsolutions allsolutions.cpp && ./allsolutions
    g++ -O2 -std=c++17 -o rwc rwc.cpp && ./rwc
    g++ -O2 -std=c++17 -o sib sib.cpp && ./sib
    g++ -O2 -std=c++17 -o bench bench.cpp && ./bench

## Report

The full report (design, measurements, analysis) is in `report/main.tex`
(LaTeX, compiles on Overleaf).

## Notes

- Greedy is optimal here because the euro system is canonical; it fails on
  e.g. L = {3, 2}, m = 7 or L = {5, 2, 1.5}, m = 9.5, where the exhaustive
  and pruned searches still find a solution.
- Timings were measured on one machine with `-O2` and are indicative.
