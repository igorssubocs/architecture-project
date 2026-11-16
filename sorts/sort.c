#include <stdio.h>
#include <time.h>

#define RUNS    30

int original[5000];
int numbers[5000];

int main()
{
    int sizes[3] = {
        1000,
        2500,
        5000
    };

    for (int i = 0; i < 5000; i++)
    {
        original[i] = 5000 - i;
    }

    for (int s = 0; s < 3; s++)
    {
        int size = sizes[s];
        double insertion_total = 0;
        double shell_total = 0;

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
        }

        printf("C insertion %d: %.4f ms\n", size, insertion_total / CLOCKS_PER_SEC * 1000 / RUNS);
        printf("C shell %d: %.4f ms\n", size, shell_total / CLOCKS_PER_SEC * 1000 / RUNS);
    }
}
