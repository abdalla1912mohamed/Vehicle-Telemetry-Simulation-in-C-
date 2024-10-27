#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H 

#include "Sensor.hpp"

/**
 * @class TemperatureSensor
 * @brief Represents a temperature sensor that inherits from the Sensor base class.
 *
 * The TemperatureSensor class simulates a physical temperature sensor. It provides
 * functionalities for obtaining temperature readings, attaching/detaching ECUs,
 * and notifying subscribed ECUs about updates.
 */
class TemperatureSensor : public Sensor {
public:
    /**
     * @brief Default constructor for the TemperatureSensor class.
     */
    TemperatureSensor();

    /**
     * @brief Destructor for the TemperatureSensor class.
     */
    ~TemperatureSensor();

    /**
     * @brief Retrieves the unique sensor ID.
     * @return The ID of the sensor.
     */
    int getSensorID() const override;

    /**
     * @brief Retrieves the temperature data.
     * @return The current temperature reading.
     */
    double GetSensorData() override; 

    /**
     * @brief Reads the temperature sensor data by generating a random value.
     */
    void sensorRead() override; 

    /**
     * @brief Retrieves the count of existing temperature sensors.
     * @return The number of temperature sensors created.
     */
    int getSensorCount() const; 

    /**
     * @brief Prints information about the temperature sensor.
     */
    void PrintInfo() override;

    /**
     * @brief Retrieves the type of the sensor.
     * @return The type of the sensor as a string.
     */
    std::string getType() override; 

    /**
     * @brief Deleted copy constructor.
     */
    TemperatureSensor(const TemperatureSensor&) = delete;

    /**
     * @brief Deleted assignment operator.
     * @return A reference to the current instance.
     */
    TemperatureSensor& operator=(const TemperatureSensor&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    TemperatureSensor(TemperatureSensor&&) = delete; 

    /**
     * @brief Deleted move assignment operator.
     * @return A reference to the current instance.
     */
    TemperatureSensor& operator=(TemperatureSensor&&) = delete;  

    /**
     * @brief Attaches an ECU to the temperature sensor.
     * @param E A weak pointer to the ECU to be attached.
     */
    void AttachECU(std::weak_ptr<ECU> E) override; 

    /**
     * @brief Detaches an ECU from the temperature sensor.
     * @param E A weak pointer to the ECU to be detached.
     */
    void DeAttachECU(std::weak_ptr<ECU> E) override;  

    /**
     * @brief Updates the attached ECU with the latest sensor data.
     * @param E A weak pointer to the ECU to be updated.
     */
    void updateECU(std::weak_ptr<ECU> E) override; 

    /**
     * @brief Notifies all attached ECUs with the latest sensor data.
     */
    void NotifyAllECUs() override; 

    /**
     * @brief Retrieves the total number of temperature sensors created.
     * @return The total sensor count.
     */
    virtual int getTotalSensorsCount() override; 

private:
    double Temperature; ///< Current temperature value.
    static int T_Sensor_Count; ///< Static variable to track the number of TemperatureSensors created.
    const int Sensor_ID; ///< Unique sensor ID.
    
    /**
     * @brief Generates a random temperature reading.
     * @return A randomly generated temperature value.
     */
    double getTemperature();

    /**
     * @brief Generates random data for the temperature sensor.
     * @return A randomly generated double representing temperature.
     */
    double getRandomData() override; // Generates random data

    std::string type = "Temperature Sensor"; ///< Type of the sensor.
};

#endif // !TEMPERATURE_SENSOR_H
