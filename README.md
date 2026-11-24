# Language or Algorithm? C vs Python Sorting Speed

Research project for CII3SE003CI Architecture of Computers, Vistula University.
Author: Igors Subočs (77186)

## Files

- `sort.c` – insertion sort and shell sort in C
- `sort.py` – the same sorts in Python
- `run_all.sh` – runs all tests
- `results.txt` – C (-O2) and Python results
- `results_O0.txt` – C results without optimization (-O0)

## Tests

- Data: reversed, random, nearly sorted
- Sizes: 1000, 2000, 4000, 8000, 16000
- C repeats each sort 100 times, Python 10 times; the average is printed
- Each line ends with OK if the array was sorted correctly
- Everything is run 10 times; the paper uses the median

## Requirements

gcc or clang, Python 3. No extra libraries.

## Run

```bash
bash run_all.sh
```

Takes about 25 minutes.