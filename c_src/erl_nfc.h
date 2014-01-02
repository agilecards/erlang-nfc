// erl_nfc.h

#include <nfc/nfc.h>
#include <nfc/nfc-types.h>


class ErlangCommsManager;

class LibnfcManager
{
  public:
    LibnfcManager();
    ~LibnfcManager();

    int init_libnfc(char* arg);
    int start_polling(uint8_t* buf, int* len, uint8_t numPolls);
    int stop_polling(); 

 private:

    nfc_context *context;
    nfc_device  *pnd;
    nfc_target nt;
    nfc_modulation* cardTypes;

    uint8_t uiPollNr;
    static const uint8_t uiPeriod = 2;
    static const size_t szModulations = 1;

    char* serialise_card(nfc_target);

};
