package main

import "fmt"

func main() {
	var ival int = 100
	var ptr1 *int = &ival
	fmt.Println(ival, ptr1, *ptr1)
	ptr2 := ptr1
	fmt.Println(ival, ptr1, *ptr1, ptr2, *ptr2)
	*ptr2 = 200	
	fmt.Println(ival, ptr1, *ptr1, ptr2, *ptr2)
	fmt.Printf("%T, %T, %T, %T\n", ival, ptr1, "abc", true)
}
