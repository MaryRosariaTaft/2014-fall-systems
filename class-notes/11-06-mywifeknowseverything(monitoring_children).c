/*

wait(int *status) <unistd.h>

stops a parents process from running until any child has changed its status (e.g. running-->completed, running-->terminated, foreground-->background, etc.)

return value is the PID of the process which caused wait to end

the parameter is used to store info about the child processes' status

note: if a child process seg faults, the parent will still be fine (until it seg faults, too, as all things ultimately do)

------

exit(int status) <stdlib.h>

WEXITSTATUS <unistd.h>

------

11-07 (continuation)

WIFEXITED, WIFSIGNALED, WIFSTOPPED, etc.

waitpid(pid, status, options), <unistd.h>

>pid --> the pid of the specific child to look for
>note: function will act like regular wait (single-param) if you pass -1 as the pid

>options --> waits for a certain type of behavior
> passing 0 will make it run normally

------

exec functions <unistd.h> - run built-in or existing programs from within another (e.g. running a web browser from a program we write in class)
>however, the program you execute takes over your own code and will prevent [the rest of] your code from running

execl(<PATH>, <COMMAND>, <ARGS>, NULL)

*
NOTE: which/whereis - command that returns the path of an executable file (e.g. 'which ls')
*

PATH: path to the program (e.g. "/bin/ls")
COMMAND: name of the program (e.g. "ls")
ARGS: command-line arguments (e.g. "-l")
NULL is a necessary last parameter

*/
