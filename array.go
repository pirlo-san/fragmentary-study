package main

import "fmt"

func main() {
	var array = [5]int{1, 3, 5, 7, 9}
	fmt.Println(array)

	var array2 = [3][4]int{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
	}

	var i, j int
	for i = 0; i < 3; i++ {
		for j = 0; j < 4; j++ {
			fmt.Printf("Element[%d][%d] = %d\n", i, j, array2[i][j])
		}
	}
}
