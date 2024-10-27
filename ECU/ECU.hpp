#ifndef ECU_H 
#define  ECU_H

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map> 
#include "/home/abdalla/EmbeddedLINUX_Projects/CAR_ECU_CPP_PROJECT/logger/CarLogger.hpp"
#include <sstream>
#include <atomic>

// Base ECU class
#define Sensor_Types_Count 4 // Definition for the sensor types

class Car; 
class Sensor; 
class ECU; // Forward declaration

/**
 * @brief Abstract observer class for ECU.
 */
class EObserver {
public: 
    virtual ~EObserver() = default; 

       /**
     * @brief attach a sensor from the ECU.
     * 
     * @param s A shared pointer to the sensor to be attached.
     */
    
     virtual void AttachSensor(std::shared_ptr<Sensor> s) = 0;

    /**
     * @brief Detach a sensor from the ECU.
     * 
     * @param s A shared pointer to the sensor to be detached.
     */
    virtual void DeattachSensor(std::shared_ptr<Sensor> s) = 0;  
};
/**
 * @brief Abstract class representing an Electronic Control Unit (ECU).
 * 
 * The ECU class is responsible for interfacing with various sensors and performing
 * specific functions based on the data received from those sensors.
 */
class ECU : public EObserver {
public: 
    // Constructor
    ECU(); 

    // Destructor
    virtual ~ECU();  

    /**
     * @brief Get the unique identifier for the ECU.
     * 
     * @return int Unique ID of the ECU.
     */
    virtual int getID() const = 0;

    /**
     * @brief Get the current count of ECUs created.
     * 
     * @return int The count of ECUs.
     */
    static int getECUCount();

    /**
     * @brief Get the name of the ECU.
     * 
     * @return std::string The name of the ECU.
     */
    virtual std::string getName() const = 0;

    /**
     * @brief Perform the specific function of the ECU based on a given car state.
     * 
     * @param c The current state of the car.
     */
    virtual void PerformFunction(Car c) = 0;

    // Deleted copy constructor
    ECU(const ECU&) = delete; 

    // Deleted assignment operator
    ECU& operator=(const ECU&) = delete; 

    // Deleted move constructor
    ECU(ECU&&) = delete; 

    // Deleted move assignment operator
    ECU& operator=(ECU&&) = delete;  

    /**
     * @brief Attach a sensor to the ECU for data updates.
     * 
     * @param s A shared pointer to the sensor to be attached.
     */
    virtual void AttachSensor(std::shared_ptr<Sensor> s) = 0;

    /**
     * @brief Detach a sensor from the ECU.
     * 
     * @param s A shared pointer to the sensor to be detached.
     */
    virtual void DeattachSensor(std::shared_ptr<Sensor> s) = 0;  

    // The index of the vector is the sensor type
    std::vector<std::unordered_map<int, double>> Recent_Sensory_Data; 

protected:   
    int ECU_ID; /**< Unique identifier for the ECU. */
    static std::atomic<int> ECU_Count; /**< Static variable to keep track of the number of ECUs created. */
    std::string name; /**< Name of the ECU. */
    std::vector<std::shared_ptr<Sensor>> Subscribed_Sensors; /**< List of subscribed sensors. */
};

#endif // !ECU_H
