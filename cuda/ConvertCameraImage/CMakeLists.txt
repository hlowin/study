cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME ConvertImage)

project(${PROJECT_NAME})

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

find_package(CUDA REQUIRED)
if(CUDA_FOUND)
    message("Cuda version: " ${CUDA_VERSION})
    cuda_add_executable(
        ${PROJECT_NAME}
        ${PROJECT_NAME}.cu
    )
endif()

find_package(OpenCV 4.1.1 REQUIRED)
if(OpenCV_FOUND)
    include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})
endif()

find_package(realsense2 REQUIRED)
if(realsense2_FOUND)
    include_directories(${PROJECT_NAME} PUBLIC ${realsense2_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${realsense2_LIBRARY})
endif()