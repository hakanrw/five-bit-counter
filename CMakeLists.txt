cmake_minimum_required(VERSION 3.13)

# initialize the SDK directly
set(PICO_BOARD pico_w)
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(five_bit_counter C CXX ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(five_bit_counter
    counter.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(five_bit_counter pico_stdlib pico_stdio)
target_include_directories(five_bit_counter PUBLIC .)
pico_add_extra_outputs(five_bit_counter)
pico_enable_stdio_usb(five_bit_counter 1)
