#include "RadarSensor.hpp"
#include <random>

/// Static member to keep track of the number of RadarSensor instances.
int RadarSensor::R_sensor_count = 0;

/// Random engine for generating random radar data.
std::default_random_engine er(std::chrono::system_clock::now().time_since_epoch().count());
/// Distribution range for radar data.
std::uniform_real_distribution<double> unifr(0, 50);

/**
 * @brief Destructor for RadarSensor.
 * Decreases the sensor count and logs the destruction of the sensor.
 */
RadarSensor::~RadarSensor() {
    R_sensor_count--;
    Sensor::total_sensor_count--; // shared variable may add a mutex or do an atomic operation

    std::ostringstream oss;
    oss << "Sensor of type " << type << " & ID = " << Sensor_ID 
        << " is destroyed. Remaining count is " << R_sensor_count;
    Logger::getInstance().log(oss.str());
}

/**
 * @brief Gets the type of the radar sensor.
 * @return The type of the sensor as a string.
 */
std::string RadarSensor::getType() {
    return type;
}

/**
 * @brief Gets the sensor ID.
 * @return The ID of the sensor.
 */
int RadarSensor::getSensorID() const {
    return Sensor_ID;
}

/**
 * @brief Gets the current count of RadarSensor instances.
 * @return The number of active RadarSensor instances.
 */
int RadarSensor::getSensorCount() const {
    return R_sensor_count;
}

/**
 * @brief Reads data from the sensor by generating random values.
 */
void RadarSensor::sensorRead() {
    getRandomData(); // call the random generator to randomize a Radar and update it
}

/**
 * @brief Generates random radar data.
 * @return The generated random radar data.
 */
double RadarSensor::getRandomData() {
    double randomRadar = unifr(er);
    this->Radar = randomRadar; // update the current Radar
    return randomRadar;
}

/**
 * @brief Retrieves the current sensor data after reading it.
 * @return The current radar sensor data.
 */
double RadarSensor::GetSensorData() {
    sensorRead();
    return Radar;
}

/**
 * @brief Logs information about the creation of the sensor.
 */
void RadarSensor::PrintInfo() {
    std::ostringstream oss;
    oss << "New sensor is created. Sensor Type: " << getType() 
        << ", Sensor ID: " << getSensorID() 
        << ", Radar Sensor Count: " << getSensorCount();
    Logger::getInstance().log(oss.str());
}

/**
 * @brief Constructs a new RadarSensor and increments the sensor count.
 */
RadarSensor::RadarSensor() : Sensor_ID(++R_sensor_count), Radar(0.0) {
    PrintInfo();
    Sensor::total_sensor_count++;
}

/**
 * @brief Attaches a new ECU to the radar sensor.
 * @param Ecu A weak pointer to the ECU to be attached.
 */
void RadarSensor::AttachECU(std::weak_ptr<ECU> Ecu) {
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
 * @brief Detaches an ECU from the radar sensor.
 * @param Ecu A weak pointer to the ECU to be detached.
 */
void RadarSensor::DeAttachECU(std::weak_ptr<ECU> Ecu) {
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
 * @brief Updates the ECU with the latest sensor data.
 * @param E A weak pointer to the ECU to be updated.
 */
void RadarSensor::updateECU(std::weak_ptr<ECU> E) {
    if (std::shared_ptr<ECU> e = E.lock()) {
        e->Recent_Sensory_Data[int(SensorTypes::RADAR_SENSOR)][Sensor_ID] = Radar;

        std::ostringstream oss;
        oss << "Updated  ECU : "<<e->getName()<<"  with Sensor type " << type<< " ID : " << Sensor_ID ;
        Logger::getInstance().log(oss.str());
    } else {
        Logger::getInstance().log("ECU object no longer exists.");
    }
}

/**
 * @brief Notifies all subscribed ECUs with the latest sensor data.
 */
void RadarSensor::NotifyAllECUs() {
    for (const auto& s : Subscribed_ECUs) {
        updateECU(s);  // update all the list of the subscribed ECUs
    }
}

/**
 * @brief Gets the total number of sensors created.
 * @return The total number of sensors.
 */
int RadarSensor::getTotalSensorsCount(){
    return Sensor::total_sensor_count; 
}
