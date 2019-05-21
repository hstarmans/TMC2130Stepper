cmake_minimum_required(VERSION 3.3)
project (test)
#Bring the headers, deprecated
include_directories(src
                    src/source)
# sources should be added manually
set(SOURCES ${PROJECT_SOURCE_DIR}/main.cpp
            ${PROJECT_SOURCE_DIR}/src/source/BusDevice.cpp
            ${PROJECT_SOURCE_DIR}/src/source/generic-gpio.cc
            ${PROJECT_SOURCE_DIR}/src/source/SPIDevice.cpp
            ${PROJECT_SOURCE_DIR}/src/source/TMC2130Stepper_CHOPCONF.cpp
            ${PROJECT_SOURCE_DIR}/src/source/TMC2130Stepper_COOLCONF.cpp
            ${PROJECT_SOURCE_DIR}/src/source/TMC2130Stepper_DRV_STATUS.cpp
            ${PROJECT_SOURCE_DIR}/src/source/TMC2130Stepper_GCONF.cpp
            ${PROJECT_SOURCE_DIR}/src/source/TMC2130Stepper_IHOLD_IRUN.cpp
            ${PROJECT_SOURCE_DIR}/src/source/TMC2130Stepper_PWMCONF.cpp
            ${PROJECT_SOURCE_DIR}/src/source/TMC2130Stepper.cpp)            
 
add_executable(main ${SOURCES})