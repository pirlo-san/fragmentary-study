package main

import "fmt"

const (
	FEMALE = iota
	MALE   = iota
	i      = 1 << iota
	j      = 2 << iota
	k
	l
)

func main() {
	fmt.Println(FEMALE, MALE, i, j, k, l)	
}
