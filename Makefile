CC = gcc

CFLAGS = -g -O2 -fvisibility=hidden -fPIC -Wall -std=c99


LDFLAGS = -g -O2 -fvisibility=hidden -Wall -std=c99 -ldl -lpthread


SOURCES = \
		src/coregl.c \
		src/coregl_thread_pthread.c \
		src/coregl_trace.c \
		src/coregl_export.c \
		src/coregl_export_egl.c \
		src/coregl_export_gl.c \
		src/modules/coregl_module.c \
		\
		src/modules/tracepath/coregl_tracepath.c \
		src/modules/tracepath/coregl_tracepath_egl.c \
		src/modules/tracepath/coregl_tracepath_gl.c \
		\
		src/modules/fastpath/coregl_fastpath.c \
		src/modules/fastpath/coregl_fastpath_egl.c \
		src/modules/fastpath/coregl_fastpath_gl.c \
		\
		src/modules/appopt/coregl_appopt.c \
		src/modules/appopt/coregl_appopt_egl.c \
		src/modules/appopt/coregl_appopt_gl.c

BIN = libCOREGL.so.1.1

OBJECTS = $(SOURCES:.c=.o)

all : $(BIN)
	ln -sf $(BIN) lib/libEGL.so.1.4
	ln -sf $(BIN) lib/libGLESv2.so.2.0
	cp src/headers/egl.h include/EGL/def_egl.h
	cp src/headers/gl.h include/GLES2/def_gl.h
	cp src/headers/sym_egl.h include/EGL/sym_egl.h
	cp src/headers/sym_gl.h include/GLES2/sym_gl.h
#	ln -sf `readlink -f /usr/lib/libEGL.so` lib/libEGL_drv.so
#	ln -sf `readlink -f /usr/lib/libGLESv2.so` lib/libGLESv2_drv.so

$(BIN) : $(OBJECTS)
	@mkdir -p lib
	$(CC) -shared -o lib/$(BIN) $(OBJECTS) $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJECTS) lib/$(BIN)

