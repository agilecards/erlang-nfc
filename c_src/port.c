// port.c

/*
this works for request/response type of API, but won't work for async data coming from
card reader.

Will get this working first, and then work out how to do the loop that hadnles both commands coming
from erlang AND data coming from card reader which needs to be sent asynchronously to the erlang 
onnected process
*/
#include <stdio.h>


typedef unsigned char byte;

int main()
{
  int fn, arg, res;
  byte buf[100];

  fprintf(stderr,"Started C port driver \n");

  while(read_cmd(buf) > 0)
    {
      fn = buf[0];
      arg = buf[1];

      fprintf(stderr,"port driver: received command %u with arg %u \r\n",fn, arg);

      // interpret commands from erlang
      if (fn == 1) {
        res = init_libnfc(arg);
      };

      buf[0] = res;
      write_cmd(buf,1);
    }
  return 1;
}
