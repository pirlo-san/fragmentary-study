package main

import (
	"fmt"
)

func main() {
	var c Circle
	c.radius = 10.0
	fmt.Println(c.getArea())
}

type Circle struct {
	radius float64
}

func (c Circle) getArea() float64 {
	return 3.14 * c.radius * c.radius
}
