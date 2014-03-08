SRCS = *.cpp
OBJS = erl_comm.o erl_nfc.o port.o
CC = g++
CFLAGS = -c
LDFLAGS =
TARGET = nfc
INCLUDES = -I/usr/local/include/nfc -I/usr/local/include
LIBDIRS = -L/usr/local/lib
LIBS = -lnfc -lglog

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(LIBDIRS) $(OBJS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -rf *o $(TARGET)
