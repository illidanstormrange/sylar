cmake_minimum_required(VERSION 2.8)
project(sylar)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMKAE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -oO -ggbd -std=c++11 -Wall -Wno-deprecated")

include_directories(.)
include_directories(/usr/include)
link_directories(/usr/lib)

find_library(YAMLCPP yaml-cpp)
message("***", ${YAMLCPP})

set(LIB_SRC
	log.cc
	util.cc
	config.cc
	thread.cc
	fiber.cc
	)
add_library(sylar SHARED ${LIB_SRC})

set(LIB_LIB
	sylar
	pthread
	${YAMLCPP}
	)

add_executable(test test.cc)
add_dependencies(test sylar)
target_link_libraries(test sylar -L/usr/lib -lyaml-cpp -lpthread)
#target_link_libraries(test sylar ${LIB_LIB})

add_executable(text_config text_config.cc)
add_dependencies(text_config sylar)
target_link_libraries(text_config sylar -L/usr/lib -lyaml-cpp -lpthread)
#
add_executable(test_thread test_thread.cc)
add_dependencies(test_thread sylar)
target_link_libraries(test_thread sylar -L/usr/lib -lyaml-cpp -lpthread)
#add_executable(text_config text_config.cc)

add_executable(test_util test_util.cc)
add_dependencies(test_util sylar)
target_link_libraries(test_util sylar -L/usr/lib -lyaml-cpp -lpthread)

add_executable(test_fiber test_fiber.cc)
add_dependencies(test_fiber sylar)
target_link_libraries(test_fiber sylar -L/usr/lib -lyaml-cpp -lpthread)

