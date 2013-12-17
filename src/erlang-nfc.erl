-module(erlang-nfc).

-export([start/0, start/1, init/1, loop/2]).

start() ->
  start([]).

start(Options) ->
  Pid = spawn_link(erlang-nfc, init, [self()]).

init(Pid) ->
  Port = open_port({spawn, priv_dir()++"/bin/nfc-port"},[binary,{packet,2}]),
  loop(Pid, Port).

loop(Pid, Port) ->
  receive
 	{init} ->
 	  Port ! {self(),[?INIT]},
 	  loop(Pid, Port)
   end

