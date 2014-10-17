set(PROJ_NAME kum)

project(${PROJ_NAME})

cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src SRC_LIST)
aux_source_directory(./src/thirdparty SRC_LIST)
aux_source_directory(. SRC_LIST)
include_directories(/usr/include/)
add_definitions(-std=c++11 -Wall)

add_executable(${PROJECT_NAME} ${SRC_LIST})

# Libraries to be linked
target_link_libraries(${PROJ_NAME} glfw GL assimp)
