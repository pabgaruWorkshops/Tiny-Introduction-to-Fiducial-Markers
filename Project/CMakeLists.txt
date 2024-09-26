# General info
cmake_minimum_required (VERSION 3.0)
project (TinyIntroductionToFiducialMarkers)
set(CMAKE_CXX_FLAGS "-std=c++11")



# OpenCV installation
find_package(OpenCV 4.5 REQUIRED)
LINK_LIBRARIES(${OpenCV_LIBS})

# Use of Ovis?
# Set to false if there is no ovis installation
set(use_of_ovis TRUE)


#~~~~~~~~~~~~~~~
#   Auxiliar
#~~~~~~~~~~~~~~~
# Aruco markers printing
add_executable(printMarkers src/auxiliar/printMarkers.cpp)
# Ovis installation test
if(use_of_ovis)
    add_executable(testOvis src/auxiliar/testOvis.cpp)
endif(use_of_ovis)

#~~~~~~~~~~~~~~~~~~
#   Applications
#~~~~~~~~~~~~~~~~~~
# Main Application
add_executable(mainApp src/apps/appA.cpp src/apps/appAFunctions/functions.cpp)
# Main Application + Ovis
if(use_of_ovis)
    add_executable(mainAppOvis src/apps/appB.cpp src/apps/appBFunctions/functions.cpp)
endif(use_of_ovis)