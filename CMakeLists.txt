cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ここから
set(TARGET_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/split.c
    ${CMAKE_CURRENT_LIST_DIR}/src/io/spi_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/src/io/uart_ex.c
    )
# ここまで変更する

if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
set(PICO_BOARD pico CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(split C CXX ASM)

pico_sdk_init()

# ここを変更する
add_executable(split ${TARGET_FILES})

pico_set_program_name(split "split")
pico_set_program_version(split "0.1")

pico_enable_stdio_uart(split 0)
pico_enable_stdio_usb(split 0)

target_link_libraries(split
        pico_stdlib)

target_include_directories(split PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include/io # この行を追加する
)

target_link_libraries(split 
        hardware_spi
        hardware_timer
        hardware_uart # この行を追加する
        )

pico_add_extra_outputs(split)
# add_subdirectory(src) # この行を追加する

