// erl_comm.h

typedef unsigned char byte;

class ErlangCommsManager
{
 public:
  ErlangCommsManager(){};

  int read_cmd(byte *buf);
  int write_cmd(byte *buf, int len);

 private:

  int read_exact(byte *buf, int len);
  int write_exact(byte *buf, int len);
};
