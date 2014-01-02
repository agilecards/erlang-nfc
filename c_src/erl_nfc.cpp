// erl_nfc.cpp

#include "erl_nfc.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "erl_comm.h"

LibnfcManager::LibnfcManager()
{
  cardTypes = new nfc_modulation[1];

  cardTypes[0].nmt =  NMT_ISO14443A;
  cardTypes[0].nbr =  NBR_106;
  /*
  cardTypes[1].nmt =  NMT_ISO14443B;
  cardTypes[1].nbr =  NBR_106;
  cardTypes[2].nmt =  NMT_FELICA;
  cardTypes[2].nbr =  NBR_212;
  cardTypes[3].nmt =  NMT_FELICA;
  cardTypes[3].nbr =  NBR_424;
  cardTypes[4].nmt =  NMT_JEWEL;
  cardTypes[4].nbr =  NBR_106;
  */
}
   
LibnfcManager::~LibnfcManager()
{
  if (pnd != NULL) nfc_close(pnd);
  if (context != NULL) nfc_exit(context);

  delete [] cardTypes;

}

int LibnfcManager::init_libnfc(int arg)
{
  fprintf(stderr,"nfc: entered init_libnfc \r\n");
  
  nfc_init(&context);

  if(context == NULL){
    fprintf(stderr,"LibnfcManager: Unable to initialise libnfc (malloc)\r\n");
    return 0;
  }
  fprintf(stderr,"LibnfcManager: Successfully initialised libnfc \r\n");

  pnd = nfc_open(context, NULL);

  if(pnd == NULL){
    fprintf(stderr,"LibnfcManager: Unable to open nfc device\r\n");
    nfc_exit(context);
    return 0;
  }
  fprintf(stderr,"LibnfcManager: Successfully opened device \r\n");

  if( nfc_initiator_init(pnd) <0){
    fprintf(stderr,"LibnfcManager: Unable to init nfc device as initiator\r\n");
    nfc_close(pnd);
    nfc_exit(context);
    return 0;
  }

  fprintf(stderr,"LibnfcManager: Device ready for polling \r\n");

  return 1;

}

int LibnfcManager::start_polling(byte* buf, int* len)
{
  int res;

  if( (res = nfc_initiator_poll_target(pnd, cardTypes, szModulations, uiPollNr, uiPeriod, &nt)) < 0)
  {
    nfc_perror(pnd,"nfc_initiator_poll_target");  
    fprintf(stderr,"LibnfcManager: Error polling target \r\n");
    // nfc_close(pnd);
    // nfc_exit(context);
    return res;
  };
  if( res > 0 ){
    // print_nfc_target(&nt, verbose);
  fprintf(stderr,"LibnfcManager: Target found \r\n");
  // serialise card details
  // return card details 
  // cm->write_cmd(nt.nti.nai.abtUid,10);
  *len = 4; 
  memcpy(buf, nt.nti.nai.abtUid, *len);

  } else {
  fprintf(stderr,"LibnfcManager: No target found \r\n");
  }
  
  return res;
}

int LibnfcManager::stop_polling()
{

  return 1;
}



/*
notes:

have realised that the polling method above will poll for a certain amount of time
and return as soon as it sees a card or when the time is up.

Best way to use this seems to be for eht erlang process to request a poll and process the result.

It immediately fires of another poll and then forwards the card details if there was one found.

*/

