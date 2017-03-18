package main

import "fmt"

func main() {
	var score int
	fmt.Print("please input the score:")
	fmt.Scanf("%d", &score)
	
	var grade string	
	switch score {
		case 90:
			grade = "A"
		case 80:
			grade = "B"
		case 70, 60:
			grade = "C"
		default:
			grade = "D"
	}

	switch grade {
		case "A":
			fmt.Println("excellent")
		case "B":
			fmt.Println("good")
		case "C":
			fmt.Println("not bad")
		case "D":
			fmt.Println("bad")
		default:
			fmt.Println("bad")
	}

	var i interface{}
	switch j := i.(type) {
		case nil:
			fmt.Printf("%T\n", j)
	}
}

