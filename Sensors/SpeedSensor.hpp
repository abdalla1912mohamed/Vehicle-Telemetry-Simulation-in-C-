#ifndef SPEED_SENSOR_H
#define SPEED_SENSOR_H 

#include "Sensor.hpp"
#include <memory>

/**
 * @brief Represents a speed sensor that derives from the Sensor interface.
 * 
 * @details This class implements the specific functionality for a speed sensor, 
 * including reading speed data and managing its subscribed ECUs.
 */
class SpeedSensor : public Sensor {
public:
    /**
     * @brief Constructs a SpeedSensor object.
     */
    SpeedSensor();

    /**
     * @brief Destroys the SpeedSensor object.
     */
    ~SpeedSensor();

    /** 
     * @brief Gets the unique identifier for the speed sensor.
     * 
     * @return An integer representing the sensor ID.
     */
    int getSensorID() const;

    /** 
     * @brief Retrieves the current speed sensor data.
     * 
     * @return A double representing the current speed.
     */
    double GetSensorData() override;

    /** 
     * @brief Mimics reading sensor data by generating a random speed value.
     */
    void sensorRead() override;

    /** 
     * @brief Retrieves the total count of speed sensors.
     * 
     * @return An integer representing the total number of speed sensors.
     */
    int getSensorCount() const;

    /** 
     * @brief Prints information about the speed sensor.
     */
    void PrintInfo() override;

    /** 
     * @brief Gets the type of the sensor.
     * 
     * @return A string representing the sensor type.
     */
    std::string getType() override;

    // Deleted copy constructor and assignment operator
    SpeedSensor(const SpeedSensor&) = delete; 
    SpeedSensor& operator=(const SpeedSensor&) = delete;

    // Deleted move constructor and assignment operator
    SpeedSensor(SpeedSensor&&) = delete; 
    SpeedSensor& operator=(SpeedSensor&&) = delete;  

    /** 
     * @brief Attaches an ECU to the speed sensor for notifications.
     * 
     * @param E A weak pointer to the ECU to be attached.
     */
    void AttachECU(std::weak_ptr<ECU> E) override;

    /** 
     * @brief Detaches an ECU from the speed sensor.
     * 
     * @param E A weak pointer to the ECU to be detached.
     */
    void DeAttachECU(std::weak_ptr<ECU> E) override;

    /** 
     * @brief Updates the specified ECU with the latest speed data.
     * 
     * @param E A weak pointer to the ECU to be updated.
     */
    void updateECU(std::weak_ptr<ECU> E) override;

    /** 
     * @brief Notifies all subscribed ECUs of the data update.
     */
    void NotifyAllECUs() override;

    /** 
     * @brief Gets the total count of sensor instances.
     * 
     * @return An integer representing the total number of sensors.
     */
    virtual int getTotalSensorsCount() override;

private:
    double speed;                     /**< Current speed value */
    static int S_Sensor_Count;       /**< Static count of speed sensors */
    const int Sensor_ID;             /**< Unique identifier for the sensor */
    
    /** 
     * @brief Generates a random speed value.
     * 
     * @return A double representing the randomly generated speed.
     */
    double getSpeed();

    /** 
     * @brief Generates random data for the speed sensor.
     * 
     * @return A double representing the random speed data.
     */
    double getRandomData() override; 

    std::string type = "Speed Sensor"; /**< Type of the sensor */
};

#endif // !SPEED_SENSOR_H
