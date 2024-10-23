# This is the main binary. List your C files here.
add_executable(sleep
    sleep.c
    )

pico_set_program_name(sleep "test")
pico_set_program_version(sleep "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(sleep 0)
pico_enable_stdio_usb(sleep 1)

# This is the main binary. List your C files here.
add_executable(delay
    delay.c
    )

pico_set_program_name(delay "test")
pico_set_program_version(delay "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(delay 0)
pico_enable_stdio_usb(delay 1)

# This is the main binary. List your C files here.
add_executable(timer
    timer.c
    )

pico_set_program_name(timer "test")
pico_set_program_version(timer "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(timer 0)
pico_enable_stdio_usb(timer 1)

# This is the main binary. List your C files here.
add_executable(gpio_interrupt
    gpio_interrupt.c
    )

pico_set_program_name(gpio_interrupt "test")
pico_set_program_version(gpio_interrupt "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(gpio_interrupt 0)
pico_enable_stdio_usb(gpio_interrupt 1)

# Add the libraries to the build
target_link_libraries(sleep PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)

# Add the libraries to the build
target_link_libraries(delay PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)

# Add the libraries to the build
target_link_libraries(timer PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)
# Add the libraries to the build
target_link_libraries(gpio_interrupt PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
    target_link_libraries(sleep PRIVATE
        pico_cyw43_arch_none
    )
    target_link_libraries(delay PRIVATE
        pico_cyw43_arch_none
    )
    target_link_libraries(timer PRIVATE
    pico_cyw43_arch_none
)
target_link_libraries(gpio_interrupt PRIVATE
pico_cyw43_arch_none)
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(sleep)
pico_add_extra_outputs(delay)
pico_add_extra_outputs(timer)
pico_add_extra_outputs(gpio_interrupt)




add_custom_target(flashsleep picotool load -f $<TARGET_FILE:sleep> DEPENDS sleep)
add_custom_target(flashdelay picotool load -f $<TARGET_FILE:sleep> DEPENDS delay)
add_custom_target(flashtimer picotool load -f $<TARGET_FILE:sleep> DEPENDS timer)
add_custom_target(flashgpio_interrupt picotool load -f $<TARGET_FILE:sleep> DEPENDS gpio_interrupt)


