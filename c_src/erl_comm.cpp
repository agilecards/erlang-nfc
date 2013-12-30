// erl_comm.cpp

#include <stdio.h>
#include <unistd.h>
#include "erl_comm.h"

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

int  ErlangCommsManager::write_cmd(byte *buf, int len)
{
  byte li;

  fprintf(stderr,"entered write_cmd \r\n");

  li = (len >> 8) & 0xff;
  write_exact(&li, 1);

  li = len & 0xff;
  write_exact(&li, 1);

  return write_exact(buf, len);
}


