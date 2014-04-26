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
    #    -DV8_DEPRECATION_WARNINGS
    #    -D_WIN32_WINNT=0x0602
    #    -DWINVER=0x0602
    #    -D_WINDOWS
    #    -DNOMINMAX
    #    -DPSAPI_VERSION=1
    #    -D_CRT_RAND_S
    #    -D_STD_C
    #    -D_CRT_SECURE_NO_DEPRECATE
    #    -D_SCL_SECURE_NO_DEPRECATE
    #    -DNTDDI_VERSION=0x06020000
    #    -D_USING_V110_SDK71_
    #    -DCLD_VERSION=2
    #    -D_STDC_CONSTANT_MACROS
    #    -D_STDC_FORMAT_MACROS
    #    -DNVALGRIND
    #    -DDYNAMIC_ANNOTATIONS_ENABLED=0
    #    -DCERT_CHAIN_PARA_HAS_EXTRA_FIELDS
    #    -DWIN32_LEAN_AND_MEAN
    #    -D_ATL_NO_OPENGL
    #    -D_HAS_EXCEPTIONS=0
    #    -D_SECURE_ATL
    #    -DCHROMIUM_BUILD
    #    -DTOOLKIT_VIEWS=1
    #    -DUSE_AURA=1
    #    -DUSE_ASH=1
    #    -DUSE_LIBJPEG_TURBO=1
    #    -DICU_UTIL_DATA_IMPL=ICU_UTIL_DATA_SHARED
    #    -DENABLE_ONE_CLICK_SIGNIN
    #    -DENABLE_WEBRTC=1
    #    -DENABLE_PEPPER_CDMS
    #    -DENABLE_CONFIGURATION_POLICY
    #    -DENABLE_INPUT_SPEECH
    #    -DENABLE_NOTIFICATIONS
    #    -DENABLE_EGLIMAGE=1
    #    -DENABLE_TASK_MANAGER=1
    #    -DENABLE_EXTENSIONS=1
    #    -DENABLE_PLUGIN_INSTALLATION=1
    #    -DENABLE_PLUGINS=1
    #    -DENABLE_SESSION_SERVICE=1
    #    -DENABLE_THEMES=1
    #    -DENABLE_AUTOFILL_DIALOG=1
    #    -DENABLE_BACKGROUND=1
    #    -DENABLE_AUTOMATION=1
    #    -DENABLE_GOOGLE_NOW=1
    #    -DENABLE_FULL_PRINTING=1
    #    -DENABLE_PRINTING=1
    #    -DENABLE_SPELLCHECK=1
    #    -DENABLE_CAPTIVE_PORTAL_DETECTION=1
    #    -DENABLE_APP_LIST=1
    #    -DENABLE_SETTINGS_APP=1
    #    -DENABLE_MANAGED_USERS=1
    #    -DENABLE_MDNS=1
)
set (COMMON_LIBS
    #    wininet.lib
    #    dnsapi.lib
    #    version.lib
    #    msimg32.lib
    #    ws2_32.lib
    #    usp10.lib
    #    psapi.lib
    #    dbghelp.lib
    #    winmm.lib
    #    shlwapi.lib
    #    odbc32.lib
    #    odbccp32.lib
    #    delayimp.lib
    #    credui.lib
    #    netapi32.lib
    #    comctl32.lib
    #    rpcrt4.lib
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
