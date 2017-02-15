package main

import "fmt"

var (
	ival int
	str  string
)

func main() {
	name, age, height := "pirlo", 30, 1.71
	fmt.Println("Hello, my name is", name, ", age is", age, ", and height is", height)
}
