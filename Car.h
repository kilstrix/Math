#pragma once

enum class Weather { Sunny, Rain, Snow };

class Car {
    public:
        double fuelCapacity;
        double fuelConsumption;
        double averageSpeed[3];
    
    public:
        virtual ~Car() {}
        virtual void SetFuelCapacity(double fc) = 0;
        virtual void SetFuelConsumption(double fc) = 0;
        virtual void SetAverageSpeed(Weather weather, double speed) = 0;
        virtual double GetFuelCapacity() const = 0;
        virtual double GetFuelConsumption() const = 0;
        virtual double GetAverageSpeed(Weather weather) const = 0;
        virtual const char* GetName() const = 0;
};
