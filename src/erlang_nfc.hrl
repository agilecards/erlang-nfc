-ifndef(ERLANG_NFC_HRL).
-define(ERLANG_NFC_HRL, true).

% protocol messages

-define(INIT,0).
-define(EXIT,1).
-define(LIST_DEVICES,2).
-define(OPEN_DEVICE,3).
-define(CLOSE_DEVICE,4).
-define(IDLE_DEVICE,5).
-define(INITIATOR_INIT,6).
-define(INITIATOR_START_POLL,7).
-define(INITIATOR_STOP_POLL,8).

-endif.
