fn hashsize(n: u64) -> u64
{
    1_u64 << n
}


fn hashmask(n: u64) -> u64
{
    hashsize(n) - 1_u64
}

fn ooat(arr: &[u64],bits: u64) -> u64
{
    let mut hash: u64 = 0;
    
    for i in 0..arr.len()
    {
        hash += arr[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    hash & hashmask(bits)
    
}

fn main()
{
   let snowflake = [1,2,3,4,5,6];
   let code = ooat(&snowflake,17);
   println!("{}",code);
   println!("{}",code % 100_000);
}