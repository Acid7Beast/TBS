cmake_minimum_required(VERSION 3.27)
project(TBS LANGUAGES CXX)

# ==============================================================================
# General Settings
# ==============================================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==============================================================================
# Submodules and Third-Party Libraries
# ==============================================================================

# ------------------------------------------------------------------------------
# SW API
# ------------------------------------------------------------------------------
file(GLOB_RECURSE SWApiSources
    "${CMAKE_SOURCE_DIR}/external/SW/*.cpp"
    "${CMAKE_SOURCE_DIR}/external/SW/*.hpp"
)
add_library(SWApi STATIC ${SWApiSources})

target_include_directories(SWApi PUBLIC external/SW/src)

# ==============================================================================
# Main Executable
# ==============================================================================
file(GLOB_RECURSE TBSSources
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
add_executable(TBS src/main.cpp ${TBSSources})
target_compile_features(TBS PRIVATE cxx_std_20)
target_include_directories(TBS PUBLIC src)

target_link_libraries(TBS PRIVATE
    SWApi
)

# ==============================================================================
# Platform-specific settings
# ==============================================================================
# For Windows: set the default startup project in VS
if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()