#include "CarLogger.hpp"

// Define the static variable in exactly one place in the implementation file
int Logger::message_number = 0; ///< Static variable to track the number of log messages

/**
 * @brief Retrieves the singleton instance of the Logger.
 * 
 * This method ensures that the Logger instance is created only once 
 * and returns a reference to that instance. The instance is created 
 * on the first call to this method and destroyed when the program exits.
 * 
 * @return Logger& Reference to the singleton Logger instance.
 */
Logger& Logger::getInstance() {
    static Logger instance; // Guaranteed to be destroyed and instantiated on first use
    return instance;
}

// Private constructor
Logger::Logger() {
    // No need to initialize message_number here since it’s initialized above
}

/**
 * @brief Logs a message to the console.
 * 
 * This method logs the specified message along with the message number 
 * in a thread-safe manner using a mutex lock. It increments the message 
 * count each time a new message is logged.
 * 
 * @param message The message to log.
 */
void Logger::log(const std::string& message) {
    ++message_number; // Increment the log message counter
    std::lock_guard<std::mutex> guard(logMutex); // Locking for thread safety
    std::cout << "CAR LOGGER (" << message_number << "): " << message << std::endl; // Output the log message
}
