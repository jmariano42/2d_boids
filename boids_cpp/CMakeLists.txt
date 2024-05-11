# CMakeList.txt : CMake project for boids_cpp, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (boids_cpp "boids_cpp.cpp" "boids_cpp.h"   "boid.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET boids_cpp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
set(SFML_INCLUDE "C:/Program Files/SFML-2.6.1/include")
target_include_directories(boids_cpp PRIVATE ${SFML_INCLUDE})

set(SFML_AUDIO "C:/Program Files/SFML-2.6.1/lib/sfml-audio.lib")
target_link_libraries(boids_cpp PRIVATE ${SFML_AUDIO})

set(SFML_GRAPHICS "C:/Program Files/SFML-2.6.1/lib/sfml-graphics.lib")
target_link_libraries(boids_cpp PRIVATE ${SFML_GRAPHICS})

set (SFML_MAIN "C:/Program Files/SFML-2.6.1/lib/sfml-main.lib")
target_link_libraries(boids_cpp PRIVATE ${SFML_MAIN})

set(SFML_NETWORK "C:/Program Files/SFML-2.6.1/lib/sfml-network.lib")
target_link_libraries(boids_cpp PRIVATE ${SFML_NETWORK})

set(SFML_SYSTEM "C:/Program Files/SFML-2.6.1/lib/sfml-system.lib")
target_link_libraries(boids_cpp PRIVATE ${SFML_SYSTEM})

set(SFML_WINDOWS "C:/Program Files/SFML-2.6.1/lib/sfml-window.lib")
target_link_libraries(boids_cpp PRIVATE ${SFML_WINDOWS})