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

BIN = libCOREGL.so

MAJOR = 3
MINOR = 0

WRAP_EGL = libEGL.so
WRAP_GLES2 = libGLESv2.so

OUTPUT_BIN = $(BIN).$(MAJOR).$(MINOR)
OUTPUT_WRAP_EGL = $(WRAP_EGL).$(MAJOR).$(MINOR)
OUTPUT_WRAP_GLES2 = $(WRAP_GLES2).$(MAJOR).$(MINOR)

OBJECTS = $(SOURCES:.c=.o)

all : $(OUTPUT_BIN) $(OUTPUT_WRAP_EGL) $(OUTPUT_WRAP_GLES2)
	cp src/headers/egl.h include/EGL/def_egl.h
	cp src/headers/gl.h include/GLES2/def_gl.h
	cp src/headers/sym_egl.h include/EGL/sym_egl.h
	cp src/headers/sym_gl.h include/GLES2/sym_gl.h

$(OUTPUT_BIN) : $(OBJECTS)
	@mkdir -p lib
	$(CC) -shared -o lib/$(OUTPUT_BIN) $(OBJECTS) $(LDFLAGS)
	ln -sf $(OUTPUT_BIN) lib/$(BIN).$(MAJOR)
	ln -sf $(BIN).$(MAJOR) lib/$(BIN)

$(OUTPUT_WRAP_EGL) :
	@mkdir -p lib
	$(CC) -shared -o lib/$(OUTPUT_WRAP_EGL) src/wraps/coregl_egl.c $(CFLAGS) $(LDFLAGS)
	ln -sf $(OUTPUT_WRAP_EGL) lib/$(WRAP_EGL).$(MAJOR)
	ln -sf $(WRAP_EGL).$(MAJOR) lib/$(WRAP_EGL)

$(OUTPUT_WRAP_GLES2) :
	@mkdir -p lib
	$(CC) -shared -o lib/$(OUTPUT_WRAP_GLES2) src/wraps/coregl_gl.c $(CFLAGS) $(LDFLAGS)
	ln -sf $(OUTPUT_WRAP_GLES2) lib/$(WRAP_GLES2).$(MAJOR)
	ln -sf $(WRAP_GLES2).$(MAJOR) lib/$(WRAP_GLES2)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :
	rm -f $(OBJECTS) lib/*

