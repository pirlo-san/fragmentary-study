package main

import "fmt"

func main() {
	var a int = 10

loop:
	for a < 20 {
		if a == 15 {
			a++
			goto loop
		}

		fmt.Println(a)
		a++
	}
}
