cmake_minimum_required (VERSION 2.6)
project (SistOper)
add_executable(SistOper src/clock.cc src/common.cc src/disk.cc src/file.cc src/information_manager.cc src/job.cc src/main.cc src/memory.cc src/memory_manager.cc src/operating_system.cc src/process_manager.cc src/processor.cc src/segment.cc src/scheduler.cc)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
