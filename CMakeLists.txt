cmake_minimum_required(VERSION 2.8)
project(sylar)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -g -oO  -std=c++11 -Wall -Wno-deprecated")

include_directories(.)
include_directories(/usr/include)
link_directories(/usr/lib)

find_library(YAMLCPP yaml-cpp)

set(LIB_SRC
	socket.cc
	address.cc
	log.cc
	util.cc
	config.cc
	thread.cc
	scheduler.cc
	fiber.cc
	iomanager.cc
	fdmanager.cc
	timer.cc
	hook.cc
	bytearry.cc
	)
add_library(sylar SHARED ${LIB_SRC})

set(LIB_LIB
	sylar
	pthread
	${YAMLCPP}
	)


add_executable(text_config test/text_config.cc)
add_dependencies(text_config sylar)
target_link_libraries(text_config sylar -L/usr/lib -lyaml-cpp -lpthread -ldl)

add_executable(test_thread test/test_thread.cc)
add_dependencies(test_thread sylar)
target_link_libraries(test_thread sylar -L/usr/lib -lyaml-cpp -lpthread -ldl)

add_executable(test_util test/test_util.cc)
add_dependencies(test_util sylar)
target_link_libraries(test_util sylar -L/usr/lib -lyaml-cpp -lpthread -ldl)
#
add_executable(test_fiber test/test_fiber.cc)
add_dependencies(test_fiber sylar)
target_link_libraries(test_fiber sylar -L/usr/lib -lyaml-cpp -lpthread -ldl)

add_executable(test_scheduler test/test_scheduler.cc)
add_dependencies(test_scheduler sylar)
target_link_libraries(test_scheduler sylar -L/usr/lib -lyaml-cpp -lpthread -ldl)

add_executable(test_iomanager test/test_iomanager.cc)
add_dependencies(test_iomanager sylar)
target_link_libraries(test_iomanager sylar -L/usr/lib -lyaml-cpp -lpthread -ldl)

add_executable(test_hook test/test_hook.cc)
add_dependencies(test_hook sylar)
target_link_libraries(test_hook sylar -L/usr/lib -lyaml-cpp -lpthread -ldl)

add_executable(test_address test/test_address.cc)
add_dependencies(test_address sylar)
target_link_libraries(test_address sylar -L/usr/lib -lyaml-cpp -lpthread -ldl)

add_executable(test_socket test/test_socket.cc)
add_dependencies(test_socket sylar)
target_link_libraries(test_socket sylar -L/usr/lib -lyaml-cpp -lpthread -ldl)

add_executable(test_bytearray test/test_bytearray.cc)
add_dependencies(test_bytearray sylar)
target_link_libraries(test_bytearray sylar -L/usr/lib -lyaml-cpp -lpthread -ldl)
