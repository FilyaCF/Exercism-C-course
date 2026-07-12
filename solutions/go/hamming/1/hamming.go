package hamming

import "fmt"

func Distance(a, b string) (int, error) {
	if len(a) != len(b) {
		return 0, fmt.Errorf("Different lengths")
	}
	n := len(b)
	var ans int
	for i := 0; i < n; i++ {
		if a[i] != b[i] {
			ans++
		}
	}
	return ans, nil
}
