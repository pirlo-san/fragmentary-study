/*
	Exercise 5.16: Write a variadic version of strings.Join.
*/

package main

import (
	"fmt"
)

func main() {
	fmt.Println(vJoin("-"))
	fmt.Println(vJoin("-", "aaa"))
	fmt.Println(vJoin("-", "aaa", "bbb"))
}

func vJoin(sep string, ss ...string) string {

	var sepTmp string
	var sret string
	for _, s := range ss {
		sret += sepTmp + s
		sepTmp = sep
	}
	return sret
}
