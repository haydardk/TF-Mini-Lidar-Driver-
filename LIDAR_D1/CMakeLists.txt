# AYARLANACAK
add_executable(lidar)

pico_generate_pio_header(lidar ${CMAKE_CURRENT_LIST_DIR}/uart_rx.pio)
target_sources(lidar lidar.c)

pico_enable_stdio_usb(lidar 1)
pico_enable_stdio_uart(lidar 1)

target_link_libraries(lidar
        pico_stdlib
        pico_multicore
        hardware_pio
        hardware_uart
        )
pico_add_extra_outputs(lidar)

