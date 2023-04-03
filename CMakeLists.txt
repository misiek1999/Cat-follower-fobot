cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
include(pico_extras_import_optional.cmake)
# Pull freeRTOS
include(FreeRTOS_Kernel_import.cmake)

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
target_include_directories(robot PUBLIC include FreeRTOS_config)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_pwm pico_multicore FreeRTOS-Kernel FreeRTOS-Kernel-Heap1) 

# enable usb output, disable uart output
pico_enable_stdio_usb(robot 1)
pico_enable_stdio_uart(robot 0)


# pico_add_extra_outputs(robot) 

