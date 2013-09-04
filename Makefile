CC = gcc

COMPILE_DATE = "\"`git log -1 --pretty=format:%ci`\""

CFLAGS = -g -O2 -fvisibility=hidden -fPIC -Wall -std=c99 -D_COREGL_COMPILE_DATE=$(COMPILE_DATE)
CFLAGS += `pkg-config --cflags dlog`

LDFLAGS = -g -O2 -fvisibility=hidden -Wall -std=c99 -ldl -lpthread
LDFLAGS += `pkg-config --libs dlog`


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

COREGL_MAJOR = 3
COREGL_MINOR = 0

EGL_MAJOR = 1
EGL_MINOR = 4

GLESv2_MAJOR = 2
GLESv2_MINOR = 0

WRAP_EGL = libEGL.so
WRAP_GLES2 = libGLESv2.so

OUTPUT_BIN = $(BIN).$(COREGL_MAJOR).$(COREGL_MINOR)
OUTPUT_WRAP_EGL = $(WRAP_EGL).$(EGL_MAJOR).$(EGL_MINOR)
OUTPUT_WRAP_GLES2 = $(WRAP_GLES2).$(GLESv2_MAJOR).$(GLESv2_MINOR)

OBJECTS = $(SOURCES:.c=.o)

all : $(OUTPUT_BIN) $(OUTPUT_WRAP_EGL) $(OUTPUT_WRAP_GLES2)
	cp src/headers/egl.h include/EGL/def_egl.h
	cp src/headers/gl.h include/GLES3/def_gl.h
	cp src/headers/sym_egl.h include/EGL/sym_egl.h
	cp src/headers/sym_gl.h include/GLES3/sym_gl.h

$(OUTPUT_BIN) : $(OBJECTS)
	@mkdir -p lib
	$(CC) -shared -o lib/$(OUTPUT_BIN) $(OBJECTS) $(LDFLAGS)
	ln -sf $(OUTPUT_BIN) lib/$(BIN).$(COREGL_MAJOR)
	ln -sf $(BIN).$(COREGL_MAJOR) lib/$(BIN)

$(OUTPUT_WRAP_EGL) :
	@mkdir -p lib
	$(CC) -shared -o lib/$(OUTPUT_WRAP_EGL) src/wraps/coregl_egl.c $(CFLAGS) $(LDFLAGS)
	ln -sf $(OUTPUT_WRAP_EGL) lib/$(WRAP_EGL).$(EGL_MAJOR)
	ln -sf $(WRAP_EGL).$(EGL_MAJOR) lib/$(WRAP_EGL)

$(OUTPUT_WRAP_GLES2) :
	@mkdir -p lib
	$(CC) -shared -o lib/$(OUTPUT_WRAP_GLES2) src/wraps/coregl_gl.c $(CFLAGS) $(LDFLAGS)
	ln -sf $(OUTPUT_WRAP_GLES2) lib/$(WRAP_GLES2).$(GLESv2_MAJOR)
	ln -sf $(WRAP_GLES2).$(GLESv2_MAJOR) lib/$(WRAP_GLES2)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :
	rm -f $(OBJECTS) lib/*

