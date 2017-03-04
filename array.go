package main

import "fmt"

func main() {
	var arr1 [5] int
	print_array(arr1)

	var arr2 = [5]int{1, 2, 3, 4, 5}
	print_array(arr2)

	var arr3 [3][4]int
	print_array2(arr3)

	var arr4 = [3][4]int{
		{1, 2, 3, 4}, 
		{5, 6, 7, 8}, 
		{9, 10, 11, 12},
	}
	print_array2(arr4)

	var arr5 = []int{1, 2, 3, 4, 5, 6, 7}
	print_array3(arr5, 7)

	reverse_array(&arr5)
	print_array3(arr5, 7)
}

func print_array(array [5]int) {
	var i int = 0
	for i = 0; i < 5; i++ {
		fmt.Printf("%d ", array[i])
	}
	fmt.Println("")
}

func print_array2(array [3][4]int) {
	var i, j int
	for i = 0; i < 3; i++ {
		for j = 0; j < 4; j++ {
			fmt.Printf("%d ", array[i][j])
		}
		fmt.Println("")
	}
	fmt.Println("")
}

func print_array3(arr []int, size int) {
	var i int
	for i = 0; i < size; i++ {
		fmt.Printf("%d ", arr[i])
	}
	fmt.Println("")
}

func reverse_array(arr *[]int) {
	var temp1 int 
	var temp2 int 
	var temp3 int 
	temp1 = (*arr)[0]
	temp2 = (*arr)[1]
	temp3 = (*arr)[2]
	(*arr)[0] = (*arr)[6]
	(*arr)[1] = (*arr)[5]
	(*arr)[2] = (*arr)[4]
	(*arr)[4] = temp3
	(*arr)[5] = temp2
	(*arr)[6] = temp1
	
}
