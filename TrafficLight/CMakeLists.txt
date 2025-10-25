cmake_minimum_required(VERSION 3.10)
project(TrafficLight)

find_package(OpenCV REQUIRED)

add_executable(traffic_light ../main.cpp ../video_process.cpp)

target_link_libraries(traffic_light ${OpenCV_LIBS})

set(CMAKE_CXX_STANDARD 11)
