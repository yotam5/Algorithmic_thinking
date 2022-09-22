use std::io::stdin;

fn prefix_length(s1: &str, s2: &str) -> i64 {
    let mut i: i64 = 1;
    while s1.as_bytes()[(i - 1) as usize] == s2.as_bytes()[(i - 1) as usize] {
        i += 1;
    }
    i - 1
}

fn suffix_length(s1: &str, s2: &str) -> i64 {
    let mut i: i64 = (s1.len() - 1) as i64;
    while i >= 2 && s1.as_bytes()[i as usize] == s2.as_bytes()[(i - 1) as usize] {
        i -= 1;
    }
    (s1.len() as i64 - i) as i64
}

fn main() {
    let mut s1 = String::new();
    let mut s2 = String::new();
    stdin().read_line(&mut s1).unwrap();
    stdin().read_line(&mut s2).unwrap();
    let prefix = prefix_length(&s1, &s2);
    let suffix = suffix_length(&s1, &s2);

    let total = (prefix + 1) as i64 - (s1.len() as i64 - suffix as i64) as i64 + 1;
    println!("total: {}", &total);

    let total = total.abs();
    for i in 0..total {
        print!("{}", i + s1.len() as i64 - suffix as i64);
        if i < total - 1 {
            print!(" ");
        } else {
            println!();
        }
    }
}
