
#[derive(Debug)]
struct Node {
    candy: i32,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

impl Node {
    fn new_house(candy: i32) -> Self {
        assert!(candy >= 0);
        Node {
            candy,
            left: None,
            right: None,
        }
    }

    fn new_nonhouse() -> Self {
        Node {
            candy: -1,
            left: None,
            right: None,
        }
    }
}

fn tree_candy(tree: &Box<Node>) -> i32 {
    if tree.left.is_none() && tree.right.is_none() {
        return tree.candy;
    }
    return tree_candy(tree.right.as_ref().unwrap()) + tree_candy(tree.left.as_ref().unwrap());
}

fn tree_solve(tree: &Box<Node>) {
    let candy = tree_candy(tree);
    let height = tree_heigh(tree);
    let num_streets = num_streets(tree) - height;
    println!("{} {}", &num_streets, &candy);
}

fn tree_heigh(tree: &Box<Node>) -> i32 {
    if tree.left.is_none() && tree.right.is_none() {
        return 0;
    }
    1 + std::cmp::max(
        tree_heigh(tree.left.as_ref().unwrap()),
        tree_heigh(tree.right.as_ref().unwrap()),
    )
}

fn num_streets(tree: &Box<Node>) -> i32 {
    if tree.left.is_none() && tree.right.is_none() {
        return 0;
    }
    return 4
        + num_streets(tree.left.as_ref().unwrap())
        + num_streets(tree.right.as_ref().unwrap());
}

fn read_tree_helper(line: &str, pos: &mut usize) -> Option<Box<Node>> {
    let mut tree = Box::new(Node::new_nonhouse());
    if line.as_bytes()[*pos] == b'(' {
        *pos += 1;
        tree.left = read_tree_helper(line, pos);
        *pos += 1;
        tree.right = read_tree_helper(line, pos);
        *pos += 1;
        return Some(tree);
    } else {
        let lb = line.as_bytes();
        tree.left = None;
        tree.right = None;

        let c_to_d = |pos: &usize| -> i32{
           (lb[*pos] as char).to_digit(10).unwrap() as i32
        };

        tree.candy = c_to_d(pos);
        *pos += 1;

        if lb.len() < *pos && 
            lb[*pos] != b')' && lb[*pos]!= b' ' {
                tree.candy = tree.candy * 10 + c_to_d(pos);
            }
        Some(tree)
    }
}

fn read_tree(line: &str) -> Box<Node> {
    let mut pos: usize = 0;
    read_tree_helper(line, &mut pos).unwrap()
}

fn main() {
    use std::io::stdin;
    
    for i in 0..5{
        let mut s = String::new();
        stdin().read_line(&mut s).unwrap();
        let tree = read_tree(&s);
        tree_solve(&tree);
    }   
}
