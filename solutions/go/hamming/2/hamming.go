package hamming

import "fmt"

func Distance(a, b string) (int, error) {
	na := []rune(a)
	nb := []rune(b)
	if len(na) != len(nb) {
		return 0, fmt.Errorf("Different lengths")
	}
	n := len(na)
	var ans int
	for i := 0; i < n; i++ {
		if na[i] != nb[i] {
			ans++
		}
	}
	return ans, nil
}
