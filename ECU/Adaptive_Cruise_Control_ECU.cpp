#include "Adaptive_Cruise_Control_ECU.hpp"
#include "../logger/CarLogger.hpp"
#include "../Sensors/Sensor.hpp"
#include "../car/Car.hpp"

/**
 * @brief Constructs an Adaptive_Cruise_Control_ECU object.
 * 
 * Initializes the name and type of the ECU and sets the adaptive cruise control status to off.
 */
Adaptive_Cruise_Control_ECU::Adaptive_Cruise_Control_ECU() 
    : type("Adaptive Cruise Control ECU"), ADAPTIVE_ON(false) {
    name = type;  // initializing the name and type of the ECU  
}

/**
 * @brief Destructor for Adaptive_Cruise_Control_ECU.
 * 
 * Logs a message indicating the destruction of the ECU.
 */
Adaptive_Cruise_Control_ECU::~Adaptive_Cruise_Control_ECU() {
    Logger::getInstance().log(name + " is destroyed");
} 

/**
 * @brief Attaches a sensor to the adaptive cruise control ECU.
 * 
 * Checks if the sensor is already subscribed. If not, it adds the sensor
 * to the list of subscribed sensors and logs the action.
 * 
 * @param s A shared pointer to the sensor to attach.
 */
void Adaptive_Cruise_Control_ECU::AttachSensor(std::shared_ptr<Sensor> s) {
    // Check if the sensor is already subscribed
    for (const auto& sensor : Subscribed_Sensors) {
        if (sensor->getSensorID() == s->getSensorID() && sensor->getType() == s->getType()) {
            Logger::getInstance().log(s->getType() + " of ID " + std::to_string(s->getSensorID()) + " is already subscribed.");
            return; // Exit if the sensor is already subscribed
        }
    }

    // Add the sensor if it is not already subscribed
    Subscribed_Sensors.push_back(s);
    Logger::getInstance().log("A new " + s->getType() + " is subscribed.");
}

/**
 * @brief Detaches a sensor from the adaptive cruise control ECU.
 * 
 * Searches for the sensor in the list of subscribed sensors and removes it
 * if found. Logs the action.
 * 
 * @param s A shared pointer to the sensor to detach.
 */
void Adaptive_Cruise_Control_ECU::DeattachSensor(std::shared_ptr<Sensor> s) {
    auto it = Subscribed_Sensors.begin();
    while (it != Subscribed_Sensors.end()) {
        if ((*it)->getSensorID() == s->getSensorID() && (*it)->getType() == s->getType()) {
            it = Subscribed_Sensors.erase(it);  // Erase and update iterator
            Logger::getInstance().log(s->getType() + " of ID " + std::to_string(s->getSensorID()) + " is erased successfully.");
            return; // Return after successful deletion
        } else {
            ++it; // Move to the next sensor
        }
    }

    Logger::getInstance().log("Couldn't detach the sensor.");
}

/**
 * @brief Activates the adaptive cruise control functionality.
 * 
 * Logs the activation of the adaptive cruise control mode and sets the
 * status to on.
 * 
 * @param c The car object that the ECU is controlling.
 */
void Adaptive_Cruise_Control_ECU::PerformFunction(Car c) {
    Logger::getInstance().log("Adaptive Cruise Control MODE is ON"); 
    ADAPTIVE_ON = true; 
}

/**
 * @brief Checks if the adaptive cruise control is currently active.
 * 
 * @return True if the adaptive cruise control is on, false otherwise.
 */
bool Adaptive_Cruise_Control_ECU::IsON() {
    return ADAPTIVE_ON; 
}

/**
 * @brief Gets the ID of the adaptive cruise control ECU.
 * 
 * @return The ID of the ECU as an integer.
 */
int Adaptive_Cruise_Control_ECU::getID() const {
    return ECU_ID; 
}

/**
 * @brief Gets the name of the adaptive cruise control ECU.
 * 
 * @return The name of the ECU as a string.
 */
std::string Adaptive_Cruise_Control_ECU::getName() const {
    return name; 
}
