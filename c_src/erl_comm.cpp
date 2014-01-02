// erl_comm.cpp

#include <stdio.h>
#include <unistd.h>
#include "erl_comm.h"
#include "defs.h"

int  ErlangCommsManager::read_exact(byte *buf, int len)
{
  int i, got = 0;

  do {
    if ((i = read(0, buf+got, len-got)) <= 0)
      return(i);
    got += i;
  } while (got<len);

  return(len);
}

int  ErlangCommsManager::write_exact(byte *buf, int len)
{
  int i, wrote = 0;

  do {
    if ((i = write(1, buf+wrote, len-wrote)) <= 0)
      return(i);
    wrote += i;
  } while (wrote<len);

  return len;
}
int  ErlangCommsManager::read_cmd(byte *buf)
{
  int len;

  fprintf(stderr,"entered read_cmd \r\n");

  if ( read_exact(buf,2) != 2)
    return(-1);
  len = (buf[0] << 8) | buf[1];
  return read_exact(buf, len);
}

int  ErlangCommsManager::write_cmd(int packetType, byte *buf, int len)
{
  byte li;
  byte type;

  fprintf(stderr,"entered write_cmd \r\n");

  /*
 protocol is: 
 2 bytes   - # bytes in message
 1 byte    - message type (1:data/2:response)
 len bytes - message bytes

 need to add 1 to len to account for message type byte
 then output message length before message type and message
  */
  int totalLen = len + 1;

  li = (totalLen >> 8) & 0xff;
  write_exact(&li, 1);

  li = totalLen & 0xff;
  write_exact(&li, 1);
  
  switch (packetType){
  case DATA:
    type = 0x01;
    write_exact(&type,1);
    break;
  case RESPONSE:
    type = 0x02;
    write_exact(&type,1);
    break;
  }
  return write_exact(buf, len);
}


