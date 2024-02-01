set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

if(QC_BUILD_STATIC)
    add_library(${PROJECT_NAME} STATIC)
else()
    add_library(${PROJECT_NAME} SHARED)
endif()
add_library(wangwenx190::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
)

if(WIN32 AND NOT QC_BUILD_STATIC)
    qm_add_win_rc_enhanced(${PROJECT_NAME}
        NAME "Qt Crypto"
        VERSION "${PROJECT_VERSION}"
        DESCRIPTION "A very simple crypto library for Qt."
    )
endif()

set(HEADERS
    qtcrypto_global.h
    bigint.h
    mini-gmp.h
    qaesencryption.h
    qrsaencryption.h
)
target_sources(${PROJECT_NAME} PRIVATE ${HEADERS})

target_sources(${PROJECT_NAME} PRIVATE
    bigint.cpp
    mini-gmp.c
    qaesencryption.cpp
    qrsaencryption.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    QTCRYPTO_BUILD_LIBRARY
)

if(QC_BUILD_STATIC)
    target_compile_definitions(${PROJECT_NAME} PUBLIC
        QTCRYPTO_BUILD_STATIC
    )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt6::Core
)

if(QC_ENABLE_INSTALL)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
    if(MSVC)
        install(FILES "$<TARGET_PDB_FILE:${PROJECT_NAME}>" DESTINATION "${CMAKE_INSTALL_BINDIR}" OPTIONAL)
    endif()
    install(FILES ${HEADERS} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
endif()
