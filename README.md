 # This repository contains a simulated car instance built from various classes representing sensors, ECUs (Electronic Control Units), a Diagnostic ECU, and a central Logger. The system's architecture is designed with best practices in C++ OOP and design patterns to maintain scalability, efficiency, and readability.
#### how to build & RUN : 
mkdir build 
cd build 
cmake .. 
make 
./CarECU









## Key Components
### Sensors:

##### A base Sensor class represents the fundamental sensor interface.
Derived classes include TemperatureSensor, RadarSensor, BatteryLevelSensor, and SpeedSensor, each responsible for monitoring specific metrics.
Each sensor can notify its list of subscribed ECUs upon data updates.
ECUs:

##### A base ECU class defines general ECU behaviors, such as subscribing to specific sensors and receiving data.
Specialized ECUs, such as an AdaptiveCruiseControl ECU, respond to sensor data for driving decisions and are designed to handle specific sensor readings.
Diagnostic ECU:

##### A DiagnosticECU class collects data across sensors and ECUs, analyzing system health and flagging any potential issues.
Runs diagnostic checks on sensor values and outputs alerts or logs for any detected abnormalities.
Logger:

##### A Logger singleton provides system-wide logging capabilities, tracking telemetry data and diagnostic outputs.
Ensures a consolidated record of telemetry events, sensor updates, and diagnostic results for review.
Project Structure
The project is structured as follows:

porject directory - Contains the implementation files for Sensors, ECUs, , Logger and car  classes.
/src include --> the main.cpp

 ###### Modular Sensor Design: Add new sensors with ease by extending the Sensor base class.
###### Event-Driven Notification: ECUs receive real-time updates from subscribed sensors to take immediate action.
###### Comprehensive Diagnostics: The Diagnostic ECU monitors all systems for anomalies, maintaining vehicle health.
###### Singleton Logging: Unified logging service for consistent, centralized data tracking.
###### Simulation Script: Provides an interactive simulation of the telemetry system, showcasing the interaction between sensors, ECUs, and the Logger.
###### Design Patterns Used :
Observer Pattern: Sensors notify subscribed ECUs of data changes, enabling responsive and modular data handling.
Singleton Pattern: The Logger class ensures a single instance for logging across the entire simulation.
