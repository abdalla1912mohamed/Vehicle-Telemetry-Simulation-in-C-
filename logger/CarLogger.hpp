#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <mutex>
#include <string>

/**
 * @brief Logger class for logging messages in a thread-safe manner.
 * 
 * This class implements the Singleton pattern to ensure only one instance 
 * exists throughout the application. It provides a method to log messages 
 * with thread safety using mutexes.
 */
class Logger {
public:
    // Deleted copy constructor and assignment operator to prevent copying
    Logger(const Logger&) = delete; ///< Deleted copy constructor
    Logger& operator=(const Logger&) = delete; ///< Deleted assignment operator

    /**
     * @brief Gets the singleton instance of the Logger.
     * 
     * This method creates the Logger instance if it doesn't exist 
     * and returns the single instance of the Logger.
     * 
     * @return Logger& Reference to the singleton Logger instance.
     */
    static Logger& getInstance();

    /**
     * @brief Logs a message to the output.
     * 
     * This method logs the specified message in a thread-safe manner.
     * 
     * @param message The message to log.
     */
    void log(const std::string& message);

private:
    Logger(); ///< Private constructor to prevent direct instantiation

    static int message_number; ///< Static variable to track the number of messages

    std::mutex logMutex; ///< Mutex for thread-safe logging
};

#endif // LOGGER_HPP
// add configuration levels 
