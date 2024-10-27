#include "DiagnosticsECU.hpp"
#include "../logger/CarLogger.hpp"
#include "../Sensors/Sensor.hpp"
#include <memory>
#include "../car/Car.hpp"

/**
 * @brief Constructor for the DiagnosticECU class.
 * 
 * Initializes the Diagnostic ECU with its type and state.
 */
DiagnosticECU::DiagnosticECU() : type("Diagnostic ECU"), Diagnostic_ON(false) {
    // Initializing the name and type of the ECU  
    name = type; 
}

/**
 * @brief Destructor for the DiagnosticECU class.
 * 
 * Logs the destruction of the Diagnostic ECU.
 */
DiagnosticECU::~DiagnosticECU() {
    Logger::getInstance().log(name + " is destroyed");
}

/**
 * @brief Attaches a sensor to the Diagnostic ECU.
 * 
 * Checks if the sensor is already subscribed. If not, it subscribes the sensor
 * and logs the action.
 * 
 * @param s A shared pointer to the sensor to be attached.
 */
void DiagnosticECU::AttachSensor(std::shared_ptr<Sensor> s) {
    // Check if the sensor is already subscribed
    for (const auto& sensor : Subscribed_Sensors) {
        if (sensor->getSensorID() == s->getSensorID() && sensor->getType() == s->getType()) {
            Logger::getInstance().log(s->getType() + " of ID " + std::to_string(s->getSensorID()) + " is already subscribed.");
            return; // Exit if the sensor is already subscribed
        }
    }

    // Add the sensor if it is not already subscribed
    Subscribed_Sensors.push_back(s);
    Logger::getInstance().log("A new " + s->getType() + " is subscribed to Diagnostics.");
}

/**
 * @brief Detaches a sensor from the Diagnostic ECU.
 * 
 * Removes the specified sensor from the list of subscribed sensors and logs the action.
 * 
 * @param s A shared pointer to the sensor to be detached.
 */
void DiagnosticECU::DeattachSensor(std::shared_ptr<Sensor> s) {
    auto it = Subscribed_Sensors.begin();
    while (it != Subscribed_Sensors.end()) {
        if ((*it)->getSensorID() == s->getSensorID() && (*it)->getType() == s->getType()) {
            it = Subscribed_Sensors.erase(it);  // Erase and update iterator
            Logger::getInstance().log(s->getType() + " of ID " + std::to_string(s->getSensorID()) + " is erased successfully from Diagnostics.");
            return; // Return after successful deletion
        } else {
            ++it; // Move to the next sensor
        }
    }

    Logger::getInstance().log("Couldn't detach the sensor from Diagnostics.");
}

/**
 * @brief Performs the primary function of the Diagnostic ECU.
 * 
 * Activates diagnostic mode, updates the sensors, and logs the current data.
 * 
 * @param c The car instance to perform the function on.
 */
void DiagnosticECU::PerformFunction(Car c) {
    Logger::getInstance().log("Diagnostics MODE is ON");
    Diagnostic_ON = true;
    update(); 
    c.UpdateSensorsData(); // Update and log all the car sensory data 
}

/**
 * @brief Checks if the Diagnostic ECU is turned ON.
 * 
 * @return true if the ECU is ON, false otherwise.
 */
bool DiagnosticECU::IsON() {
    return Diagnostic_ON; 
}

/**
 * @brief Retrieves the ID of the Diagnostic ECU.
 * 
 * @return int The ID of the Diagnostic ECU.
 */
int DiagnosticECU::getID() const {
    return ECU_ID; 
}

/**
 * @brief Retrieves the name of the Diagnostic ECU.
 * 
 * @return std::string The name of the Diagnostic ECU.
 */
std::string DiagnosticECU::getName() const {
    return name; 
}

/**
 * @brief Updates the state of the Diagnostic ECU by notifying all subscribed sensors.
 */
void DiagnosticECU::update() {
    for (auto s : Subscribed_Sensors) {
        s->NotifyAllECUs(); 
        // Notify all ECUs by updating their sensory data 
    }
}
