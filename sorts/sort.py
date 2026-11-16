import time

RUNS = 30

original = []
for i in range (5000):
    original.append(5000 - i)

sizes = [1000, 2500, 5000]

for size in sizes:
    insertion_total = 0
    shell_total = 0

    for run in range(RUNS):
        numbers = original[:size]

        start  = time.process_time()

        for i in range(1, size):
            curr = numbers[i]
            position = i - 1

            while position >= 0 and numbers[position] > curr:
                numbers[position + 1] = numbers[position]
                position = position - 1
            numbers[position + 1] = curr

        insertion_total = insertion_total + (time.process_time() - start)

        numbers = original[:size]

        start = time.process_time()

        jump = size // 2
        while jump > 0:
            for j in range(jump, size):
                curr = numbers[j]
                position = j - jump

                while position >= 0 and numbers[position] > curr:
                    numbers[position + jump] = numbers[position]
                    position = position - jump
                numbers[position + jump] = curr
            jump = jump // 2

        shell_total = shell_total + (time.process_time() - start)

    print(f"Python insertion {size}: {insertion_total * 1000 / RUNS:.4f} ms")
    print(f"Python shell {size}: {shell_total * 1000 / RUNS:.4f} ms")