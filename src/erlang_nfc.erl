-module(erlang_nfc).

-export([start/1, init/1, loop/1, init_nfc/0]). 

-include("erlang_nfc.hrl").

init(ExtPrg) ->
    register(nfc, self()),
    process_flag(trap_exit,true),
    Port = open_port({spawn, ExtPrg}, [use_stdio,{packet,2}]),
    loop(Port).

loop(Port) ->
    receive
	{call, Caller, Msg} ->
	    port_command(Port, encode(Msg)),
	    receive
		{Port, {data, Data}} ->
		    Caller ! {nfc, decode(Data)}
	    end,
	    loop(Port);
	stop ->
	    Port ! {self(), close},
	    receive
		{Port, closed} ->
		    exit(normal)
	    end;
	{'EXIT', Port, Reason} ->
	    exit(port_terminated)
    end.

encode({init, X}) ->
    [1,X].

decode([Int]) ->
    Int.


%% client API

start(ExtPrg) ->
    spawn_link(?MODULE, init, [ExtPrg]).

init_nfc() ->
    call_port({init,[]}).

call_port(Msg) ->
    nfc ! {call, self(), Msg},
    receive
        {nfc, Result} ->
	    Result
    end.

