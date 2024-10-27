cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CarECU)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the source files for your project
set(SOURCE_FILES
    src/main.cpp
    car/Car.cpp
    ECU/Adaptive_Cruise_Control_ECU.cpp
    Sensors/BatteryLevelSensor.cpp
    ECU/DiagnosticsECU.cpp
    Sensors/RadarSensor.cpp
    Sensors/SpeedSensor.cpp
    Sensors/TemperatureSensor.cpp
    logger/CarLogger.cpp
    ECU/ECU.cpp 
  
    
)

# Include the directory containing header files
include_directories(Sensors)

# Add the executable
add_executable(CarECU ${SOURCE_FILES})
