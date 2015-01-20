/*

basic server
- server creates well-known pipe
- server _opens_ the aforementioned well-known pipes and waits for a connection
- client creates a private pipe (although it's also a named pipe)
- client connects to a server and send its own private pipe's name
- client waits for server to connect to its private pipe
- server receives client's message and removes its well-known pipe
- server sends an initial acknowledgement message to the client pipe
- client receives server's mesage, then removes its private pipe
- once the client exits, create a new well-known pipe so that a new client can access the server

forking server
- steps 1-5 same as above
- server receives client's message and forks off a subserver
- main server removes the well-known pipe and closes the connection with the client
- main server creates a new well-knwon pipes and waits for a new client
- subserver connects to the new client pipe, sending an initial acknowledgement message
- client receives server's message, then removes its private pipe
- etc. etc. etc.
* problems as above designed: clients can't connect with one another (nor subservers)
   > possible change: unnamed pipe between subservers


 */
