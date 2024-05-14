add_library(Logger STATIC "Source/Logger.cpp")

find_package(spdlog)
if(TARGET spdlog)
    # Stand-alone build
    target_compile_definitions(Logger PUBLIC "USE_SPDLOG")
endif()

target_include_directories(Logger PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include")

target_link_libraries(Logger PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)