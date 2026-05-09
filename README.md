# Sorting Algorithms
 
Benchmarks insertion sort and counting sort in C++ against 10,000 randomly generated integers, timing each with `std::chrono` and writing results to file.
 
## Algorithms
 
**Insertion Sort — O(n²)**
Shifts elements right to insert each value into its correct position. Simple but slows significantly as input grows.
 
**Counting Sort — O(n + k)**
Tallies occurrences of each value then reconstructs the sorted array. Faster than comparison-based sorts when the value range `k` is small relative to `n`.
 
## Results
 
For 10,000 integers between 0 and 1000:
 
| Algorithm | Time |
|---|---|
| Insertion Sort | 176 ms |
| Counting Sort | 0 ms |
 
Counting Sort's advantage comes from the bounded value range (0–1000). On unbounded or large-range data, its memory cost would offset the speed gain.
 
## How to Run
 
```bash
make
./sorting
```
 
Output files `result_insertion.txt` and `result_counting.txt` contain the sorted results.
