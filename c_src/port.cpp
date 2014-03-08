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
#include "defs.h"
#include <glog/logging.h>


typedef unsigned char byte;

int main(int argc, char *argv[])
{
  int fn, res, len;
  bool stay_alive = 1;
  byte arg;
  char* arg1;
  byte buf[100];
  LibnfcManager *nfcMgr;
  ErlangCommsManager commMgr;

  google::InitGoogleLogging("logfile");

  LOG(INFO) << "Started CPP Port Driver";

  fprintf(stderr,"Started CPP port driver \n");

  nfcMgr = new LibnfcManager();

  while(stay_alive && commMgr.read_cmd(buf) > 0)
    {
      fn = buf[0];
      arg = buf[1];
      arg1 = (char*)&buf[1];

      fprintf(stderr,"cpp port driver: stay_alive = %i \r\n", commMgr.stay_alive());

      fprintf(stderr,"cpp port driver: received command %u with arg %u \r\n",fn, arg);

      // interpret commands from erlang
      switch (fn) {
      case INIT:
        res = nfcMgr->init_libnfc(arg1);
	buf[0] = res;
        len = 1;
	commMgr.write_cmd(RESPONSE,buf,len);
	break;
      case POLL:
	res = nfcMgr->start_polling(buf, &len, arg);
	commMgr.write_cmd(DATA,buf,len);
	break;
      case EXIT:
        fprintf(stderr,"cpp port driver: received command existing \r\n");
        delete nfcMgr;
	stay_alive = 0;
        break;
      }

    }
  return 1;
}
