cmake_minimum_required(VERSION 3.25)
project(notes CXX)

set(CMAKE_CXX_STANDARD 23)
set(SRC ${CMAKE_CURRENT_LIST_DIR}/src)
set(INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(${PROJECT_NAME}
    ${SRC}/args.cpp
    ${SRC}/DataFile.cpp
    ${SRC}/DataHandler.cpp
    ${SRC}/DataSection.cpp
    ${SRC}/FileHandler.cpp
    ${SRC}/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE})

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"
)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()

