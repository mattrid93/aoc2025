// Day 1

use std::fs;

const INPUT_FILE: &str = "../inputs/day01.txt";

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

fn solve_p1(input: &[i32]) -> u32 {
    input
        .iter()
        .fold((50, 0_u32), |(pos, zeros), &rotation| {
            let pos = (pos + rotation).rem_euclid(100);
            let zeros = zeros + u32::from(pos == 0);
            (pos, zeros)
        })
        .1
}

fn solve_p2(input: &[i32]) -> u32 {
    let mut pos: i32 = 50;
    let mut zeros: u32 = 0;
    for &rotation in input {
        let start = pos;
        pos += rotation;
        zeros += pos.div_euclid(100).abs() as u32;
        if rotation.is_negative() && start == 0 {
            zeros -= 1;
        }
        pos = pos.rem_euclid(100);
        if pos == 0 && rotation.is_negative() {
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
