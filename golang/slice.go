package main

import (
	"fmt"
)

func main() {
	var s1 []int
	print_slice(s1)

	s1 = append(s1, 0)
	print_slice(s1)

	s1 = append(s1, 1)
	print_slice(s1)

	s1 = append(s1, 2, 3, 4)
	print_slice(s1)

	s11 := make([]int, len(s1), cap(s1) * 2)
	print_slice(s11)

	copy(s11, s1)
	print_slice(s1)

	s1 = make([]int, 3)
	print_slice(s1)

	s2 := []int {1, 2, 3}
	print_slice(s2)

	s3 := s2[1:2]
	print_slice(s3)

	s4 := s2[2:]
	print_slice(s4)

	s5 := s2[:3]
	print_slice(s5)
}

func print_slice(s []int) {
	fmt.Println(s)
	fmt.Printf("len: %d, cap = %d\n", len(s), cap(s))
	fmt.Println()
}
