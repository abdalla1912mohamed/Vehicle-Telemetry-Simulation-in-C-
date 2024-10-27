#ifndef BatteryLevel_SENSOR_H
#define BatteryLevel_SENSOR_H

#include "Sensor.hpp"

/**
 * @class BatteryLevelSensor
 * @brief Represents a battery level sensor in a car system.
 *
 * The BatteryLevelSensor class inherits from the Sensor base class and
 * provides functionality to retrieve and manage battery level data.
 */
class BatteryLevelSensor : public Sensor {
public:
    /**
     * @brief Constructs a BatteryLevelSensor object.
     */
    BatteryLevelSensor();

    /**
     * @brief Destroys the BatteryLevelSensor object.
     */
    ~BatteryLevelSensor();

    /**
     * @brief Gets the unique sensor ID.
     * @return The sensor ID.
     */
    int getSensorID() const override;

    /**
     * @brief Retrieves the current battery level sensor data.
     * @return The battery level value.
     */
    double GetSensorData() override; // getter of the BatteryLevel calling get BatteryLevel

    /**
     * @brief Reads the sensor data.
     */
    void sensorRead() override; // setter but with a random value

    /**
     * @brief Gets the total count of battery level sensors.
     * @return The count of battery level sensors.
     */
    int getSensorCount() const;

    /**
     * @brief Prints information about the battery level sensor.
     */
    void PrintInfo() override;

    /**
     * @brief Gets the type of the sensor.
     * @return A string representing the sensor type.
     */
    std::string getType() override;

    // Deleted copy constructor
    BatteryLevelSensor(const BatteryLevelSensor&) = delete;

    // Deleted assignment operator
    BatteryLevelSensor& operator=(const BatteryLevelSensor&) = delete;

    // Deleted move constructor
    BatteryLevelSensor(BatteryLevelSensor&&) = delete;

    // Deleted move assignment operator
    BatteryLevelSensor& operator=(BatteryLevelSensor&&) = delete;

    /**
     * @brief Attaches an ECU to this sensor.
     * @param E A weak pointer to the ECU to attach.
     */
    void AttachECU(std::weak_ptr<ECU> E) override;

    /**
     * @brief Detaches an ECU from this sensor.
     * @param E A weak pointer to the ECU to detach.
     */
    void DeAttachECU(std::weak_ptr<ECU> E) override;

    /**
     * @brief Updates the attached ECU.
     * @param E A weak pointer to the ECU to update.
     */
    void updateECU(std::weak_ptr<ECU> E) override;

    /**
     * @brief Notifies all attached ECUs of changes.
     */
    void NotifyAllECUs() override;

    /**
     * @brief Gets the total number of sensors of this type.
     * @return The total count of battery level sensors.
     */
    virtual int getTotalSensorsCount() override;

private:
    double BatteryLevel; ///< The current battery level.
    static int BL_Sensor_Count; ///< The total number of battery level sensors created.
    const int Sensor_ID; ///< The unique ID for this battery level sensor.

    /**
     * @brief Generates a random battery level value.
     * @return A random battery level value.
     */
    double getBatteryLevel();

    /**
     * @brief Generates random data for the sensor.
     * @return A random double value for the sensor.
     */
    double getRandomData() override; // generate random data

    std::string type = "BatteryLevel Sensor"; ///< The type of the sensor.
};

#endif // !BatteryLevel_SENSOR_H
