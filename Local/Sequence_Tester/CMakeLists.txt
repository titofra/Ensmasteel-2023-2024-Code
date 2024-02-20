cmake_minimum_required(VERSION 3.5)

# Project
project(Sequence_Tester)

# Sources
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Includes
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Flags
target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
	$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O3 -Wall -Wextra -Werror -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wunreachable-code -Wconversion -Wno-error=maybe-uninitialized -Wpedantic -Wno-error=float-equal>
)

# Add Libraries
find_package(SFML COMPONENTS window system graphics REQUIRED)

# Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window sfml-system sfml-graphics)
