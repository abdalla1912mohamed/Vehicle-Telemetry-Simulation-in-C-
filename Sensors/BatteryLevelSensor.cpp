#include "BatteryLevelSensor.hpp" 
#include "Sensor.hpp"
#include <random>

int BatteryLevelSensor::BL_Sensor_Count = 0;
std::default_random_engine eb(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<double> unifb(0, 100);

BatteryLevelSensor::~BatteryLevelSensor() {
    BL_Sensor_Count--;
    Sensor::total_sensor_count--; // Shared variable may add a mutex or do an atomic operation

    std::ostringstream oss;
    oss << "Sensor of type " << type << " & ID = " << Sensor_ID 
        << " is destroyed. Remaining count is " << BL_Sensor_Count;
    Logger::getInstance().log(oss.str());
}

/**
 * @brief Gets the type of the battery level sensor.
 * @return A string representing the sensor type.
 */
std::string BatteryLevelSensor::getType() {
    return type;  
}

/**
 * @brief Gets the unique sensor ID.
 * @return The sensor ID.
 */
int BatteryLevelSensor::getSensorID() const {
    return Sensor_ID;  
}

/**
 * @brief Gets the count of battery level sensors created.
 * @return The count of battery level sensors.
 */
int BatteryLevelSensor::getSensorCount() const {
    return BL_Sensor_Count; 
}

/**
 * @brief Reads the sensor data and updates the battery level.
 */
void BatteryLevelSensor::sensorRead() {
    getRandomData(); // Call the random generator to randomize a BatteryLevel and update it 
}

/**
 * @brief Generates random battery level data.
 * @return A random battery level value between 0 and 100.
 */
double BatteryLevelSensor::getRandomData() {
    double randomBatteryLevel = unifb(eb); 
    this->BatteryLevel = randomBatteryLevel; // Update the current BatteryLevel 
    return randomBatteryLevel; 
}

/**
 * @brief Retrieves the current battery level sensor data.
 * @return The current battery level value.
 */
double BatteryLevelSensor::GetSensorData() {
    sensorRead();                               
    return BatteryLevel; 
}

/**
 * @brief Prints information about the battery level sensor.
 */
void BatteryLevelSensor::PrintInfo() {
    std::ostringstream oss;
    oss << "New sensor is created. Sensor Type: " << getType() 
        << ", Sensor ID: " << getSensorID() 
        << ", Battery Level Sensor Count: " << getSensorCount();
    Logger::getInstance().log(oss.str());
}

/**
 * @brief Constructs a BatteryLevelSensor object.
 */
BatteryLevelSensor::BatteryLevelSensor() : Sensor_ID(++BL_Sensor_Count), BatteryLevel(0.0) {
    PrintInfo(); 
    Sensor::total_sensor_count++; 
}

/**
 * @brief Attaches an ECU to this sensor.
 * @param Ecu A weak pointer to the ECU to attach.
 */
void BatteryLevelSensor::AttachECU(std::weak_ptr<ECU> Ecu) {
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
 * @brief Detaches an ECU from this sensor.
 * @param Ecu A weak pointer to the ECU to detach.
 */
void BatteryLevelSensor::DeAttachECU(std::weak_ptr<ECU> Ecu) {
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
                ++it; // Move to the next iterator if the current one is expired
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
 * @brief Updates the attached ECU with the latest battery level data.
 * @param E A weak pointer to the ECU to update.
 */
void BatteryLevelSensor::updateECU(std::weak_ptr<ECU> E) {
    if (std::shared_ptr<ECU> e = E.lock()) {
        e->Recent_Sensory_Data[int(SensorTypes::BATTERY_LEVEL_SENSOR)][Sensor_ID] = BatteryLevel;

        std::ostringstream oss;
        oss << "Updated ECU: " << e->getName() << " with Sensor type " 
            << type << " ID: " << Sensor_ID;
        Logger::getInstance().log(oss.str());
    } else {
        Logger::getInstance().log("ECU object no longer exists.");
    }
}

/**
 * @brief Notifies all attached ECUs of the latest sensor data.
 */
void BatteryLevelSensor::NotifyAllECUs() {
    for (const auto& s : Subscribed_ECUs) {
        updateECU(s); // Update all the list of the subscribed ECUs 
    }
}

/**
 * @brief Gets the total count of all sensors.
 * @return The total count of sensors.
 */
int BatteryLevelSensor::getTotalSensorsCount() {
    return Sensor::total_sensor_count; 
}
