package collatzconjecture

import "errors"

func CollatzConjecture(n int) (steps int, err error) {
	err = nil
	if n < 1 {
		err = errors.New("n must be greater or equal than 1")
		return
	}
	for n != 1 {
		if n%2 == 1 {
			n = 3*n + 1
		} else {
			n /= 2
		}
		steps++
	}
	return
}
