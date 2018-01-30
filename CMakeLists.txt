PROJECT(Fractals)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#export compile commands for use in visualizations
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMakeModules")

SET(CXX11_FLAGS -std=gnu++11)
SET(CDEBUG_FLAGS -g)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAGS} ${CDEBUG_FLAGS}")

# Set Includdes
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

# Set sources
FILE(GLOB_RECURSE SOURCES "src/*.cpp")
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})

add_custom_target("${PROJECT_NAME}_SUCCESSFUL" ALL
                  DEPENDS ${PROJECT_NAME}
                  COMMAND ${CMAKE_COMMAND} -E echo ""
                  COMMAND ${CMAKE_COMMAND} -E echo "====================="
                  COMMAND ${CMAKE_COMMAND} -E echo "  Compile complete!"
                  COMMAND ${CMAKE_COMMAND} -E echo "====================="
                  COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_CURRENT_BINARY_DIR}"
                 )