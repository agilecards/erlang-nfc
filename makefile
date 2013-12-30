SRCS = c_src/*.cpp
OBJS = $(SRCS:.cpp = .o)
CC = g++
CFLAGS = -c
LDFLAGS =
TARGET = nfc
INCLUDES = /usr/local/include/nfc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@


%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c -I$(INCLUDES) -o $@ $<

clean:
	rm -rf c_src/*o c_src/$(TARGET)