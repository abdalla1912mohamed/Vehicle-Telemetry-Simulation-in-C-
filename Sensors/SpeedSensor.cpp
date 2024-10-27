#include "SpeedSensor.hpp"
#include <memory>
#include <random>
#include <utility>
#include "../ECU/ECU.hpp"
#include "Sensor.hpp"

int SpeedSensor::S_Sensor_Count = 0;
std::atomic<int> Sensor::total_sensor_count{0};

std::default_random_engine es(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<double> unifs(0, 320);

SpeedSensor::~SpeedSensor() {
    S_Sensor_Count--;
    Sensor::total_sensor_count--;

    std::ostringstream oss;
    oss << "Sensor of type " << type << " & ID = " << Sensor_ID 
        << " is destroyed. Remaining count is " << S_Sensor_Count;
    Logger::getInstance().log(oss.str());
}

/**
 * @brief Gets the type of the sensor.
 * 
 * @return A string representing the type of the speed sensor.
 */
std::string SpeedSensor::getType() {
    return type;
}

/**
 * @brief Gets the ID of the sensor.
 * 
 * @return The unique identifier for the speed sensor.
 */
int SpeedSensor::getSensorID() const {
    return Sensor_ID;
}

/**
 * @brief Gets the count of speed sensors currently active.
 * 
 * @return The total count of speed sensors.
 */
int SpeedSensor::getSensorCount() const {
    return S_Sensor_Count;
}

/**
 * @brief Reads the sensor data by generating a random speed value.
 */
void SpeedSensor::sensorRead() {
    getRandomData();  // Call the random generator to randomize speed and update it
}

/**
 * @brief Generates a random speed value between 0 and 320.
 * 
 * @return A double representing the randomly generated speed.
 */
double SpeedSensor::getRandomData() {
    double randomSpeed = unifs(es);
    this->speed = randomSpeed;  // Update the current speed
    return randomSpeed;
}

/**
 * @brief Retrieves the current sensor data (speed).
 * 
 * @return A double representing the current speed value.
 */
double SpeedSensor::GetSensorData() {
    sensorRead();
    return speed; 
}

/**
 * @brief Logs information about the new speed sensor created.
 */
void SpeedSensor::PrintInfo() {
    std::ostringstream oss;
    oss << "New Sensor is created :: Sensor Type is " << getType()
        << " Sensor ID is " << getSensorID()
        << " Speed Sensor Count is " << getSensorCount();
    Logger::getInstance().log(oss.str());
}

/**
 * @brief Constructs a SpeedSensor object and initializes it.
 * 
 * @details Increments the sensor count and logs the sensor information.
 */
SpeedSensor::SpeedSensor() : Sensor_ID(++S_Sensor_Count), speed(0.0) {
    PrintInfo();
    Sensor::total_sensor_count++;  // Make it atomic
}

/**
 * @brief Attaches an ECU to the speed sensor for notifications.
 * 
 * @param Ecu A weak pointer to the ECU to be attached.
 */
void SpeedSensor::AttachECU(std::weak_ptr<ECU> Ecu) {
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
        oss << "A new ECU: " << sharedEcu->getName() << " subscribes to this " << this->getType() << " sensor.";
        Logger::getInstance().log(oss.str());
    } else {
        Logger::getInstance().log("ECU object no longer exists.");
    }
}

/**
 * @brief Detaches an ECU from the speed sensor.
 * 
 * @param Ecu A weak pointer to the ECU to be detached.
 */
void SpeedSensor::DeAttachECU(std::weak_ptr<ECU> Ecu) {
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
                Logger::getInstance().log("Couldn't detach ECU (expired).");
                ++it;  // Move to the next iterator if the current one is expired
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
 * @brief Updates the specified ECU with the latest speed data.
 * 
 * @param E A weak pointer to the ECU to be updated.
 */
void SpeedSensor::updateECU(std::weak_ptr<ECU> E) {
    if (std::shared_ptr<ECU> e = E.lock()) {
        e->Recent_Sensory_Data[int(SensorTypes::SPEED_SENSOR)][Sensor_ID] = speed;

        std::ostringstream oss;
        oss << "Updated ECU: " << e->getName() << " with Sensor type " << type << " ID: " << Sensor_ID;
        Logger::getInstance().log(oss.str());
    } else {
        Logger::getInstance().log("ECU object no longer exists.");
    }
}

/**
 * @brief Notifies all subscribed ECUs with the latest speed data.
 */
void SpeedSensor::NotifyAllECUs() {
    for (const auto& s : Subscribed_ECUs) {
        updateECU(s);  // Update all the list of the subscribed ECUs
    }
}

/**
 * @brief Gets the total count of sensor instances.
 * 
 * @return An integer representing the total number of sensors.
 */
int SpeedSensor::getTotalSensorsCount() {
    return Sensor::total_sensor_count; 
}
