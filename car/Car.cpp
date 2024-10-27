#include "Car.hpp" 
#include "../ECU/Adaptive_Cruise_Control_ECU.hpp"
#include "../logger/CarLogger.hpp"
#include "../ECU/DiagnosticsECU.hpp"
#include "../Sensors/RadarSensor.hpp"
#include "../Sensors/Sensor.hpp"
#include "../Sensors/SpeedSensor.hpp"
#include "../Sensors/TemperatureSensor.hpp"
#include <memory>
#include <algorithm> // For std::find_if

Car::Car(const std::string& model, const std::string& make)
    : model(model), make(make), Adaptive_MODE(false), 
      Car_Speed_Sensor(std::make_shared<SpeedSensor>()),
      Car_Temperature_Sensor(std::make_shared<TemperatureSensor>()),
      Car_Battery_Level_Sensor(std::make_shared<BatteryLevelSensor>()),
      Car_Radar_Sensor(std::make_shared<RadarSensor>()),
      Car_Adaptive_Cruise_Control_ECU(std::make_shared<Adaptive_Cruise_Control_ECU>()),
      Car_Diagnostic_ECU(std::make_shared<DiagnosticECU>())
{
    Logger::getInstance().log("A new " + make + " " + model + " is created");
    // Initialize the car with sensors and ECUs
    CarINIT();
}

void Car::CarINIT() {
    Logger::getInstance().log("Starting the Engine of " + make + " " + model + " vom vom vom");

    // Resize the Sensors vector to hold all default sensor types
    Sensors.resize(MAX_SENSOR_NUMBER); 

    // Directly assign sensors to the corresponding indices
    Sensors[(int)SensorTypes::SPEED_SENSOR] = Car_Speed_Sensor;
    Sensors[(int)SensorTypes::TEMPERATURE_SENSOR] = Car_Temperature_Sensor;
    Sensors[(int)SensorTypes::RADAR_SENSOR] = Car_Radar_Sensor;
    Sensors[(int)SensorTypes::BATTERY_LEVEL_SENSOR] = Car_Battery_Level_Sensor;

    ECUs.push_back(Car_Adaptive_Cruise_Control_ECU); 
    ECUs.push_back(Car_Diagnostic_ECU); 

    // Initialize car_info with default values and log them
    Car_info[SensorTypes::SPEED_SENSOR] = 0; 
    Logger::getInstance().log("Speed of " + make + " " + model + ": " + std::to_string(Car_info[SensorTypes::SPEED_SENSOR]));

    Car_info[SensorTypes::TEMPERATURE_SENSOR] = 25; 
    Logger::getInstance().log("Temperature of " + make + " " + model + ": " + std::to_string(Car_info[SensorTypes::TEMPERATURE_SENSOR]));

    Car_info[SensorTypes::RADAR_SENSOR] = 0; 
    Logger::getInstance().log("Radar reading of " + make + " " + model + ": " + std::to_string(Car_info[SensorTypes::RADAR_SENSOR]));

    Car_info[SensorTypes::BATTERY_LEVEL_SENSOR] = 100; 
    Logger::getInstance().log("Battery level of " + make + " " + model + ": 100%");
}

void Car::UpdateSensorsData() {
    // Update sensor data
    Car_info[SensorTypes::SPEED_SENSOR] = Car_Speed_Sensor->GetSensorData(); 
    Car_info[SensorTypes::TEMPERATURE_SENSOR] = Car_Temperature_Sensor->GetSensorData(); 
    Car_info[SensorTypes::RADAR_SENSOR] = Car_Radar_Sensor->GetSensorData(); 
    Car_info[SensorTypes::BATTERY_LEVEL_SENSOR] = Car_Battery_Level_Sensor->GetSensorData(); 

    // Log the updated sensor values
    Logger::getInstance().log("Updated sensor data for " + make + " " + model + ": " +
        "Speed: " + std::to_string(Car_info[SensorTypes::SPEED_SENSOR]) + ", " +
        "Temperature: " + std::to_string(Car_info[SensorTypes::TEMPERATURE_SENSOR]) + ", " +
        "Radar: " + std::to_string(Car_info[SensorTypes::RADAR_SENSOR]) + ", " +
        "Battery Level: " + std::to_string(Car_info[SensorTypes::BATTERY_LEVEL_SENSOR]) + "%");
}

Car::~Car() {
     //Logger::getInstance().log(make + " " + model + " car is destroyed"); 
}

void Car::ActivateSensor(std::shared_ptr<Sensor> S) {
    /**
     * @brief Activates a new sensor and adds it to the car's sensor list.
     * 
     * @param S A shared pointer to the sensor to be activated.
     */
    Sensors.push_back(S); 
    Logger::getInstance().log("New Activated sensor: " + S->getType()); // Log sensor activation
}

void Car::ActivateECU(std::shared_ptr<ECU> E) {
    /**
     * @brief Activates a new ECU and adds it to the car's ECU list.
     * 
     * @param E A shared pointer to the ECU to be activated.
     */
    ECUs.push_back(E); 
    Logger::getInstance().log("New Activated ECU: " + E->getName()); // Log ECU activation
}

void Car::setAdaptiveMode(bool mode) {
    /**
     * @brief Sets the adaptive cruise control mode and triggers its function if enabled.
     * 
     * @param mode A boolean indicating whether to enable or disable the adaptive mode.
     */
    Adaptive_MODE = mode; // Set adaptive mode first
    Logger::getInstance().log("Setting adaptive mode to " + std::string(mode ? "enabled" : "disabled")); // Log the new state

    for (auto& E : ECUs) {
        if (E->getName() == "Adaptive Cruise Control ECU") {
            E->PerformFunction(*this); 
            Logger::getInstance().log("Performing function for Adaptive Cruise Control ECU"); // Log function execution
        }
    }
}

void Car::DisplayStatus() {
    /**
     * @brief Displays the current status of the car, including speed, temperature, battery level, radar status, and adaptive mode.
     */
    if(Car_info[SensorTypes::SPEED_SENSOR] > MAX_SPEED) {
        Logger::getInstance().log("Speed Exceeded please SLOW DOWN"); 
    } else {
        Logger::getInstance().log("Speed is within the allowed Range"); 
    }

    if(Car_info[SensorTypes::TEMPERATURE_SENSOR] > MAX_TEMPERATURE) {
        Logger::getInstance().log("Car is overheating please stop"); 
    } else {
        Logger::getInstance().log("Temperature is within the allowed Range"); 
    }

    if(Car_info[SensorTypes::BATTERY_LEVEL_SENSOR] < LOW_BATTERY) {
        Logger::getInstance().log("LOW BATTERY PLEASE GO TO THE NEAREST CHARGING STATION"); 
    } else {
        Logger::getInstance().log("Battery is Good"); 
    }

    if(Car_info[SensorTypes::RADAR_SENSOR] < SAFE_RADAR_DISTANCE) {
        Logger::getInstance().log("Collision is predicted please Slow down"); 
    } else {
        Logger::getInstance().log("NO collision Threats"); 
    }

    if(Adaptive_MODE == true) {
        Logger::getInstance().log("CRUISE CONTROL IS ON"); 
    } else {
        Logger::getInstance().log("CRUISE CONTROL IS OFF"); 
    }
}

bool Car::getAdaptiveMode() {
    /**
     * @brief Retrieves the current state of the adaptive cruise control mode.
     * 
     * @return bool True if adaptive mode is active, false otherwise.
     */
    return Adaptive_MODE; 
}

void Car::StartDiagonisticTool() const {
    /**
     * @brief Starts the diagnostic tool for the car, attaching all sensors to the diagnostic ECU.
     */
    for(auto s : Sensors) {
        Car_Diagnostic_ECU->AttachSensor(s); 
        s->AttachECU(Car_Diagnostic_ECU); 
    }
    
    Car_Diagnostic_ECU->PerformFunction(*this); 
}
