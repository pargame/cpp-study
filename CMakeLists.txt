cmake_minimum_required(VERSION 3.20)

project(CppSolves CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 바이너리를 build/(debug or release)/ 바로 아래로 출력 (F5 자동 연동)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Mac 환경에서 <bits/stdc++.h> 헤더 탐색 경로
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 실행 타깃
add_executable(example example.cpp)
