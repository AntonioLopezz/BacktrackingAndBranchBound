# Greedy & Backtracking 🔧🧩

Implementation of two algorithmic paradigms in C++ applied to two real optimization problems: a **Greedy** algorithm for mechanic-to-fault assignment, and a **Backtracking** algorithm for maximum-diversity subset selection. Both include theoretical complexity analysis via the RAM model and experimental validation with regression fitting.

Both solutions were accepted on the **Mooshak** online judge.

---

## 📋 Problems

### 1. Greedy — Mechanic Assignment
Given `M` mechanics and `A` faults, and a boolean compatibility matrix `C[i][j]` indicating whether mechanic `i` can fix fault `j`, find an assignment that maximizes the number of faults repaired (each mechanic can be assigned to at most one fault per day). A solution reaching at least 60% of the optimum is considered valid.

**Selection strategy:** faults are pre-sorted by the number of mechanics that can fix them (ascending), so the most restrictive faults are assigned first, preventing the only capable mechanic from being taken by a less critical fault.

| Case | Complexity |
|------|-----------|
| Worst case | Θ(n²) |
| Best case | Θ(n²) |

Both cases share the same dominant term due to the counting loop that always traverses the full M×A matrix. Confirmed experimentally with R² = 0.9965.

---

### 2. Backtracking — Maximum Diversity Subset
Given a set of `n` elements and a distance matrix `D[i][j]`, select a subset of `m` elements that maximizes the total sum of pairwise distances. The solution vector is kept in strictly increasing order to avoid exploring equivalent subsets.

**Pruning strategy:** before expanding a branch, an optimistic upper bound is computed as `remaining_pairs × max_pair_distance`. If this estimate cannot beat the current best solution, the branch is pruned.

| Case | Complexity |
|------|-----------|
| Worst case (no pruning) | Θ(2ⁿ) |
| Best case (effective pruning) | Θ(n) |

Worst case confirmed experimentally with R² = 0.9990. Best case R² = 0.9230 (lower value explained by execution times near the `std::chrono` clock resolution).

---

## 📂 Project Structure

```
GreedyAndBacktracking/
├── E_AR.h                    # Greedy function declarations
├── E_AR.cpp                  # Greedy implementation
├── E_BT.h                    # Backtracking function declarations
├── E_BT.cpp                  # Backtracking implementation
├── test_unitarios_AR.cpp     # Manual unit tests — Greedy
├── test_unitarios_BT.cpp     # Manual unit tests — Backtracking
├── tiempos_AR.cpp            # Worst case timing — Greedy
├── tiempos_BT.cpp            # Best/worst case timing — Backtracking
├── regresion_AR.py           # Regression fitting and plots — Greedy
├── regresion_BT.py           # Regression fitting and plots — Backtracking
├── Makefile                  # Build rules
├── figurasAR/
│   ├── ajuste_peor_AR.pdf         # Quadratic fit — Greedy worst case
│   ├── ajuste_peor_log_AR.pdf     # Same with log x-axis
│   ├── puntos_peor_AR.pdf         # Raw timing scatter — Greedy
│   ├── puntos_peor_log_AR.pdf     # Same with log x-axis
│   ├── regresion_AR.txt           # Regression coefficients
│   └── resultados_AR.csv          # Raw timing data
├── figurasBT/
│   ├── ajuste_mejor_caso_BT.pdf   # Linear fit — Backtracking best case
│   ├── ajuste_peor_caso_BT.pdf    # Exponential fit — Backtracking worst case
│   ├── comparativa_poda_BT.pdf    # Best vs worst case comparison
│   ├── regresion_BT.txt           # Regression coefficients
│   └── resultados_BT.csv          # Raw timing data
└── AEDII_BT_AR.pdf           # Full technical report
```

## 🛠️ Build & Run

```bash
make
```

Run unit tests:
```bash
./prueba_AR
./prueba_BT
```

Run timing analysis:
```bash
./prueba_tiempos_AR
./prueba_tiempos_BT
```

Generate regression plots (requires Python + matplotlib + numpy + scipy):
```bash
python regresion_AR.py
python regresion_BT.py
```

## ✅ Validation

**Greedy** — tested with manual cases covering: no mechanics available, single mechanic for all faults, last mechanic being the only capable one (worst case trigger), and the example from the problem statement.

**Backtracking** — tested with manual cases from the problem statement plus best/worst case generators. Input sizes `n ∈ {4, 6, 8, ..., 22}` with `m = n/2` (maximizes C(n,m) and therefore the worst case).

## 📊 Experimental Results

**Greedy** — input sizes `nᵢ = 100 · 2ⁱ` for `i = 0..6`, up to `n = 6400` (memory-limited by the n×n boolean matrix). 10 measurements per size, median taken.

| n | Time (ms) |
|---|-----------|
| 100 | 0.10 |
| 200 | 0.27 |
| 400 | 0.79 |
| 800 | 3.38 |
| 1600 | 17.25 |
| 3200 | 91.22 |
| 6400 | 475.34 |

**Backtracking** — 5 measurements per size, median taken. Exponential growth in the worst case vs near-constant time in the best case due to effective pruning.

| n | Worst (ms) | Best (ms) |
|---|-----------|----------|
| 4 | 0.0023 | 0.0013 |
| 10 | 0.0202 | 0.0035 |
| 16 | 2.2542 | 0.0062 |
| 22 | 127.60 | 0.0118 |

## 🔧 Technologies

- C++17
- Python 3 (numpy, matplotlib, scipy)
- Make
