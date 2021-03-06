cmake_minimum_required (VERSION 2.6)
project (SistOper)
add_executable(SistOper src/common.cc src/file.cc
    src/information_manager.cc src/job.cc src/main.cc 
    src/memory_manager.cc src/operating_system.cc src/process_manager.cc
    src/segment.cc src/scheduler.cc src/events/job_arrival_event.cc
    src/event.cc src/events/processor_request_event.cc src/events/time_slice_event.cc
	src/events/job_finish_event.cc)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
