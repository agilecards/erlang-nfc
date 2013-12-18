//nfc.c
#include <stdio.h>

/*
  methods for interacting with libnfc
*/


// init libnfc
int init_libnfc() {
  fprintf(stderr,"nfc: entered init_libnfc \r\n");
  return 1;
}

// exit libnfc
int exit_libnfc() {
  return 1;
}

// list devices


// open a device


// close a device


// make device idle


// setup device as nfc reader (initiator)


// start initiator polling for tags


