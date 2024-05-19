cmake_minimum_required(VERSION 3.15)
project(Logger)

# make cache variables for install destinations
include(GNUInstallDirs)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_library(Logger STATIC "Source/Logger.cpp")

target_include_directories(Logger
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

find_package(spdlog REQUIRED) 

target_link_libraries(Logger PRIVATE spdlog::spdlog)
target_compile_definitions(Logger PRIVATE "USE_SPDLOG")

install(TARGETS Logger
        EXPORT LoggerTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES Include/Logger.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT LoggerTargets
        FILE LoggerTargets.cmake
        NAMESPACE Logger::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Logger
)

export(EXPORT LoggerTargets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/LoggerTargets.cmake"
       NAMESPACE Logger::
)