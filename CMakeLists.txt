cmake_minimum_required (VERSION 2.6)
project (cef_test_app)

# Configure MSVC runtime library ('/MD' or 'MT')
include (./configure_msvc_runtime.cmake)
configure_msvc_runtime ()

include_directories (
    .
    ..
    ../include
    ../libcef_dll
)
add_definitions (
    -DUNICODE
    -D_UNICODE
    -DOS_WIN
    -DUSE_CEF_SHARED
)
set (COMMON_LIBS
    opengl32.lib
    glu32.lib
)

find_library (LIBCEF libcef ../Release)
find_library (LIBCEF_WRAPPER libcef_dll_wrapper ../Release)
if (NOT LIBCEF OR NOT LIBCEF_WRAPPER)
    message(FATAL_ERROR "libcef or libcef_dll_wrapper not found")
endif ()

# sub-process target
set (subproc test_subprocess)
set (${subproc}_HEADERS
    test_app.h
    test_handler.h
    util.h
)
set (${subproc}_SOURCES
    test_subprocess_win.cpp
    test_app.cpp
    test_handler.cpp
    test_handler_win.cpp
)
add_executable (${subproc} ${${subproc}_SOURCES})
add_dependencies (${subproc} ${${subproc}_HEADERS} ${${subproc}_SOURCES})
target_link_libraries (${subproc}
    ${COMMON_LIBS}
    ${LIBCEF}
    ${LIBCEF_WRAPPER}
)

# main executable
set (main cef_test_app)
set (${main}_HEADERS
    test_app.h
    test_handler.h
    util.h
)
set (${main}_SOURCES
    test_win.cpp
    test_app.cpp
    test_handler.cpp
    test_handler_win.cpp
)
add_executable (${main} ${${main}_SOURCES})
add_dependencies (${main} ${${main}_HEADERS} ${${main}_SOURCES})
target_link_libraries (${main}
    ${COMMON_LIBS}
    ${LIBCEF}
    ${LIBCEF_WRAPPER}
)

# install
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR})
install (TARGETS ${subproc} ${main} DESTINATION ../out/Release)
