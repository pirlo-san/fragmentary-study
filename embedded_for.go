package main

import "fmt"

func main() {
	var start int = 2
	var end   int = 100

	for value := start; value <= end; value++ {
		//fmt.Printf("%d ", value)
		var i int
		for i = 2; i < value; i++ {
			if value %i == 0 {
				break
			}
		}

		if i == value {
			fmt.Printf("%d是素数\n", value)
		}
	}
}
