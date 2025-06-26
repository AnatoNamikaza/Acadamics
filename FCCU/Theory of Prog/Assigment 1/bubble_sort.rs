fn bubble_sort(arr: &mut Vec<i32>) {
    let n = arr.len();
    for _ in 0..n {
        for j in 0..n - 1 {
            if arr[j] > arr[j + 1] {
                arr.swap(j, j + 1);
            }
        }
    }
}

fn main() {
    let mut arr = vec![5, 3, 8, 4, 2];
    bubble_sort(&mut arr);
    println!("{:?}", arr);
}
