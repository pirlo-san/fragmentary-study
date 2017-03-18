package main

import "fmt"

func main() {
	s := []int{1, 2, 3}
	s = append(s, 4, 5, 6)
	for idx, val := range s {
		fmt.Println(idx, val)
	}

	m := map[int]string {3: "maldini", 21: "pirlo", 22: "kaka"}
	for key, value := range m {
		fmt.Println(key, value)
	}
}
