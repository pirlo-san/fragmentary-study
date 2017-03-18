package main

import "fmt"

type Phone interface {
	call(from string) string
}

type IPhone struct {
}

type Nokia struct {
}

func (iPhone IPhone) call(from string) string {
	fmt.Printf("call from %s\n", from)
	return "iPhone"
}

func (nokia Nokia) call(from string) string {
	fmt.Printf("call from %s\n", from)
	return "Nokia"
}

func main() {
	var phone Phone

	phone = new(IPhone)
	fmt.Println(phone.call("pirlo"))

	phone = new(Nokia)
	fmt.Println(phone.call("kaka"))
}
