-module(erlang_nfc).

-export([start/0, start/1, init/1, loop/2]).

-include("erlang_nfc.hrl").

start() ->
  start([]).

start(Options) ->
  spawn_link(erlang_nfc, init, [self()]).

init(Pid) ->
  Port = open_port({spawn, "nfc-port"},[binary,{packet,2}]),
  loop(Pid, Port).

loop(Pid, Port) ->
  receive
 	{init} ->
 	  Port ! {self(),[?INIT]},
 	  loop(Pid, Port)
   end.

