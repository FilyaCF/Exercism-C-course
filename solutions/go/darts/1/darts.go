package darts

import "math"

func Score(x, y float64) int {
	radius := math.Sqrt(x*x + y*y)
	if radius > 10 {
		return 0
	} else if radius > 5 {
		return 1
	} else if radius > 1 {
		return 5
	} else {
		return 10
	}
}
