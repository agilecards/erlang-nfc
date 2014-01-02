-module(erlang_nfc).

-export([start/0, start/1, init/1, loop/2, start_polling/1, stop_polling/1]). 

-include("erlang_nfc.hrl").

init(Pid) ->
						% register(nfc, self()),
    process_flag(trap_exit,true),
    Port = open_port({spawn, './nfc'}, [use_stdio,{packet,2}]),
    loop(Pid,Port).

loop(Pid,Port) ->
						% receive options from calling process
						% send and receive polling data from Port process
						% C++ process will poll devices and send a message once a tag is detected
						% so once tag message is received, need to tell C++ to start polling again.
						% maybe do this by having a start_polling option which sends the first poll request
						% and then the processing of the reply kicks off the new poll request

    receive
        {Port, {data, Bytes}} ->
            Pid ! {data, Bytes},
            port_command(Port, encode({poll,[]})),
            loop(Pid,Port);

        {Port, {response, Response}} ->
            handle_response({command, Response}),
            loop(Pid,Port);
        
	{init, ConnString} ->
	    port_command(Port, encode({init, ConnString})),
	        receive
		    {Port, {data, Response}} ->
		        handle_response({init, Response})
		end,
		loop(Pid,Port);

	{startpolling} ->
	    port_command(Port, encode({poll,[]})),
	    loop(Pid,Port);

	{stoppolling} ->
            done
	    
    end.

encode({init, X}) ->
    [1,X];
encode({poll,X}) ->
    [2,X].

handle_response({init, Response}) ->
    done;
handle_response({command, Response}) ->
    done.


%% client API

start() ->
    start([]).

start(Options) ->
    Pid = spawn_link(?MODULE, init, [self()]),
    process_options(Pid,Options),
    Pid.

process_options(_Pid,[]) -> done;
process_options(Pid,[Opt|Opts]) ->
    Pid ! Opt,
    process_options(Pid,Opts). 

start_polling(Pid) ->
    Pid ! {startpolling},
    done.

stop_polling(Pid) ->
    Pid ! {stoppolling}.
