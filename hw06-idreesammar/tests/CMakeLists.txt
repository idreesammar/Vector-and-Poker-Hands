# Require CMAKE 3.1 or higher
cmake_minimum_required(VERSION 3.1)

# If you create new headers/cpp files, add them to these list!
set(HEADER_FILES
    catch.hpp
)

set(SOURCE_FILES
    Catch.cpp
	studentTests.cpp
)

# Don't change this
add_executable(tests ${SOURCE_FILES})
target_link_libraries(tests src)
