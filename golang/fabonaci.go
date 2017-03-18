package main

import "fmt"

func main() {
	var i uint = 0

	for ; i < 10; i++ {
		fmt.Printf("%d ", fabonaci(i))
	}
	fmt.Println()
}

func fabonaci(i uint) uint {
	if i < 2 {
		return i
	}

	return fabonaci(i - 1) + fabonaci(i - 2)
}
