/*
	Exercise 5.15 Write variadic functions max and min, analogous to sum.
	What should these functions do when called with no arguments?
	Write variants that require at least one argument.
*/

package main

import (
	"fmt"
)

func main() {
	fmt.Println(max())
	fmt.Println(max(1))
	fmt.Println(max(1, 2))
	fmt.Println(max(1, 2, 3))

	//	fmt.Println(max1()) // compile error: not enough arguments in call to max1
	fmt.Println(max1(1))
	fmt.Println(max1(1, 2))
	fmt.Println(max1(1, 2, 3))

	fmt.Println(min())
	fmt.Println(min(1))
	fmt.Println(min(1, 2))
	fmt.Println(min(1, 2, 3))

	//	fmt.Println(min1()) // compile error: not enough arguments in call to min1
	fmt.Println(min1(1))
	fmt.Println(min1(1, 2))
	fmt.Println(min1(1, 2, 3))
}

func max(vals ...int) (int, error) {

	if len(vals) <= 0 {
		return 0, fmt.Errorf("max: at least one arg should be given")
	}

	mval := vals[0]
	for _, val := range vals[1:] {
		if val > mval {
			mval = val
		}
	}

	return mval, nil
}

func max1(val int, vals ...int) int {

	mval, err := max(vals...)
	if err != nil || val > mval {
		return val
	}

	return mval
}

func min(vals ...int) (int, error) {

	if len(vals) <= 0 {
		return 0, fmt.Errorf("min: at least one arg should be given")
	}

	mval := vals[0]
	for _, val := range vals[1:] {
		if val < mval {
			mval = val
		}
	}

	return mval, nil
}

func min1(val int, vals ...int) int {

	mval, err := min(vals...)
	if err != nil || val < mval {
		return val
	}

	return mval
}
