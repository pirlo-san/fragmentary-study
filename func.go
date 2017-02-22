package main

import "fmt"
import "math"

func main() {
	var a int = 10
	var b int = 20
	fmt.Printf("max(%d, %d) = %d\n", a, b, max(a, b))

	name, no := swap(22, "kaka")
	fmt.Printf("%s %d\n", name, no)

	i, j :=  100, 200
	fmt.Printf("%d %d\n", i, j)
	swap2(&i, &j)
	fmt.Printf("%d %d\n", i, j)

	GetSquareRoot := func(x float64) float64 {
		return math.Sqrt(x)
	}

	fmt.Println(GetSquareRoot(9))
	
	nextNumber := getSequence()
	fmt.Println(nextNumber())
	fmt.Println(nextNumber())
	fmt.Println(nextNumber())
	nextNumber1 := getSequence()
	fmt.Println(nextNumber1())
	fmt.Println(nextNumber1())
	fmt.Println(nextNumber1())
}

func max(a int, b int) int {
	if a > b {
		return a
	}

	return b
}

func swap(i int, s string) (string, int) {
	return s, i
}

func swap2(i *int, j *int) {
	var temp int = *i
	*i = *j
	*j = temp
}

func getSequence() func() int {
	i := 0
	return func() int {
		i++
		return i
	}
}
