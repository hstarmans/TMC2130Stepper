# Author Hexastorm 

project (TMC2130Stepper)

cmake_minimum_required(VERSION 3.3)

# adds compiler flags
add_definitions(-Wall -std=c++0x)

#Bring the headers, deprecated
include_directories(src
                   src/source)

# sources should be added manually
set(LIB_SOURCES 
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

# this code can be used to build c++ examples
# compilation output is placed in  binary folder
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# library is written to build folder
# add_library( TMC2130Lib ${LIB_SOURCES})

# set(TARGETS ${PROJECT_SOURCE_DIR}/examples/testzconnection.cpp
# 	    ${PROJECT_SOURCE_DIR}/examples/testyconnection.cpp
# 	    ${PROJECT_SOURCE_DIR}/examples/testxconnection.cpp
# 	    ${PROJECT_SOURCE_DIR}/examples/homex.cpp)

# foreach( target ${TARGETS})
#     get_filename_component(targetname ${target} NAME)
#     string( REPLACE ".cpp" "" targetname ${targetname} )
#     add_executable( ${targetname} ${target}) 
#     target_link_libraries( ${targetname} TMC2130Lib )
# endforeach( target ${TARGETS})

# build the python module
add_subdirectory(${PROJECT_SOURCE_DIR}/python/pybind11)

pybind11_add_module(steppers ${PROJECT_SOURCE_DIR}/python/src/main.cpp ${LIB_SOURCES})
