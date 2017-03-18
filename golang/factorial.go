package main

import "fmt"

func main() {
	var i uint = 0

	for ; i < 10; i++ {
		fmt.Printf("Factorial of %d is %d\n", i, factorial(i))
	}
}

func factorial(n uint) uint {
	if n == 0 {
		return 1
	}

	return n * factorial(n - 1)
}
