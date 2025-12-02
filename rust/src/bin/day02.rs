// Day 2

use std::fs;

const INPUT_FILE: &str = "../inputs/day02.txt";

fn parse_input() -> Vec<(usize, usize)> {
    let mut result: Vec<(usize, usize)> = fs::read_to_string(INPUT_FILE)
        .expect("No input file")
        .strip_suffix("\n")
        .unwrap()
        .split(",")
        .map(|pair| {
            let vec: Vec<usize> = pair
                .split("-")
                .map(|s| s.parse::<usize>().unwrap())
                .collect();
            (vec[0], vec[1])
        })
        .collect();
    result.sort();
    result
}

fn invalid_id(counter: usize, reps: usize) -> usize {
    let mut s = counter.to_string();
    for _ in 1..reps {
        s.push_str(&counter.to_string());
    }
    s.parse::<usize>().unwrap()
}

fn solve_p1(input: &[(usize, usize)]) -> usize {
    let mut total: usize = 0;
    let mut counter: usize = 1;
    let mut id = invalid_id(counter, 2);
    for &(s, e) in input {
        while id < s {
            counter += 1;
            id = invalid_id(counter, 2);
        }
        while id <= e {
            total += id;
            counter += 1;
            id = invalid_id(counter, 2);
        }
    }
    total
}

fn is_invalid_id(id: usize) -> bool {
    let s = id.to_string();
    let n = s.len();
    if n < 2 {
        return false;
    }
    for m in 1..(n / 2 + 1) {
        if n % m == 0 {
            let k = n / m;
            if s == s.get(..m).unwrap().repeat(n / m) {
                return true;
            }
        }
    }
    false
}

fn solve_p2(input: &[(usize, usize)]) -> usize {
    let mut total: usize = 0;
    for &(s, e) in input {
        for i in s..(e + 1) {
            if is_invalid_id(i) {
                total += i;
            }
        }
    }
    total
}

fn main() {
    let input = parse_input();
    println!("Part 1: {}", solve_p1(&input));
    println!("Part 2: {}", solve_p2(&input));
}
