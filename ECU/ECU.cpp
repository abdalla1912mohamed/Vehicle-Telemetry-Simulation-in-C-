#include "ECU.hpp"
#include <unordered_map>
#include <vector>

std::atomic<int> ECU::ECU_Count {0}; 

/**
 * @brief Get the current count of ECUs created.
 * 
 * @return int The count of ECUs.
 */
int ECU::getECUCount() {
    return ECU_Count; 
}

/**
 * @brief Destructor for the ECU class.
 * 
 * Decreases the count of ECUs when an ECU object is destroyed
 * and logs the remaining count of ECUs.
 */
ECU::~ECU() {
    ECU_Count--; 
    std::cout << "ECU is destroyed; remaining ECU count is " << ECU_Count << std::endl; 
}

/**
 * @brief Constructor for the ECU class.
 * 
 * Initializes the ECU object, increments the count of ECUs,
 * and assigns a unique ID to the ECU.
 */
ECU::ECU() : Recent_Sensory_Data(Sensor_Types_Count) {
    ECU_Count++;  
    ECU_ID = ECU_Count; 
    std::cout << "A new ECU is created; the ECU count is " << ECU_Count << std::endl; 
}
