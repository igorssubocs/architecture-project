#include <stdio.h>
#include <time.h>

#define RUNS 100
#define MAX 16000

int original[MAX];
int numbers[MAX];

int main()
{
    int sizes[5] = {1000, 2000, 4000, 8000, 16000};
    char *names[3] = {"reversed", "random", "nearly"};

    for (int type = 0; type < 3; type++)
    {
        int x = 1;

        for (int i = 0; i < MAX; i++)
        {
            if (type == 0)
                original[i] = MAX - i;
            if (type == 1)
            {
                x = (x * 75 + 74) % 65537;
                original[i] = x;
            }
            if (type == 2)
                original[i] = i;
        }
        if (type == 2)
        {
            for (int i = 0; i < MAX - 1; i = i + 100)
            {
                int tmp = original[i];
                original[i] = original[i + 1];
                original[i + 1] = tmp;
            }
        }

        for (int s = 0; s < 5; s++)
        {
            int size = sizes[s];
            double insertion_total = 0;
            double shell_total = 0;
            int ok = 1;

            for (int run = 0; run < RUNS; run++)
            {
                for (int i = 0; i < size; i++)
                {
                    numbers[i] = original[i];
                }
                
                clock_t start = clock();
                for (int i = 1; i < size; i++)
                {
                    int curr = numbers[i], position = i - 1;

                    while   (position >= 0 && numbers[position] > curr)
                    {
                        numbers[position + 1] = numbers[position];
                        position = position - 1;
                    }
                    numbers[position + 1] = curr;
                }
                insertion_total = insertion_total + (clock() - start);

                for (int i = 1; i < size; i++)
                {
                    if (numbers[i - 1] > numbers[i]) {
                        ok = 0;
                    }
                }
                
                for (int i = 0; i < size; i++)
                {
                    numbers[i] = original[i];
                }

                start = clock();
                for (int jump = size / 2; jump > 0; jump = jump / 2)
                {
                    for (int j = jump; j < size; j++)
                    {
                        int curr = numbers[j], position = j - jump;

                        while   (position >= 0 && numbers[position] > curr)
                        {
                            numbers[position + jump] = numbers[position];
                            position = position - jump;
                        }
                        numbers[position + jump] = curr;
                    }
                }
                shell_total = shell_total + (clock() - start);

                for (int i = 1; i < size; i++)
                {
                    if (numbers[i - 1] > numbers[i]) {
                        ok = 0;
                    }
                }
            }

            printf("C insertion %s %d: %.4f ms %s\n", names[type], size, insertion_total / CLOCKS_PER_SEC * 1000 / RUNS, ok ? "OK" : "ERROR");
            printf("C shell %s %d: %.4f ms %s\n", names[type], size, shell_total / CLOCKS_PER_SEC * 1000 / RUNS, ok ? "OK" : "ERROR");
        }
    }
}
