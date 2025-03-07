cmake_minimum_required(VERSION 3.10)
project(VirtualCameraDriver)

# C++17 사용
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCV 찾기
find_package(OpenCV REQUIRED)

# 소스파일과 헤더파일을 명시적으로 추가
set(SOURCES
	src/main.cpp
	src/FrameBuffer.cpp
	src/CameraInput.cpp
	src/VirtualCamera.cpp
)

set(HEADERS
	include/common.hpp
	include/FrameBuffer.hpp
	include/CameraInput.hpp
	include/VirtualCamera.hpp)

# 프로젝트 소스 파일 추가
add_executable(VCD ${SOURCES} ${HEADERS})

# 헤더 include 디렉토리 지정
target_include_directories(VCD PRIVATE 
	${CMAKE_SOURCE_DIR}/include 
	${OpenCV_INCLUDE_DIRS}
)

# OpenCV 라이브러리 링크
target_link_libraries(VCD PRIVATE ${OpenCV_LIBS})
