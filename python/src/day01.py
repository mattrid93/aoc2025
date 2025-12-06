"""
Advent of Code 2025 day 1
"""

INPUT_FILE = "../inputs/day01.txt"


def parse_input():
    with open(INPUT_FILE, "r") as f:
        return [_.strip() for _ in f.readlines()]


def solve_p1(rotations):
    pos = 50
    zeros = 0
    for rot in rotations:
        d, x = rot[:1], int(rot[1:])
        if d == "L":
            x *= -1
        pos = (pos + x) % 100
        if pos == 0:
            zeros += 1
    return zeros


def solve_p2(rotations):
    pos = 50
    zeros = 0
    for rot in rotations:
        start = pos
        d, x = rot[:1], int(rot[1:])
        if d == "L":
            x *= -1
        pos += x
        passes, pos = divmod(pos, 100)
        if x < 0 and start == 0:
            # Already counted "passing" zero previously
            zeros += abs(passes) - 1
        else:
            zeros += abs(passes)
        if pos == 0 and x < 0:
            # Need to account for final land on zero from above
            zeros += 1
    return zeros


def main():
    data = parse_input()
    print(f"Part 1 = {solve_p1(data)}")
    print(f"Part 2 = {solve_p2(data)}")


if __name__ == "__main__":
    main()
