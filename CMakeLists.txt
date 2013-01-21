CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(coregl C)

SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(EXEC_PREFIX "\${prefix}")
SET(LIBDIR "\${prefix}/lib")
SET(INCLUDEDIR "\${prefix}/include")
SET(VERSION_MAJOR 3)
SET(VERSION "${VERSION_MAJOR}.0")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

ADD_DEFINITIONS("-DPREFIX=\"${PREFIX}\"")

EXEC_PROGRAM(date OUTPUT_VARIABLE COMPILE_DATE)
ADD_DEFINITIONS("-D_COREGL_COMPILE_DATE=\"${COMPILE_DATE}\"")

SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -fvisibility=hidden")
SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -g -O2 -fPIC -Wall -std=c99 -D_COREGL_EMBEDDED_GL")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")

SET(CMAKE_SKIP_BUILD_RPATH TRUE)

#################################################################
# Build coregl Library
# ------------------------------
SET(COREGL "COREGL")
SET(SRCS_common
		src/coregl.c
		src/coregl_thread_pthread.c
		src/coregl_trace.c
		src/coregl_export.c
		src/coregl_export_egl.c
		src/coregl_export_gl.c
		src/modules/coregl_module.c
		src/modules/tracepath/coregl_tracepath.c
		src/modules/tracepath/coregl_tracepath_egl.c
		src/modules/tracepath/coregl_tracepath_gl.c

		src/modules/fastpath/coregl_fastpath.c
		src/modules/fastpath/coregl_fastpath_egl.c
		src/modules/fastpath/coregl_fastpath_gl.c

		src/modules/appopt/coregl_appopt.c
		src/modules/appopt/coregl_appopt_egl.c
		src/modules/appopt/coregl_appopt_gl.c
)
#################################################################
# Build egl Library
# ------------------------------
SET(EGL "EGL")
SET(EGL_SRCS_common
		src/wraps/coregl_egl.c
)
#################################################################
# Build gles2 Library
# ------------------------------
SET(GLES2 "GLESv2")
SET(GLES2_SRCS_common
		src/wraps/coregl_gl.c
)



#SET(HEADERS_common src/coregl_export.h src/coregl_fastpath.h src/coregl_fastpath_state.h src/coregl.h src/coregl_internal.h src/coregl_thread_pthread.h src/coregl_wrappath.h)

INCLUDE(FindPkgConfig)
pkg_check_modules(pkg_common REQUIRED x11)
FOREACH(flag ${pkg_common_CFLAGS})
	SET(EXTRA_CFLAGS_common "${EXTRA_CFLAGS_common} ${flag} -lGLESv2_drv -lEGL_drv")
ENDFOREACH(flag)

ADD_LIBRARY(${COREGL} SHARED ${SRCS_common})
SET_TARGET_PROPERTIES(${COREGL} PROPERTIES SOVERSION ${VERSION_MAJOR})
SET_TARGET_PROPERTIES(${COREGL} PROPERTIES VERSION ${VERSION})
#SET_TARGET_PROPERTIES(${COREGL} PROPERTIES COMPILE_FLAGS ${EXTRA_CFLAGS_common})
TARGET_LINK_LIBRARIES(${COREGL} ${pkg_common_LDFLAGS} "-ldl -g -O2 -fvisibility=hidden -Wall -std=c99 -lpthread")

ADD_LIBRARY(${EGL} SHARED ${EGL_SRCS_common})
SET_TARGET_PROPERTIES(${EGL} PROPERTIES SOVERSION ${VERSION_MAJOR})
SET_TARGET_PROPERTIES(${EGL} PROPERTIES VERSION ${VERSION})
#SET_TARGET_PROPERTIES(${COREGL} PROPERTIES COMPILE_FLAGS ${EXTRA_CFLAGS_common})
TARGET_LINK_LIBRARIES(${EGL} ${pkg_common_LDFLAGS} "-ldl -g -O2 -fvisibility=hidden -Wall -std=c99 -lpthread")

ADD_LIBRARY(${GLES2} SHARED ${GLES2_SRCS_common})
SET_TARGET_PROPERTIES(${GLES2} PROPERTIES SOVERSION ${VERSION_MAJOR})
SET_TARGET_PROPERTIES(${GLES2} PROPERTIES VERSION ${VERSION})
#SET_TARGET_PROPERTIES(${COREGL} PROPERTIES COMPILE_FLAGS ${EXTRA_CFLAGS_common})
TARGET_LINK_LIBRARIES(${GLES2} ${pkg_common_LDFLAGS} "-ldl -g -O2 -fvisibility=hidden -Wall -std=c99 -lpthread")

CONFIGURE_FILE(${COREGL}.pc.in ${COREGL}.pc @ONLY)

INSTALL(TARGETS ${COREGL} DESTINATION lib COMPONENT RuntimeLibraries)
INSTALL(TARGETS ${EGL} DESTINATION lib COMPONENT RuntimeLibraries)
INSTALL(TARGETS ${GLES2} DESTINATION lib COMPONENT RuntimeLibraries)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${COREGL}.pc DESTINATION lib/pkgconfig)

#FOREACH(hfile ${HEADERS_common})
#	INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/${hfile} DESTINATION include/coregl)
#ENDFOREACH(hfile)
#INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/coregl.h DESTINATION include)

