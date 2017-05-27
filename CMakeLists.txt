cmake_minimum_required(VERSION 2.4.7)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

PROJECT(indi-amh CXX C)
include(ExternalProject)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")
set(BIN_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
set(MAKE make)

find_package(INDI REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INDI_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/libs/AdafruitStepperMotorHAT_CPP)

add_library(AdafruitStepperMotorHAT STATIC IMPORTED)
set_property(TARGET AdafruitStepperMotorHAT PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/AdafruitStepperMotorHAT_CPP/AdafruitStepperMotorHAT.a)
add_dependencies(AdafruitStepperMotorHAT libAdafruitStepperMotorHAT)

################ AdafruitStepperMotorHAT ################

ExternalProject_Add(libAdafruitStepperMotorHAT
    GIT_REPOSITORY "https://github.com/rkaczorek/AdafruitStepperMotorHAT_CPP.git"
    GIT_TAG "master"
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/AdafruitStepperMotorHAT_CPP
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libs/AdafruitStepperMotorHAT_CPP
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE}
    INSTALL_COMMAND ""
    BUILD_IN_SOURCE 1
)


################ Adafruit Motor HAT Focuser ################

set(indi_amh_focuser_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/amh_focuser.cpp
   )

add_executable(indi_amh_focuser ${indi_amh_focuser_SRCS})
target_link_libraries(indi_amh_focuser indidriver AdafruitStepperMotorHAT wiringPi pthread crypt rt)
install(TARGETS indi_amh_focuser RUNTIME DESTINATION bin)
install(FILES indi_amh_focuser.xml DESTINATION ${INDI_DATA_DIR})
