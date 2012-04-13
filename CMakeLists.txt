CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(coregl C)

SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(EXEC_PREFIX "\${prefix}")
SET(LIBDIR "\${prefix}/lib")
SET(INCLUDEDIR "\${prefix}/include")
SET(VERSION_MAJOR 1)
SET(VERSION "${VERSION_MAJOR}.1")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

ADD_DEFINITIONS("-DPREFIX=\"${PREFIX}\"")

SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -fvisibility=hidden")
SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -g -O2 -fvisibility=hidden -fPIC -Wall -std=c99 -D_COREGL_EMBEDDED_GL")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")

SET(CMAKE_SKIP_BUILD_RPATH TRUE)

#################################################################
# Build coregl Library
# ------------------------------
SET(COREGL "COREGL")
SET(SRCS_common src/coregl.c src/coregl_thread_pthread.c src/coregl_trace.c
		src/coregl_override.c src/coregl_wrappath.c
		src/coregl_wrappath_egl.c src/coregl_wrappath_gl.c
		src/coregl_fastpath.c src/coregl_fastpath_egl.c
		src/coregl_fastpath_gl.c)
#SET(HEADERS_common src/coregl_fastpath.h src/coregl_fastpath_state.h src/coregl.h src/coregl_internal.h src/coregl_thread_pthread.h src/coregl_wrappath.h)

INCLUDE(FindPkgConfig)
pkg_check_modules(pkg_common REQUIRED x11)
FOREACH(flag ${pkg_common_CFLAGS})
	SET(EXTRA_CFLAGS_common "${EXTRA_CFLAGS_common} ${flag}")
ENDFOREACH(flag)

ADD_LIBRARY(${COREGL} SHARED ${SRCS_common})
SET_TARGET_PROPERTIES(${COREGL} PROPERTIES SOVERSION ${VERSION_MAJOR})
SET_TARGET_PROPERTIES(${COREGL} PROPERTIES VERSION ${VERSION})
#SET_TARGET_PROPERTIES(${COREGL} PROPERTIES COMPILE_FLAGS ${EXTRA_CFLAGS_common})
TARGET_LINK_LIBRARIES(${COREGL} ${pkg_common_LDFLAGS} "-ldl -g -O2 -fvisibility=hidden -Wall -std=c99 -lpthread")

CONFIGURE_FILE(${COREGL}.pc.in ${COREGL}.pc @ONLY)

INSTALL(TARGETS ${COREGL} DESTINATION lib COMPONENT RuntimeLibraries)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${COREGL}.pc DESTINATION lib/pkgconfig)
#FOREACH(hfile ${HEADERS_common})
#	INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/${hfile} DESTINATION include/coregl)
#ENDFOREACH(hfile)
#INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/coregl.h DESTINATION include)

