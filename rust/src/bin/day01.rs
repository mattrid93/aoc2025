// Day 1

use std::fs;

const INPUT_FILE: &str = "../inputs/day01.txt";

fn modulo(x: i32, y: i32) -> i32 {
    ((x % y) + y) % y
}

fn div(x: i32, y: i32) -> i32 {
    (x - modulo(x, y)) / y
}

fn parse_input() -> Vec<i32> {
    fn parse(input: &str) -> i32 {
        let (direction, remainder) = input.split_at(1);
        let mut amount = remainder.parse::<i32>().expect("Cannot parse input");
        if direction == "L" {
            amount *= -1;
        }
        amount
    }

    fs::read_to_string(INPUT_FILE)
        .expect("No input file")
        .lines()
        .map(parse)
        .collect()
}

fn solve_p1(input: &Vec<i32>) -> u32 {
    let mut pos: i32 = 50;
    let mut zeros: u32 = 0;
    for rotation in input {
        pos = modulo(pos + rotation, 100);
        if pos == 0 {
            zeros += 1;
        }
    }
    zeros
}

fn solve_p2(input: &Vec<i32>) -> u32 {
    let mut pos: i32 = 50;
    let mut zeros: u32 = 0;
    for rotation in input {
        let start = pos;
        pos += rotation;
        zeros += div(pos, 100).abs() as u32;
        if (*rotation < 0) && (start == 0) {
            zeros -= 1;
        }
        pos = modulo(pos, 100);
        if (pos == 0) && (*rotation < 0) {
            zeros += 1;
        }
    }
    zeros
}

fn main() {
    let input = parse_input();
    println!("Part 1: {}", solve_p1(&input));
    println!("Part 2: {}", solve_p2(&input));
}
