set(HEADER_FILES
        inc/inventory_node.h inc/stack.h inc/inventory.h inc/stack_node.h)

set(SOURCE_FILES
        src/inventory.cpp src/stack.cpp src/inventory_node.cpp)
include_directories(inc)
add_library(lib_lab_exam STATIC ${SOURCE_FILES} ${HEADER_FILES})