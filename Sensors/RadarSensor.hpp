#ifndef  RADAR_SENSOR_H
#define RADAR_SENSOR_H 

#include "Sensor.hpp"

/**
 * @class RadarSensor
 * @brief Represents a radar sensor that inherits from the Sensor class.
 *
 * This class is responsible for generating random radar data and
 * notifying subscribed ECUs (Electronic Control Units) with the sensor data.
 */
class RadarSensor : public Sensor {
public:
    /**
     * @brief Default constructor for the RadarSensor class.
     */
    RadarSensor();

    /**
     * @brief Destructor for the RadarSensor class.
     */
    ~RadarSensor();

    /**
     * @brief Gets the unique identifier for the sensor.
     * @return The sensor ID.
     */
    int getSensorID() const;

    /**
     * @brief Gets the sensor data by generating a new radar value.
     * @return The radar sensor data.
     */
    double GetSensorData() override;  // getter of the Radar calling get Radar 

    /**
     * @brief Reads the sensor data by generating a random value.
     */
    void sensorRead() override;  // setter but with a random value

    /**
     * @brief Gets the count of Radar sensors.
     * @return The count of Radar sensors.
     */
    int getSensorCount() const;

    /**
     * @brief Prints information about the radar sensor.
     */
    void PrintInfo() override;

    /**
     * @brief Gets the type of the sensor.
     * @return The sensor type as a string.
     */
    std::string getType() override;

    // Delete copy and move constructors and assignment operators
    RadarSensor(const RadarSensor&) = delete; //delete copy constructor 
    RadarSensor& operator=(const RadarSensor&) = delete; // delete the assignment operator
    RadarSensor(RadarSensor&&) = delete; // delete the move constructor
    RadarSensor& operator=(RadarSensor&&) = delete; // delete the move assignment operator

    /**
     * @brief Attaches an ECU to the radar sensor.
     * @param E Weak pointer to the ECU to attach.
     */
    void AttachECU(std::weak_ptr<ECU> E) override;

    /**
     * @brief Detaches an ECU from the radar sensor.
     * @param E Weak pointer to the ECU to detach.
     */
    void DeAttachECU(std::weak_ptr<ECU> E) override;

    /**
     * @brief Updates the attached ECU with the current sensor data.
     * @param E Weak pointer to the ECU to update.
     */
    void updateECU(std::weak_ptr<ECU> E) override;

    /**
     * @brief Notifies all subscribed ECUs with the current sensor data.
     */
    void NotifyAllECUs() override;

    /**
     * @brief Gets the total count of radar sensors.
     * @return The total number of radar sensors.
     */
    virtual int getTotalSensorsCount() override;

private:
    double Radar;                  ///< Current radar value.
    static int R_sensor_count;     ///< Static count of radar sensors.
    const int Sensor_ID;           ///< Unique identifier for the sensor.
    
    /**
     * @brief Generates random radar data.
     * @return The generated random radar data.
     */
    double getRandomData() override; // generate random data

    std::string type = "Radar Sensor"; ///< Type of the sensor.
};

#endif // !RADAR_SENSOR_H
