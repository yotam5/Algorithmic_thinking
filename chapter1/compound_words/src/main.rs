use std::borrow::Borrow;

const NUMB_BITS: u64 = 17;

fn hashsize(n: u64) -> u64 {
    1_u64 << n
}

fn hashmask(n: u64) -> u64 {
    hashsize(n) - 1_u64
}

fn ooat(key_arr: &[u8], bits: u64) -> u64 {
    let mut hash = 5381;
    for i in 0..key_arr.len() {
        hash = ((hash << 5) + hash) + (key_arr[i] as u64);
    }

    hash % bits
}

#[derive(Debug)]
struct WordNode {
    word: String,
    next: Option<Box<WordNode>>,
}

fn in_hash_table(hash_table: &[Option<Box<WordNode>>], find: &[u8]) -> bool {
    let word_code = ooat(find, NUMB_BITS);
    let word_ptr = hash_table[word_code as usize].borrow();
    if word_ptr.is_none() {
        return false;
    }
    let mut pt = Some(word_ptr.as_ref().unwrap());

    loop {
        if pt.is_none() {
            break;
        }
        if pt.unwrap().word.as_bytes() == find {
            return true;
        }
        if pt.unwrap().next.is_some() {
            pt = pt.unwrap().next.as_ref();
        } else {
            pt = None;
        }
    }
    false
}

fn identify_compound_words(words: &[String], hash_table: &[Option<Box<WordNode>>]) {
    for word in words {
        for j in 1..(word.len()) {
            if in_hash_table(hash_table, &word.as_bytes()[..j])
                && in_hash_table(hash_table, &word.as_bytes()[j..])
            {
                println!("compund: {}", word);
            }
        }
    }
}

fn main() {
    let mut words: Vec<String> = Vec::new();
    let mut hash_table: Vec<Option<Box<WordNode>>> = Vec::with_capacity(NUMB_BITS as usize);

    for _ in 0..NUMB_BITS {
        hash_table.push(None);
    }

    let mut total = 0;

    for _ in 0..5 {
        let mut s = String::with_capacity(17);
        std::io::stdin().read_line(&mut s).unwrap();
        let _ = s.pop();
        let word_code = ooat(&s.as_bytes(), NUMB_BITS);
        let mw = Box::new(WordNode {
            next: None,
            word: s.clone(),
        });
        words.push(s);
        hash_table[word_code as usize] = Some(mw);
        total += 1;
    }
    identify_compound_words(&words, &hash_table);
    println!("{:?}", &hash_table);
}
