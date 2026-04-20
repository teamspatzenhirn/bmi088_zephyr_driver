# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

set(BOARD teensy41)

get_filename_component(BMI088_MODULE
    "${CMAKE_CURRENT_LIST_DIR}/../../../../../modules/bmi088"
    ABSOLUTE
)
get_filename_component(LPSPI_MODULE
    "${CMAKE_CURRENT_LIST_DIR}/../../../../../modules/lpspi"
    ABSOLUTE
)

list(APPEND EXTRA_ZEPHYR_MODULES 
	${BMI088_MODULE}
	${LPSPI_MODULE}
)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(as5x47_sample)

FILE(GLOB app_sources src/*.cpp)
target_sources(app PRIVATE ${app_sources})
