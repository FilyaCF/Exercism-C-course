package cars

// CalculateWorkingCarsPerHour calculates how many working cars are
// produced by the assembly line every hour.
func CalculateWorkingCarsPerHour(productionRate int, successRate float64) (result float64) {
	result = float64(productionRate) * successRate / 100.0
	return
}

// CalculateWorkingCarsPerMinute calculates how many working cars are
// produced by the assembly line every minute.
func CalculateWorkingCarsPerMinute(productionRate int, successRate float64) (result int) {
	result = int(CalculateWorkingCarsPerHour(productionRate, successRate) / 60)
	return
}

// CalculateCost works out the cost of producing the given number of cars.
func CalculateCost(carsCount int) (cost uint) {
	cost = uint(carsCount)/10*95000 + uint(carsCount%10)*10000
	return
}
