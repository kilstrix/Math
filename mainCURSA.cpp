#define _CRT_SECURE_NO_WARNINGS

#include "Circuit.h"
#include "Renault.h"
#include "Bugatti.h"

#include <iostream>

int main()
{
	Circuit c;
	c.SetLength(200);
	c.SetWeather(Weather::Sunny);
	c.AddCar(new Renault());
	c.AddCar(new Bugatti());
	//c.AddCar(new Seat());
	//c.AddCar(new Fiat());
	//c.AddCar(new RangeRover());
	c.Race();
	c.ShowFinalRanks(); // it will print the time each car needed to finish the circuit sorted from the fastest car to the slowest.
	c.ShowWhoDidNotFinish(); // it is possible that some cars don't have enough fuel to finish the circuit
	return 0;
}
