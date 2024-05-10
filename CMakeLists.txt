cmake_minimum_required(VERSION 3.15)

project(Logger VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} STATIC src/Logger.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(spdlog)
if(TARGET spdlog)
target_compile_definitions(${PROJECT_NAME} PUBLIC "USE_SPDLOG")#
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog_header_only)
endif()