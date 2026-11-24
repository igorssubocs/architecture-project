gcc -O2 -o sort sort.c
gcc -O0 -o sort_O0 sort.c

for i in 1 2 3 4 5 6 7 8 9 10
do
    ./sort
    python3 sort.py
done > results.txt

for i in 1 2 3 4 5 6 7 8 9 10
do
    ./sort_O0
done > results_O0.txt