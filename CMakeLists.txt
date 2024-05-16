add_library(Logger INTERFACE)

find_package(spdlog)
if(TARGET spdlog)
    # Stand-alone build
    target_compile_definitions(Logger PUBLIC "USE_SPDLOG")
endif()

target_include_directories(Logger INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/Include")

target_link_libraries(Logger INTERFACE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)