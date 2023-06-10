cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico-projects-serial_servo)

pico_sdk_init()

add_executable(servo_serial_communication
    servo_serial_communication.c
    )

target_link_libraries(servo_serial_communication pico_stdlib hardware_adc hardware_pwm)

pico_enable_stdio_usb(servo_serial_communication 1)
pico_enable_stdio_uart(servo_serial_communication 0)

pico_add_extra_outputs(servo_serial_communication)