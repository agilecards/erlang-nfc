// erl_nfc.h

#include <nfc/nfc.h>
#include <nfc/nfc-types.h>

class LibnfcManager
{
  public:
    LibnfcManager(){};

    int init_libnfc(int arg);

 private:

    nfc_context *context;
};
