project(boost_tutorial)

cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()

include_directories(/usr/local/include)

link_directories(/usr/local/lib)
set(REQUIRED_LIB boost_thread boost_system)

macro (make_exec name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} ${REQUIRED_LIB})
endmacro (make_exec)

make_exec(any)
make_exec(function)
make_exec(make_shared)
make_exec(property_tree)
make_exec(smart_pointer)
# make_exec(thread)
