package main

import "fmt"

type DivideError struct {
	devidee int
	devider int
}

func (d *DivideError) Error() string {
	s := `
	Error, devider is 0:
	devidee: %d
	devider: 0`

	return fmt.Sprintf(s, d.devidee)
}

func Divide(varDividee int, varDivider int) (result float32, errmsg string) {
	if varDivider == 0 {
		d := DivideError {
			devidee: varDividee,
			devider: varDivider,
		}
		errmsg = d.Error()
		return
	}

	return float32(varDividee) / float32(varDivider), ""
}

func main() {
	result, errmsg := Divide(17, 5)
	fmt.Println(result, errmsg)

	result, errmsg = Divide(17, 0)
	fmt.Println(result, errmsg)

}
