package main

import "fmt"

const MAX int = 3

func main() {
	var a int = 10
	fmt.Printf("%x\n", &a)

	var ptr1 *int
	fmt.Println(ptr1)

	var arr = [MAX]int{10, 100, 200}
	var i int
	for i = 0; i < MAX; i++ {
		fmt.Printf("arr[%d] = %d\n", i, arr[i])
	}

	arr2 := [MAX]int {20, 30, 40}
	var ptrs [MAX] *int
	for i = 0; i < MAX; i++ {
		ptrs[i] = &arr2[i]
	}

	fmt.Println(ptrs)
	for i = 0; i < MAX; i++ {
		fmt.Println(ptrs[i])
		fmt.Println(*ptrs[i])
	}

	var ptr2 *[MAX] int
	ptr2 = &arr
	fmt.Println(ptr2)
	for i = 0; i < MAX; i++ {
		fmt.Println((*ptr2)[i])
	}

	var f float32 = 3.14159265
	var fptr *float32 = &f
	var fptrptr **float32 = &fptr
	fmt.Println(f)
	fmt.Println(fptr)
	fmt.Println(fptrptr)
	fmt.Println(*fptr)
	fmt.Println(*fptrptr)
	fmt.Println(**fptrptr)
}
