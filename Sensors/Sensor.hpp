#ifndef SENSOR_H  
#define SENSOR_H 

/**
 * @brief This interface defines the basic functionality for all sensor types, 
 * including speed, temperature, radar, and battery level.
 * 
 * @details It declares several virtual functions that must be overridden 
 * by derived sensor classes to implement specific behaviors.
 */

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <atomic>
#include "../logger/CarLogger.hpp"
#include "../ECU/ECU.hpp"  // Forward declaration of ECU class

/** 
 * @brief Observer interface for the Observer design pattern.
 * 
 * @details The sensor acts as an observer for a list of subscribed ECUs, 
 * notifying them of updates when sensor data changes.
 */
class SObserver {
public: 
    virtual ~SObserver() = default; 
    virtual void updateECU(std::weak_ptr<ECU> E) = 0;  /**< 

     * @brief Update a subscribed ECU with the latest sensor data.
     * 
     * @param E A weak pointer to the ECU that will be updated.
     */
     /** 
     * @brief Attach an ECU to the sensor for notifications.
     * 
     * @param E A weak pointer to the ECU to be attached.
     */
    virtual void AttachECU(std::weak_ptr<ECU> E) = 0; 

    /** 
     * @brief Detach an ECU from the sensor.
     * 
     * @param E A weak pointer to the ECU to be detached.
     */
    virtual void DeAttachECU(std::weak_ptr<ECU> E) = 0;  




}; 

/**
 * @enum SensorTypes
 * @brief Enumeration of different sensor types.
 */
enum class SensorTypes {
    SPEED_SENSOR = 0,        /**< Speed sensor type */
    TEMPERATURE_SENSOR = 1,  /**< Temperature sensor type */
    RADAR_SENSOR = 2,        /**< Radar sensor type */
    BATTERY_LEVEL_SENSOR = 3  /**< Battery level sensor type */
};

/**
 * @brief Abstract base class for all sensors.
 * 
 * @details This class implements the observer pattern and serves as a base 
 * for different sensor types, defining the common interface that they must 
 * adhere to.
 */
class Sensor : public SObserver {
public:
    Sensor() = default;

    /** 
     * @brief Generate random sensor data.
     * 
     * @return A double representing the random sensor data.
     */
    virtual double getRandomData() = 0; 

    /** 
     * @brief Mimic sensor reading by calling getRandomData().
     */
    virtual void sensorRead() = 0; 

    /** 
     * @brief Getter for the current sensor data value.
     * 
     * @return A double representing the current sensor data.
     */
    virtual double GetSensorData() = 0; 

    virtual ~Sensor() = default; // Rule of zero applied

    /** 
     * @brief Print information about the sensor.
     */
    virtual void PrintInfo() = 0;  

    /** 
     * @brief Attach an ECU to the sensor for notifications.
     * 
     * @param E A weak pointer to the ECU to be attached.
     */
    virtual void AttachECU(std::weak_ptr<ECU> E) = 0; 

    /** 
     * @brief Detach an ECU from the sensor.
     * 
     * @param E A weak pointer to the ECU to be detached.
     */
    virtual void DeAttachECU(std::weak_ptr<ECU> E) = 0;  

    /** 
     * @brief Update the specified ECU with the latest data.
     * 
     * @param E A weak pointer to the ECU to be updated.
     */
    virtual void updateECU(std::weak_ptr<ECU> E) = 0;  

    /** 
     * @brief Notify all subscribed ECUs of the data update.
     */
    virtual void NotifyAllECUs() = 0; 

    /** 
     * @brief Get the type of the sensor.
     * 
     * @return A string representing the sensor type.
     */
    virtual std::string getType() = 0;   

    /** 
     * @brief Get the unique identifier for the sensor.
     * 
     * @return An integer representing the sensor ID.
     */
    virtual int getSensorID() const = 0;    

    /** 
     * @brief Get the total count of sensor instances.
     * 
     * @return An integer representing the total number of sensors.
     */
    virtual int getTotalSensorsCount() = 0; 

protected: 
    std::vector<std::weak_ptr<ECU>> Subscribed_ECUs; /**< List of subscribed ECUs */
    static std::atomic<int> total_sensor_count; /**< Atomic count of total sensor instances */
};

#endif  
