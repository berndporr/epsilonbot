cmake_minimum_required(VERSION 3.20.0)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(Zetabot_Library LANGUAGES CXX)
include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall)

find_package (Curses)

set(LIBINCLUDE zetabot.h rpi_pwm.h)

add_library(zetabot
  STATIC
  zetabot.cpp
  )

set_target_properties(zetabot PROPERTIES
  POSITION_INDEPENDENT_CODE TRUE
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(zetabot gpiodcxx rt)

install(TARGETS zetabot EXPORT zetabot-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable (testIO testIO.cpp)
target_link_libraries(testIO zetabot ncurses rt)

add_executable (testMotor testMotor.cpp)
target_link_libraries(testMotor zetabot ncurses rt)

add_executable (testSpeeds testSpeeds.cpp)
target_link_libraries(testSpeeds zetabot ncurses rt)