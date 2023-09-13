CC := g++
CFLAGS := -I/usr/include/opencv4/ \
	-I$(mkfile_path)../spike/device/ \
	-I$(mkfile_path)../

LIBS := -lopencv_core -lopencv_videoio -lopencv_imgcodecs

all: background_tasks

background_tasks: main.cpp ../spike/device/RearCamera.cpp ../spike/device/Signal.cpp
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

clean:
	rm -f background_tasks