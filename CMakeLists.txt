# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
#include(pico_sdk_import.cmake)
# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)


project(WindOMaticX C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

#include ($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

# Add pico-stepper directory
add_subdirectory(../pico-stepper/lib stepper)

# Add pico-display directory
#set(PICO_SSD1306_DIR ../../pico-ssd1306/)
#include(pico-ssd1306.cmake)





# Add executable.
add_executable(wmx main.c)

target_link_libraries(wmx pico_stdlib hardware_i2c)
#target_link_libraries(wmx pico_stdlib hardware_spi)
#target_include_directories(wmx INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

#target_include_directories(wmx PUBLIC ../pico-ssd1306)

# This stdio configuration alows to see the Pico output when connected to a
# picoprobe. Enable usb and disable uart for standalone operation (direct USB
# connection).
pico_enable_stdio_uart(wmx 1)
pico_enable_stdio_usb(wmx 1)

# Standard and additional libraries
target_link_libraries(
	wmx
	pico_stdlib
	pico-stepper)

pico_add_extra_outputs(wmx)
