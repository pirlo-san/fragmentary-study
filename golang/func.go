package main

import (
	"fmt"
	"math"
)

func main() {
	fmt.Printf("max(10, 20) = %d\n", max(10, 20))
	name, no := swap(21, "pirlo")
	fmt.Printf("%s %d\n", name, no)

	var a int = 10;
	var b int = 20;
	fmt.Printf("before swap, a = %d, b = %d\n", a, b)
	swap2(&a, &b)
	fmt.Printf("before swap, a = %d, b = %d\n", a, b)

	getSquareRoot := func (x float64) float64 {
		return math.Sqrt(x)
	}

	fmt.Printf("getSquareRoot(9) = %f\n", getSquareRoot(9))

	nextNumber := getSequence()
	fmt.Println(nextNumber())
	fmt.Println(nextNumber())
	fmt.Println(nextNumber())
	nextNumber1 := getSequence()
	fmt.Println(nextNumber1())
	fmt.Println(nextNumber1())
}

func max(a, b int) int {
	var result int = b
	if (a > b) {
		result = a
	}
	return result
}

func swap(no int, name string) (string, int) {
	return name, no
}

func swap2(p1 *int, p2 *int) {
	var temp int = *p1
	*p1 = *p2
	*p2 = temp
}

func getSequence() func() int {
	var i int = 0
	return func() int {
		i++
		return i
	}
}
