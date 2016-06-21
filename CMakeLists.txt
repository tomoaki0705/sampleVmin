cmake_minimum_required(VERSION 2.8)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm.*|ARM.*)")
	set(CMAKE_CXX_FLAGS "-mfp16-format=ieee -mfpu=neon-fp16 -flax-vector-conversions")
endif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm.*|ARM.*)")

project(vminTest)

add_executable(vminTest main.cpp)
