SRCS = *.cpp
OBJS = erl_comm.o erl_nfc.o port.o
CC = g++
CFLAGS = -c
LDFLAGS =
TARGET = nfc
INCLUDES = /usr/local/include

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *o $(TARGET)
