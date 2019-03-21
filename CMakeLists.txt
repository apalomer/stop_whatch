# Set up cmake
cmake_minimum_required (VERSION 3.0)
project (stop_watch CXX C)
add_compile_options(-std=c++11 -Wall -Wextra)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set ouput paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Find LIbrary
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

include_directories(src)

# Add code
add_executable(stop_watch
  src/main.cpp
  src/stopwhatch.cpp src/stopwhatch.h src/stopwhatch.ui
  src/analogclock.cpp src/analogclock.h
  src/digitalclock.cpp src/digitalclock.h
  src/digitalchrono.cpp src/digitalchrono.h
  src/abstractclock.cpp src/abstractclock.h
  src/logosdisplay.cpp src/logosdisplay.h)
target_link_libraries(stop_watch Qt5::Core Qt5::Widgets)
