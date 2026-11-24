import time

RUNS = 10
MAX = 16000

sizes = [1000, 2000, 4000, 8000, 16000]
names = ["reversed", "random", "nearly"]

for type in range(3):
    original = []
    x = 1
    for i in range(MAX):
        if type == 0:
            original.append(MAX - i)
        if type == 1:
            x = (x * 75 + 74) % 65537
            original.append(x)
        if type == 2:
            original.append(i)
    if type == 2:
        for i in range(0, MAX - 1, 100):
            tmp = original[i]
            original[i] = original[i + 1]
            original[i + 1] = tmp

    for size in sizes:
        insertion_total = 0
        shell_total = 0
        ok = True

        for run in range(RUNS):
            numbers = original[:size]

            start = time.process_time()
            for i in range(1, size):
                curr = numbers[i]
                position = i - 1
                while position >= 0 and numbers[position] > curr:
                    numbers[position + 1] = numbers[position]
                    position = position - 1
                numbers[position + 1] = curr
            insertion_total = insertion_total + (time.process_time() - start)

            for i in range(1, size):
                if numbers[i - 1] > numbers[i]:
                    ok = False

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

            for i in range(1, size):
                if numbers[i - 1] > numbers[i]:
                    ok = False

        result = "OK" if ok else "ERROR"
        print(f"Python insertion {names[type]} {size}: {insertion_total * 1000 / RUNS:.4f} ms {result}")
        print(f"Python shell {names[type]} {size}: {shell_total * 1000 / RUNS:.4f} ms {result}")