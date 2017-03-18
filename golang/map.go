package main

import (
	"fmt";
)

func main() {
	var m1 map[int]string
	print_map(m1)

	m2 := make(map[int]string)
	m2[3] = "maldini"
	m2[21] = "pirlo"
	m2[22] = "kaka"
	print_map(m2)

	for no := range m2 {
		fmt.Println(no, m2[no])
	}


	delete(m2, 22)
	print_map(m2)

	value, bexist := m2[3]
	fmt.Println(value, bexist)

	value, bexist = m2[21]
	fmt.Println(value, bexist)
}

func print_map(m map[int]string) {
	fmt.Println(m)
}
