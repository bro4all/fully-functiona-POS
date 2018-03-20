set(HEADER_FILES
        inc/node.h inc/stack.h inc/inventory.h)

set(SOURCE_FILES
        src/inventory.cpp src/stack.cpp)
include_directories(inc)
add_library(lib_lab_exam STATIC ${SOURCE_FILES} ${HEADER_FILES})