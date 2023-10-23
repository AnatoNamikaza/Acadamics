package Assigment2_Code

import (
    "fmt"
    "math"
)

// Function with parameters and return values
func add(a, b int) int {
    return a + b
}

// Struct definition
type Person struct {
    Name string
    Age  int
}

// Method for a struct
func (p Person) introduce() {
    fmt.Printf("Hi, I'm %s and I'm %d years old.\n", p.Name, p.Age)
}

func main() {
    // Variable declaration and initialization
    message := "Hello, Go!"
    fmt.Println(message)

    // Basic data types
    var integer int = 42
    var floatingPoint float64 = 3.1415
    var boolean bool = true
    fmt.Printf("Integer: %d, Floating Point: %f, Boolean: %t\n", integer, floatingPoint, boolean)

    // Arrays and Slices
    numbers := []int{1, 2, 3, 4, 5}
    fmt.Println("Slice:", numbers)

    // Control structures
    for i := 0; i < len(numbers); i++ {
        fmt.Printf("Index %d: %d\n", i, numbers[i])
    }

    // Function call
    result := add(10, 20)
    fmt.Println("Addition result:", result)

    // Conditional statement
    if result > 30 {
        fmt.Println("Result is greater than 30")
    } else {
        fmt.Println("Result is not greater than 30")
    }

    // Struct usage
    person := Person{Name: "Alice", Age: 30}
    person.introduce()

    // Math library
    squareRoot := math.Sqrt(16)
    fmt.Printf("Square root of 16: %f\n", squareRoot)
}
