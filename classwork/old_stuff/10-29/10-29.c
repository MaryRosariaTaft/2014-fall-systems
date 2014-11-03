/*

  file redirection --> changing the usual input/output behavior of a program (e.g. reading/writing from a file or such instead of the command line)

  '>' --> redirects stdout to a file; overwrites the contents of that file

  syntax: <COMMAND> > <FILE>

  example: ls > file_list.txt --> prints return of 'ls' into 'file_list.txt' instead of to the terminal

  NOTE: CTRL+D IS AN END-OF-FILE INDICATOR IN THE TERMINAL

  '>>' --> appends instead of overwriting

  '2>' --> redirects stderr (standard error) to a file; overwrites that file

  (normal behavior of stderr --> prints to the terminal; e.g. "No such file or directory")

  '2>>' won't overwrite

  example: cat nonexistent_file 2> errors.txt
  --> if nonexistent_file doesn't exist, errors.txt will now contain "No such file or directory"

  example of usage: tracking errors in an ongoing program which has a lot of other stdout (so the errors don't get mixed in)

  ***
  file descriptors in standard file table:
  0: stdin
  1: stdout
  2: stderr
  ***

  '&>' --> redirects stdout AND stderr

  '>' --> redirects stdin

  syntax: <COMMAND> < <FILE>

  example of usage: testing a program that would otherwise require user input

  (./a.out < commands.txt)

  '|' --> "pipe"; redirects stdout from one command to stdin of the next

  syntax: <COMMAND1> | <COMMAND2>

  example: ls | wc --> will return the word count of the output of 'ls' (i.e. the number of files you have wherever you used ls)

  __________________________________

  redirection in C programs:

  dup2 from <unistd.h> --> redirects one file descriptor to another

  syntax: dup2(fd1,fd2) //file descriptors
  --> redirects fd2 to fd1

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* int main(){ */

/*   int fd; */
/*   fd = open("file_list.txt", O_WRONLY | O_TRNCH); */

/*   dup2(fd,STDOUT_FILENO); // standard out file number, which is 2 */

/*   printf("stuff\n"); */

/*   close(fd); */

/* } */

/*

  the above code will print "stuff" INTO FILE_LIST.TXT instead of into the terminal

BUT you've now lost any reference to the original fd2 (here, the program can't return to terminal output)

so, there's another function:

dup(fd)

--> duplicates an existing entry in the file table, then returns a new file descriptor for the duplicate entry

*/

int main(){

  int fd1, fd2;

  fd1 = dup(STDOUT_FILENO); //sets fd1's file table entry to std out

  dup2(fd2, STDOUT_FILENO); //sets STDOUT_FILENO's entry to fd2, some other open file

  dup2(fd1,STDOUT_FILENO); //sets STDOUT_FILENO's entry to fd1, which is stdout

  printf("stuff\n");

  close(fd);

}

