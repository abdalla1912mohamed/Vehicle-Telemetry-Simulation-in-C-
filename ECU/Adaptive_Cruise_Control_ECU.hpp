#ifndef ADAPTIVE_CRUISE_CONTROL_ECU_h 
#define ADAPTIVE_CRUISE_CONTROL_ECU_h 

#include "ECU.hpp"

/**
 * @class Adaptive_Cruise_Control_ECU
 * @brief Class representing an Adaptive Cruise Control ECU.
 * 
 * This class inherits from the ECU base class and implements methods to
 * attach and detach sensors, perform functions related to adaptive cruise control,
 * and manage the state of the adaptive cruise control system.
 */
class Adaptive_Cruise_Control_ECU : public ECU {
public:
    /**
     * @brief Default constructor for Adaptive_Cruise_Control_ECU.
     * 
     * Initializes the ECU and sets the adaptive cruise control status.
     */
    Adaptive_Cruise_Control_ECU();

    /**
     * @brief Attaches a sensor to the adaptive cruise control ECU.
     * @param s A shared pointer to the sensor to attach.
     */
    void AttachSensor(std::shared_ptr<Sensor> s) override;

    /**
     * @brief Detaches a sensor from the adaptive cruise control ECU.
     * @param s A shared pointer to the sensor to detach.
     */
    void DeattachSensor(std::shared_ptr<Sensor> s) override;

    /**
     * @brief Gets the name of the adaptive cruise control ECU.
     * @return The name of the ECU as a string.
     */
    std::string getName() const override;

    /**
     * @brief Gets the ID of the adaptive cruise control ECU.
     * @return The ID of the ECU as an integer.
     */
    int getID() const override;

    /**
     * @brief Performs the function of the adaptive cruise control ECU.
     * @param c The car object that the ECU is controlling.
     */
    void PerformFunction(Car c) override;

    /**
     * @brief Destructor for Adaptive_Cruise_Control_ECU.
     * 
     * Cleans up resources and performs any necessary shutdown procedures.
     */
    ~Adaptive_Cruise_Control_ECU();

    /**
     * @brief Checks if the adaptive cruise control is currently active.
     * @return True if the adaptive cruise control is on, false otherwise.
     */
    bool IsON(); 

private:
    std::string type;  ///< The type of the adaptive cruise control ECU.
    bool ADAPTIVE_ON;  ///< The status indicating if adaptive cruise control is active.
};

#endif // !ADAPTIVE_CRUISE_CONTROL_ECU_h 
