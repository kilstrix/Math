#include "Bugatti.h"

Bugatti::Bugatti() {
    fuelCapacity = 60.188;
    fuelConsumption = 11.8;
    averageSpeed[static_cast<int>(Weather::Sunny)] = 500;
    averageSpeed[static_cast<int>(Weather::Rain)] = 500;
    averageSpeed[static_cast<int>(Weather::Snow)] = 500;
}

void Bugatti::SetFuelCapacity(double fc) {
    fuelCapacity = fc;
}
void Bugatti::SetFuelConsumption(double fc) {
    fuelConsumption = fc;
}
void Bugatti::SetAverageSpeed(Weather weather, double speed) {
    averageSpeed[static_cast<int>(weather)] = speed;
}
double Bugatti::GetFuelCapacity() const {
    return fuelCapacity;
}
double Bugatti::GetFuelConsumption() const {
    return fuelConsumption;
}
double Bugatti::GetAverageSpeed(Weather weather) const {
    return averageSpeed[static_cast<int>(weather)];
}
const char* Bugatti::GetName() const {
    return "Bugatti";
}