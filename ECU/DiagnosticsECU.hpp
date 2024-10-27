#ifndef DIAGNOSTIC_ECU_h 
#define DIAGNOSTIC_ECU_h 

#include "ECU.hpp"

// Forward declaration
class Car;

/**
 * @brief Class representing a Diagnostic ECU, inheriting from the ECU base class.
 */
class DiagnosticECU : public ECU {
public:
    /**
     * @brief Constructor for the DiagnosticECU class.
     * 
     * Initializes a new instance of the DiagnosticECU.
     */
    DiagnosticECU();

    /**
     * @brief Attaches a sensor to this Diagnostic ECU.
     * 
     * @param s A shared pointer to the sensor to be attached.
     */
    void AttachSensor(std::shared_ptr<Sensor> s) override;

    /**
     * @brief Detaches a sensor from this Diagnostic ECU.
     * 
     * @param s A shared pointer to the sensor to be detached.
     */
    void DeattachSensor(std::shared_ptr<Sensor> s) override;

    /**
     * @brief Retrieves the name of this Diagnostic ECU.
     * 
     * @return std::string The name of the Diagnostic ECU.
     */
    std::string getName() const override;

    /**
     * @brief Retrieves the ID of this Diagnostic ECU.
     * 
     * @return int The ID of the Diagnostic ECU.
     */
    int getID() const override;

    /**
     * @brief Performs the main function of the Diagnostic ECU with the specified car.
     * 
     * @param c The car to perform the function on.
     */
    void PerformFunction(Car c) override;

    /**
     * @brief Updates the state of the Diagnostic ECU.
     */
    void update();

    /**
     * @brief Destructor for the DiagnosticECU class.
     * 
     * Cleans up resources used by the DiagnosticECU.
     */
    ~DiagnosticECU();

    /**
     * @brief Checks if the Diagnostic ECU is turned ON.
     * 
     * @return true if the ECU is ON, false otherwise.
     */
    bool IsON();

private:
    std::string type; ///< Type of the Diagnostic ECU
    bool Diagnostic_ON; ///< State indicating if the ECU is ON
};

#endif
