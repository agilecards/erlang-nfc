// port.cpp

/*
this works for request/response type of API, but won't work for async data coming from
card reader.

Will get this working first, and then work out how to do the loop that hadnles both commands coming
from erlang AND data coming from card reader which needs to be sent asynchronously to the erlang 
onnected process
*/
#include <stdio.h>
#include "erl_comm.h"
#include "erl_nfc.h"


typedef unsigned char byte;

int main()
{
  int fn, arg, res;
  byte buf[100];
  LibnfcManager nfcMgr;
  ErlangCommsManager commMgr;

  fprintf(stderr,"Started CPP port driver \n");


  while(commMgr.read_cmd(buf) > 0)
    {
      fn = buf[0];
      arg = buf[1];

      fprintf(stderr,"cpp port driver: received command %u with arg %u \r\n",fn, arg);

      // interpret commands from erlang
      switch (fn) {
      case 1:
        res = nfcMgr.init_libnfc(arg);
	break;
      case 7:
	res = nfcMgr.start_polling();
	break;
      }

      buf[0] = res;
      commMgr.write_cmd(buf,1);
    }
  return 1;
}
