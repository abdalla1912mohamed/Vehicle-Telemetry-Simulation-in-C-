#include "TemperatureSensor.hpp"
#include <random>

// Initialize static member variable
int TemperatureSensor::T_Sensor_Count = 0;

// Random number generator setup
std::default_random_engine et(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<double> unift(0, 320);

/**
 * @brief Destructor for the TemperatureSensor class.
 * Decreases the sensor count and logs the destruction of the sensor.
 */
TemperatureSensor::~TemperatureSensor() {
    T_Sensor_Count--;
    Sensor::total_sensor_count--; // Shared variable may require a mutex or atomic operation

    std::ostringstream oss;
    oss << "Sensor of type " << type << " & ID = " << Sensor_ID 
        << " is destroyed. Remaining count is " << T_Sensor_Count;
    Logger::getInstance().log(oss.str());
}

/**
 * @brief Gets the type of the sensor.
 * @return A string representing the type of the sensor.
 */
std::string TemperatureSensor::getType() {
    return type;
}

/**
 * @brief Retrieves the unique sensor ID.
 * @return The ID of the sensor.
 */
int TemperatureSensor::getSensorID() const {
    return Sensor_ID;
}

/**
 * @brief Gets the count of existing temperature sensors.
 * @return The number of temperature sensors created.
 */
int TemperatureSensor::getSensorCount() const {
    return T_Sensor_Count;
}

/**
 * @brief Reads the temperature sensor data by generating a random value.
 */
void TemperatureSensor::sensorRead() {
    getRandomData(); // Call the random generator to randomize a Temperature and update it
}

/**
 * @brief Generates a random temperature reading.
 * @return A randomly generated temperature value.
 */
double TemperatureSensor::getRandomData() {
    double randomTemperature = unift(et);
    this->Temperature = randomTemperature; // Update the current Temperature
    return randomTemperature;
}

/**
 * @brief Gets the sensor data.
 * @return The current temperature reading.
 */
double TemperatureSensor::GetSensorData() {
    sensorRead();
    return Temperature;
}

/**
 * @brief Prints information about the temperature sensor.
 * Logs the sensor's type, ID, and count.
 */
void TemperatureSensor::PrintInfo() {
    std::ostringstream oss;
    oss << "New sensor is created. Sensor Type: " << getType() 
        << ", Sensor ID: " << getSensorID() 
        << ", Temperature Sensor Count: " << getSensorCount();
    Logger::getInstance().log(oss.str());
}

/**
 * @brief Default constructor for the TemperatureSensor class.
 * Initializes sensor ID and temperature, logs sensor creation, and updates the total sensor count.
 */
TemperatureSensor::TemperatureSensor() 
    : Sensor_ID(++T_Sensor_Count), Temperature(0.0) {
    PrintInfo();
    Sensor::total_sensor_count++;
}

/**
 * @brief Attaches an ECU to the temperature sensor.
 * @param Ecu A weak pointer to the ECU to be attached.
 */
void TemperatureSensor::AttachECU(std::weak_ptr<ECU> Ecu) {
    if (std::shared_ptr<ECU> sharedEcu = Ecu.lock()) {
        for (const auto& subscribedEcu : Subscribed_ECUs) {
            if (std::shared_ptr<ECU> existingEcu = subscribedEcu.lock()) {
                if (existingEcu->getID() == sharedEcu->getID()) {
                    std::ostringstream oss;
                    oss << "ECU " << existingEcu->getName() << " is already subscribed.";
                    Logger::getInstance().log(oss.str());
                    return;  // Exit if ECU is already subscribed
                }
            }
        }

        Subscribed_ECUs.push_back(Ecu);
        std::ostringstream oss;
        oss << "A new ECU: " << sharedEcu->getName() 
            << " subscribes to this " << this->getType() << " sensor.";
        Logger::getInstance().log(oss.str());
    } else {
        Logger::getInstance().log("ECU object no longer exists.");
    }
}

/**
 * @brief Detaches an ECU from the temperature sensor.
 * @param Ecu A weak pointer to the ECU to be detached.
 */
void TemperatureSensor::DeAttachECU(std::weak_ptr<ECU> Ecu) {
    if (std::shared_ptr<ECU> sharedECU = Ecu.lock()) {
        auto it = Subscribed_ECUs.begin();
        while (it != Subscribed_ECUs.end()) {
            if (std::shared_ptr<ECU> e = it->lock()) {
                if (e->getID() == sharedECU->getID() && e->getName() == sharedECU->getName()) {
                    it = Subscribed_ECUs.erase(it);  // Reassign the iterator after erasing
                    std::ostringstream oss;
                    oss << sharedECU->getName() << " was successfully detached.";
                    Logger::getInstance().log(oss.str());
                    return;
                } else {
                    ++it;
                }
            } else {
                Logger::getInstance().log("Couldn't detach (expired).");
                ++it;
            }
        }
        std::ostringstream oss;
        oss << "Could not find the ECU: " << sharedECU->getName() 
            << " with ID: " << sharedECU->getID() << " to detach.";
        Logger::getInstance().log(oss.str());
    } else {
        Logger::getInstance().log("The ECU reference has expired and cannot be locked.");
    }
}

/**
 * @brief Updates the attached ECU with the latest sensor data.
 * @param E A weak pointer to the ECU to be updated.
 */
void TemperatureSensor::updateECU(std::weak_ptr<ECU> E) {
    if (std::shared_ptr<ECU> e = E.lock()) {
        e->Recent_Sensory_Data[int(SensorTypes::TEMPERATURE_SENSOR)][Sensor_ID] = Temperature;

        std::ostringstream oss;
        oss << "Updated ECU: " << e->getName() << " with Sensor type " << type 
            << " ID: " << Sensor_ID;
        Logger::getInstance().log(oss.str());
    } else {
        Logger::getInstance().log("ECU object no longer exists.");
    }
}

/**
 * @brief Notifies all attached ECUs with the latest sensor data.
 */
void TemperatureSensor::NotifyAllECUs() {
    for (const auto& s : Subscribed_ECUs) {
        updateECU(s);  // Update all the list of the subscribed ECUs
    }
}

/**
 * @brief Gets the total number of sensors created.
 * @return The total sensor count from the base Sensor class.
 */
int TemperatureSensor::getTotalSensorsCount() {
    return Sensor::total_sensor_count; 
}
