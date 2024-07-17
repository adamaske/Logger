cmake_minimum_required(VERSION 3.15)

project(Logger VERSION 0.1)


set(LOGGER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")
set(LOGGER_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(LOGGER_RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Resources")

file(GLOB INCS "${LOGGER_INCLUDE_DIR}/*.h")
file(GLOB SRCS "${LOGGER_SOURCE_DIR}/*.cpp")

add_library(Logger STATIC ${SRCS})

option(WRAP_SPDLOG ON)
if(WRAP_SPDLOG)
find_package(spdlog)
    if(TARGET spdlog)
        target_compile_definitions(Logger PUBLIC "USE_SPDLOG")
target_link_libraries(Logger PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)
    endif()
endif()

target_include_directories(Logger PUBLIC ${LOGGER_INCLUDE_DIR})

 
add_subdirectory(Tests)
#if this is the only built 
if(${CMAKE_SOURCE_DIR} EQUAL ${CMAKE_CURRENT_SOURCE_DIR})
  
endif()
