package main

import (
	"fmt"
)

func main() {
	var a, b int = 10, 20
	fmt.Printf("Before swap: a = %d, b = %d\n", a, b)
	swap(&a, &b)
	fmt.Printf("After  swap: a = %d, b = %d\n", a, b)
}


func swap(ptr1 *int, ptr2 *int) {
	var temp int = *ptr1

	*ptr1 = *ptr2
	*ptr2 = temp
}
