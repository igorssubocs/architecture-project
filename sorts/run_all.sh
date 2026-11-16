gcc -O2 -o sort sort.c

for i in 1 2 3 4 5 6 7 8 9 10
do
    ./sort
    python3 sort.py
done > result.txt