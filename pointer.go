package main

import "fmt"

func main() {
	var ival int = 100
	ptr1 := &ival
	fmt.Println(ival, ptr1, *ptr1)
	ptr2 := ptr1
	fmt.Println(ival, ptr1, *ptr1, ptr2, *ptr2)
	*ptr2 = 200	
	fmt.Println(ival, ptr1, *ptr1, ptr2, *ptr2)
}
