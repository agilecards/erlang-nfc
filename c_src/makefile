SRCS = *.cpp
OBJS = erl_comm.o erl_nfc.o port.o
CC = g++
CFLAGS = -c
LDFLAGS =
TARGET = nfc
INCLUDES = /usr/local/include/nfc
LIBS = /usr/local/lib

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -L$(LIBS) $(OBJS) -o $@ -lnfc

.cpp.o:
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $<

clean:
	rm -rf *o $(TARGET)
