// Day 2

use std::fs;

const INPUT_FILE: &str = "../inputs/day04.txt";

fn parse_input() -> Vec<Vec<i32>> {
    fs::read_to_string(INPUT_FILE)
        .expect("no input file")
        .trim_end()
        .lines()
        .map(|line| line.chars().map(|c| (c == '@') as i32).collect())
        .collect()
}

fn remove(input: &mut Vec<Vec<i32>>, neighbours: &mut Vec<Vec<i32>>, n: usize, m: usize) -> usize {
    let mut removed = 0;
    for i in 0..n {
        for j in 0..m {
            if input[i][j] == 1 && neighbours[i][j] < 4 {
                removed += 1;
                input[i][j] = 2;
            }
        }
    }
    for i in 0..n {
        for j in 0..m {
            if input[i][j] == 2 {
                input[i][j] = 0;
                if j > 0 {
                    neighbours[i][j - 1] -= 1;
                }
                if j < m - 1 {
                    neighbours[i][j + 1] -= 1;
                }
                if i > 0 {
                    neighbours[i - 1][j] -= 1;
                    if j > 0 {
                        neighbours[i - 1][j - 1] -= 1;
                    }
                    if j < m - 1 {
                        neighbours[i - 1][j + 1] -= 1;
                    }
                }
                if i < n - 1 {
                    neighbours[i + 1][j] -= 1;
                    if j > 0 {
                        neighbours[i + 1][j - 1] -= 1;
                    }
                    if j < m - 1 {
                        neighbours[i + 1][j + 1] -= 1;
                    }
                }
            }
        }
    }
    removed
}

fn solve(input: &mut Vec<Vec<i32>>) -> (usize, usize) {
    let n = input.len();
    let m = input[0].len();
    let mut neighbours: Vec<Vec<i32>> = vec![vec![0; m]; n];
    for i in 0..n {
        for j in 0..m {
            if j > 0 {
                neighbours[i][j] += input[i][j - 1];
            }
            if j < m - 1 {
                neighbours[i][j] += input[i][j + 1];
            }
            if i > 0 {
                neighbours[i][j] += input[i - 1][j];
                if j > 0 {
                    neighbours[i][j] += input[i - 1][j - 1];
                }
                if j < m - 1 {
                    neighbours[i][j] += input[i - 1][j + 1];
                }
            }
            if i < n - 1 {
                neighbours[i][j] += input[i + 1][j];
                if j > 0 {
                    neighbours[i][j] += input[i + 1][j - 1];
                }
                if j < m - 1 {
                    neighbours[i][j] += input[i + 1][j + 1];
                }
            }
        }
    }

    let mut p1_total = 0;
    for i in 0..n {
        for j in 0..m {
            if input[i][j] > 0 && neighbours[i][j] < 4 {
                p1_total += 1;
            }
        }
    }

    let mut p2_total = 0;
    let mut prev = 1;
    while p2_total != prev {
        prev = p2_total;
        p2_total += remove(input, &mut neighbours, n, m);
    }

    (p1_total, p2_total)
}

fn main() {
    let mut input = parse_input();
    let (p1, p2) = solve(&mut input);
    println!("Part 1: {}", p1);
    println!("Part 1: {}", p2);
}
