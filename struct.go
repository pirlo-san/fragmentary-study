package main

import (
	"fmt"
)

type Book struct {
	title   string
	author  string
	subject string
	id	int
}

func main() {
	var book1 Book
	book1.title = "Design Patterns"
	book1.author = "Gang Four"
	book1.subject = "CS"
	book1.id = 1001
	print_book(&book1)
}

func print_book(book *Book) {
	fmt.Printf("Title:   %s\n", book.title)
	fmt.Printf("Author:  %s\n", book.author)
	fmt.Printf("Subject: %s\n", book.subject)
	fmt.Printf("Id:      %d\n", book.id)
	fmt.Println()
}
