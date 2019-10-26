cmake_minimum_required(VERSION 2.4.7)
PROJECT(indi-astroberry-amh CXX C)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake_modules/")
include(GNUInstallDirs)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 3)

find_package(INDI REQUIRED)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/indi_amh_focuser.xml.cmake ${CMAKE_CURRENT_BINARY_DIR}/indi_amh_focuser.xml)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INDI_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/libs/)

include(CMakeCommon)


add_library(AdafruitStepperMotorHAT STATIC IMPORTED)
set_property(TARGET AdafruitStepperMotorHAT PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/AdafruitStepperMotorHAT.a)

find_library(wiringPi_LIB wiringPi)

set(AMH_LIBRARIES "AdafruitStepperMotorHAT")


################ Adafruit Motor HAT Focuser ################
set(indi_amh_focuser_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/amh_focuser.cpp
   )

IF (UNITY_BUILD)
    ENABLE_UNITY_BUILD(indi_amh_focuser indi_amh_focuser_SRCS 6 cpp)
ENDIF ()

add_executable(indi_amh_focuser ${indi_amh_focuser_SRCS})
target_link_libraries(indi_amh_focuser ${INDI_DRIVER_LIBRARIES} ${AMH_LIBRARIES} ${wiringPi_LIB})
install(TARGETS indi_amh_focuser RUNTIME DESTINATION bin)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/indi_amh_focuser.xml DESTINATION ${INDI_DATA_DIR})
