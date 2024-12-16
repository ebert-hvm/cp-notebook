cmake_minimum_required(VERSION 3.15)
project(CP_Notebook LANGUAGES CXX)

# ----------------------------
# Configuration Options
# ----------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Option for verbose output
option(BUILD_VERBOSE "Enable verbose output" OFF)
if (BUILD_VERBOSE)
    message(STATUS "Verbose build enabled")
endif()

# ----------------------------
# Directory Setup
# ----------------------------
set(ALGORITHMS_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)
set(TEST_DATA_DIR ${CMAKE_SOURCE_DIR}/data)

# ----------------------------
# Collect Source Files
# ----------------------------
file(GLOB_RECURSE ALGORITHM_SOURCES "${ALGORITHMS_DIR}/*.cpp")
file(GLOB_RECURSE ALGORITHM_HEADERS "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp")

# ----------------------------
# Main Library Target
# ----------------------------
add_library(ICPCAlgorithms STATIC ${ALGORITHM_SOURCES} ${ALGORITHM_HEADERS})

target_include_directories(ICPCAlgorithms
    PUBLIC
        ${INCLUDE_DIR}
)

# ----------------------------
# Local Testing Setup
# ----------------------------
enable_testing()
file(GLOB_RECURSE TEST_FILES "${TESTS_DIR}/*.cpp")

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE ICPCAlgorithms)
    target_compile_definitions(${TEST_NAME} PRIVATE TEST_DATA_DIR="${TEST_DATA_DIR}")
    add_test(
        NAME ${TEST_NAME}
        COMMAND ${TEST_NAME}
    )
endforeach()

# ----------------------------
# Online Judge Submission
# ----------------------------
add_custom_target(submit
    COMMAND ${CMAKE_COMMAND} -E echo "Submitting to online judge..."
    # Add submission logic here (e.g., custom script or curl command)
)
