#pragma once

#include "Car.h"

class Renault : public Car{
public:
    Renault();
    void SetFuelCapacity(double fc) override;
    void SetFuelConsumption(double fc) override;
    void SetAverageSpeed(Weather weather, double speed) override;
    double GetFuelCapacity() const override;
    double GetFuelConsumption() const override;
    double GetAverageSpeed(Weather weather) const override;
    const char* GetName() const override;
};