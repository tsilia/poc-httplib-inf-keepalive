# poc-httplib-inf-keepalive
POC illustrating the 'huge keep alives' issue with cpphttplib.

1. Server sets high max_keep_alives and listens to a port
2. Client constantly posts data to the server
3. Attempt to stop the server leads to nothing, it's still running
4. Once the client stops, the server does so, too.
