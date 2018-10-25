set(lib_string_SRCS lib_string.h lib_string.c)


add_library(lib_string STATIC ${lib_string_SRCS})
add_library(lib_string-shared SHARED ${lib_string_SRCS})
set_target_properties(lib_string-shared PROPERTIES OUTPUT_NAME lib_string)