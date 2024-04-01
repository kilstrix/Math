#include "Circuit.h"

#include <algorithm>
#include <iostream>

using namespace std;

void Circuit::SetLength(double l) { 
    length = l; 
}
void Circuit::SetWeather(Weather w) { 
    weather = w; 
}
void Circuit::AddCar(Car* car) { 
    cars.push_back(unique_ptr<Car>(car)); 
}

void Circuit::Race() {
    for (size_t i = 0; i < cars.size(); i++)
    {
        double speed = cars[i]->GetAverageSpeed(weather);
        double range = (cars[i]->GetFuelCapacity() / cars[i]->GetFuelConsumption()) * 100;
        double time = length / speed;
        if (range >= length)
        {
            finishingTimes.push_back(make_pair(time, cars[i].get()));
        }
        else
        {
            unfinishingTimes.push_back(make_pair(time, cars[i].get()));
        }
    }

    sort(finishingTimes.begin(), finishingTimes.end());
    sort(unfinishingTimes.begin(), unfinishingTimes.end());

    
    

}

void Circuit::ShowFinalRanks() {
    for (size_t i = 0; i < finishingTimes.size(); i++)
    {
        cout << finishingTimes[i].second->GetName() << " " << finishingTimes[i].first;
        cout << endl;
    }
    cout << endl;
}

void Circuit::ShowWhoDidNotFinish() {
    for (size_t i = 0; i < unfinishingTimes.size(); i++)
    {
        cout << unfinishingTimes[i].second->GetName();
        //cout << " " << finishingTimes[i].first;
        cout << endl;
    }
}