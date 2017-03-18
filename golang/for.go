package main

import "fmt"

func main() {
	var end   int = 20
	var start int
	array := [6]int{2, 4, 6, 8}

	for start = 0; start < 10; start++ {
		fmt.Printf("value: %d\n", start)
	}

	for start < end {
		fmt.Printf("value: %d\n", start)
		start++
	}

	for i, x := range array {
		fmt.Printf("array[%d]: %d\n", i, x)
	}
}
