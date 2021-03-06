cmake_minimum_required(VERSION 2.8)
project(sylar)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -g -oO  -std=c++11 -Wall -Wno-deprecated")

include_directories(.)
include_directories(/usr/include)
link_directories(/usr/lib)

find_library(YAMLCPP yaml-cpp)

set(LIB_SRC
	config.cc
	log.cc
	mutex.cc
	socket.cc
	daemon.cc
	stream.cc
	socket_stream.cc
	hook.cc
	address.cc
	env.cc
	util.cc
	thread.cc
	scheduler.cc
	iomanager.cc
	fdmanager.cc
	timer.cc
	bytearry.cc
	tcp_server.cc
	module.cc
	application.cc
	fiber.cc
	worker.cc
	library.cc
	util/hash_util.cc
	util/json_util.cc
	http/http.cc
	http/http_parser.cc
	http/http_session.cc
	http/http_connection.cc
	http/servlet.cc
	http/http_server.cc
	http/http11_parser.cc
	http/httpclient_parser.cc
	http/ws_server.cc
	http/ws_servlet.cc
	#http/ws_connection.cc
	http/ws_session.cc
	uri.cc
	)
add_library(sylar SHARED ${LIB_SRC})

set(LIB_LIB
	sylar
	pthread
	jsoncpp
	${YAMLCPP}
	)


add_executable(text_config test/text_config.cc)
add_dependencies(text_config sylar)
target_link_libraries(text_config sylar -L/usr/lib -lyaml-cpp -lpthread -ldl  -lssl -lcrypto -ljsoncpp)

add_executable(test_thread test/test_thread.cc)
add_dependencies(test_thread sylar)
target_link_libraries(test_thread sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_util test/test_util.cc)
add_dependencies(test_util sylar)
target_link_libraries(test_util sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)
#
add_executable(test_fiber test/test_fiber.cc)
add_dependencies(test_fiber sylar)
target_link_libraries(test_fiber sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_scheduler test/test_scheduler.cc)
add_dependencies(test_scheduler sylar)
target_link_libraries(test_scheduler sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_iomanager test/test_iomanager.cc)
add_dependencies(test_iomanager sylar)
target_link_libraries(test_iomanager sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_hook test/test_hook.cc)
add_dependencies(test_hook sylar)
target_link_libraries(test_hook sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_address test/test_address.cc)
add_dependencies(test_address sylar)
target_link_libraries(test_address sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_socket test/test_socket.cc)
add_dependencies(test_socket sylar)
target_link_libraries(test_socket sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_bytearray test/test_bytearray.cc)
add_dependencies(test_bytearray sylar)
target_link_libraries(test_bytearray sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_http test/test_http.cc)
add_dependencies(test_http sylar)
target_link_libraries(test_http sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_http_parser test/test_http_parser.cc)
add_dependencies(test_http_parser sylar)
target_link_libraries(test_http_parser sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_tcp_server test/test_tcp_server.cc)
add_dependencies(test_tcp_server sylar)
target_link_libraries(test_tcp_server sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(echo_server examples/echo_server.cc)
add_dependencies(echo_server sylar)
target_link_libraries(echo_server sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_http_server test/test_http_sever.cc)
add_dependencies(test_http_server sylar)
target_link_libraries(test_http_server sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_http_connection test/tese_connection.cc)
add_dependencies(test_http_connection sylar)
target_link_libraries(test_http_connection sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_uri test/test_uri.cc)
add_dependencies(test_uri sylar)
target_link_libraries(test_uri sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(my_http_server samples/my_http_server.cc)
add_dependencies(my_http_server sylar)
target_link_libraries(my_http_server sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_daemon test/test_deamon.cc)
add_dependencies(test_daemon sylar)
target_link_libraries(test_daemon sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_env test/test_env.cc)
add_dependencies(test_env sylar)
target_link_libraries(test_env sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)

add_executable(test_application test/tese_application.cc)
add_dependencies(test_application sylar)
target_link_libraries(test_application sylar -L/usr/lib -lyaml-cpp -lpthread -ldl -lssl -lcrypto -ljsoncpp)
