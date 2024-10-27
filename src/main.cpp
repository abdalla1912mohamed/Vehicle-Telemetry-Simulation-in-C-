#include"../car/Car.hpp" 
#include "../logger/CarLogger.hpp" 
#include"../Sensors/Sensor.hpp"
#include"../ECU/ECU.hpp" 
#include<thread> 
#include<chrono> 


int main() {
    std::shared_ptr<Car> c = std::make_shared<Car>("rio", "kia");
    c->CarINIT();
    c->setAdaptiveMode(true);
    c->StartDiagonisticTool();
    c->DisplayStatus();
    
    while (true) {
        c->UpdateSensorsData();
        c->StartDiagonisticTool();
        c->DisplayStatus();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
// add a log to file 
