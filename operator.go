package main

import "fmt"

func main() {
	var a int = 10
	var b int = 20
	fmt.Println("a + b =", a + b)
	fmt.Println("a - b =", a - b)
	fmt.Println("a * b =", a * b)
	fmt.Println("a / b =", a / b)
	fmt.Println("a % b =", a % b)
	a++
	fmt.Println("a++ =", a)
	b--
	fmt.Println("b-- =", b)


	fmt.Println(a > b)
	fmt.Println(a < b)
	
}
