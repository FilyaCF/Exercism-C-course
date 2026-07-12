// Package weather describes weather.
package weather

var (
	// CurrentCondition describes CurrentCondition.
	CurrentCondition string
	// CurrentLocation describes CurrentLocation.
	CurrentLocation string
)

// Forecast made smth.
func Forecast(city, condition string) string {
	CurrentLocation, CurrentCondition = city, condition
	return CurrentLocation + " - current weather condition: " + CurrentCondition
}
