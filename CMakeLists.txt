add_library(lumberjack lumberjack.cpp)

option(lumberjack_COMPILE_INFO "whether to compile info logging calls" ON)
option(lumberjack_COMPILE_WARNINGS "whether to compile warnings or not" ON)
option(lumberjack_COMPILE_NONE "if this is on, all logging calls are compiled to nothing" OFF)

# Determine the operating system name
if (WIN32)
    set(OS_NAME "Windows")
elseif (APPLE)
    set(OS_NAME "macOS")
elseif (UNIX)
    set(OS_NAME "Unix")
else ()
    set(OS_NAME "Unknown")
endif ()

configure_file(lumberjack_config.h.in lumberjack_config.h)

target_include_directories(lumberjack
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)


install(TARGETS lumberjack DESTINATION lib)
INSTALL(FILES lumberjack.h lumberjack_config.h DESTINATION include)
