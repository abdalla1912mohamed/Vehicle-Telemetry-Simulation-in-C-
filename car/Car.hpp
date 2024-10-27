#ifndef CAR_H 
#define CAR_H 

#include "../ECU/Adaptive_Cruise_Control_ECU.hpp"
#include "../Sensors/BatteryLevelSensor.hpp"
#include "../logger/CarLogger.hpp" 
#include "../ECU/DiagnosticsECU.hpp"
#include "../Sensors/RadarSensor.hpp"
#include "../Sensors/Sensor.hpp" 
#include "../ECU/ECU.hpp"
#include "../Sensors/SpeedSensor.hpp"
#include "../Sensors/TemperatureSensor.hpp"
#include <memory>
#include <unordered_map>

#define MAX_SENSOR_NUMBER 4 ///< Maximum number of sensors
#define MAX_SPEED 50 ///< Maximum speed limit
#define MAX_TEMPERATURE 30 ///< Maximum temperature limit
#define LOW_BATTERY 20 ///< Battery level threshold for low battery warning
#define SAFE_RADAR_DISTANCE 5 ///< Minimum safe distance for radar detection

/**
 * @brief Represents a car with various sensors and ECUs (Electronic Control Units).
 * 
 * The Car class encapsulates the functionality of a vehicle, including
 * activating ECUs and sensors, updating sensor data, and displaying 
 * the car's status.
 */
class Car {
public: 
    /**
     * @brief Constructs a Car object with the specified model and make.
     * 
     * @param model The model of the car.
     * @param make The make of the car.
     */
    Car(const std::string& model, const std::string& make);
    
    /**
     * @brief Destroys the Car object and releases resources.
     */
    ~Car();

    /**
     * @brief Activates the specified ECU.
     * 
     * @param E A shared pointer to the ECU to be activated.
     */
    void ActivateECU(std::shared_ptr<ECU> E);

    /**
     * @brief Activates the specified sensor.
     * 
     * @param S A shared pointer to the sensor to be activated.
     */
    void ActivateSensor(std::shared_ptr<Sensor> S);

    /**
     * @brief Starts the diagnostic tool for the car.
     */
    void StartDiagonisticTool() const;

    /**
     * @brief Initializes the car systems.
     */
    void CarINIT();

    /**
     * @brief Sets the adaptive cruise control mode.
     * 
     * @param mode A boolean indicating the desired adaptive mode state.
     */
    void setAdaptiveMode(bool mode);

    /**
     * @brief Retrieves the current state of the adaptive cruise control mode.
     * 
     * @return bool True if adaptive mode is active, false otherwise.
     */
    bool getAdaptiveMode();

    /**
     * @brief Updates the data from all sensors in the car.
     */
    void UpdateSensorsData();

    /**
     * @brief Displays the current status of the car, including sensor data.
     */
    void DisplayStatus();

private: 
    std::string model; ///< The model of the car
    std::string make; ///< The make of the car
    std::vector<std::shared_ptr<ECU>> ECUs; ///< List of ECUs in the car
    std::vector<std::shared_ptr<Sensor>> Sensors; ///< List of sensors in the car
    std::unordered_map<SensorTypes, double> Car_info; ///< Map to store sensor data
    std::shared_ptr<SpeedSensor> Car_Speed_Sensor; ///< Speed sensor of the car
    std::shared_ptr<TemperatureSensor> Car_Temperature_Sensor; ///< Temperature sensor of the car
    std::shared_ptr<BatteryLevelSensor> Car_Battery_Level_Sensor; ///< Battery level sensor of the car
    std::shared_ptr<RadarSensor> Car_Radar_Sensor; ///< Radar sensor of the car
    std::shared_ptr<Adaptive_Cruise_Control_ECU> Car_Adaptive_Cruise_Control_ECU; ///< Adaptive cruise control ECU
    std::shared_ptr<DiagnosticECU> Car_Diagnostic_ECU; ///< Diagnostic ECU
    bool Adaptive_MODE; ///< Indicates whether adaptive mode is active
};

#endif // CAR_H
