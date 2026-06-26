cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_hid_bridge C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(pico_hid_bridge
    src/main.c
    src/usb_descriptors.c
)

target_include_directories(pico_hid_bridge PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

target_link_libraries(pico_hid_bridge PRIVATE
    pico_stdlib
    pico_unique_id
    pico_cyw43_arch_lwip_threadsafe_background
    tinyusb_device
    tinyusb_board
)

pico_enable_stdio_usb(pico_hid_bridge 1)
pico_enable_stdio_uart(pico_hid_bridge 0)

pico_add_extra_outputs(pico_hid_bridge)
