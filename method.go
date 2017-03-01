package main

import (
	"fmt"
)

func main() {
	var s Student
	s.name = "pirlo"
	s.age  = 38
	fmt.Println(s.getName())
	fmt.Println(s.getAge())
	name, age := s.getAll()
	fmt.Printf("name: %s, age: %d\n", name, age)
	s.printInfo()
}

type Student struct {
	name string
	age  int
}


func (s Student) getName() string {
	return s.name
}

func (s Student) getAge() int {
	return s.age
}

func (s Student) getAll() (string, int) {
	return s.name, s.age
}

func (s Student) printInfo() {
	fmt.Printf("name: %s, age: %d\n", s.name, s.age)
}
