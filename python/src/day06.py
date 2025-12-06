"""
AoC Day 6
"""

from functools import reduce

INPUT_FILE = "../inputs/day06.txt"


def solve_p1():
    total = 0
    with open(INPUT_FILE, "r") as f:
        nums = None
        for line in f.readlines():
            if nums is None:
                nums = [[int(x)] for x in line.split()]
                continue
            for i, x in enumerate(line.split()):
                if x.isdecimal():
                    nums[i].append(int(x))
                elif x == "*":
                    total += reduce(lambda a, b: a * b, nums[i])
                elif x == "+":
                    total += sum(nums[i])
                else:
                    assert False, x
    return total


def solve_p2():
    total = 0
    with open(INPUT_FILE, "r") as f:
        lines = [l.rstrip("\n") for l in f.readlines() if l.strip()]

    M = len(lines[0])

    stack = []
    for i in range(M - 1, -1, -1):
        x = "".join([l[i] for l in lines])
        if not x.strip():
            continue
        if x.endswith(" "):
            stack.append(int(x))
        else:
            stack.append(int(x[:-1]))
            if x[-1] == "*":
                total += reduce(lambda a, b: a * b, stack)
            elif x[-1] == "+":
                total += sum(stack)
            else:
                assert False, x
            stack = []

    return total


def main():
    print(f"Part 1: {solve_p1()}")
    print(f"Part 2: {solve_p2()}")


if __name__ == "__main__":
    main()
