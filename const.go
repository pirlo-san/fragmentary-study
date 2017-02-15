package main

import "fmt"
import "unsafe"

const (
	RED = 0
	BLUE = 1
	GREEN = 2
)

const (
	a = "abc"
	b = len(a)
	c = unsafe.Sizeof(a)
)

func main() {
	const WIDTH int = 100
	const HEIGHT    = 200
	fmt.Println(WIDTH, HEIGHT, RED, BLUE, GREEN, a, b, c)
}
