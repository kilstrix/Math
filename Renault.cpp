#include "Renault.h"

Renault::Renault() {
    fuelCapacity = 60;
    fuelConsumption = 500000;
    averageSpeed[static_cast<int>(Weather::Sunny)] = 300;
    averageSpeed[static_cast<int>(Weather::Rain)] = 200;
    averageSpeed[static_cast<int>(Weather::Snow)] = 10;
}

void Renault::SetFuelCapacity(double fc) { 
    fuelCapacity = fc; 
}
void Renault::SetFuelConsumption(double fc) { 
    fuelConsumption = fc; 
}
void Renault::SetAverageSpeed(Weather weather, double speed) { 
    averageSpeed[static_cast<int>(weather)] = speed; 
}
double Renault::GetFuelCapacity() const { 
    return fuelCapacity; 
}
double Renault::GetFuelConsumption() const { 
    return fuelConsumption; 
}
double Renault::GetAverageSpeed(Weather weather) const { 
    return averageSpeed[static_cast<int>(weather)]; 
}
const char* Renault::GetName() const { 
    return "Renault"; 
}