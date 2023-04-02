cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
# include(pico_extras_import_optional.cmake)

# project name 
project(robot C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the SDK
pico_sdk_init()

include(CTest)
enable_testing()

#include source directory
file(GLOB SOURCES "src/*.cpp")
add_executable(robot ${SOURCES})

# add include directory
target_include_directories(robot PUBLIC include)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_pwm) 

# pico_add_extra_outputs(robot) 
pico_add_extra_outputs(${PROJECT_NAME})

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
    