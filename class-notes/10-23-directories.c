/*

Where do CS priests live?
In directory!

a directory is a file containing the names of the files within the directory along with basic information like file type

moving files into / out of a directory means changing the directory file, not actually moving any other data

C Commands:
getcwd(char* buffer, size) <unistd.h> - get current working directory
chdir(<PATH>) <unistd.h> - change directory; returns 0 if successful; sets 'errno' if change doesn't work and then returns -1
opendir(<PATH>) <dirent.h> - reads the content of a directory file *without* changing the working directory; returns a pointer to a directory stream (called a DIR*)
closedir(<PATH>) - follow-up to opendir()
readdir(DIR*) - returns a pointer to the *next entry* in the directory stream (use readdir(opendir(<PATH>)) ) ; does NOT censor out hidden files like "ls" in the terminal does
struct dirrent <sys/types.h> <--directory entry - contains d_name and d_type

Bash Commands:
pwd - print working directory
cd - change directory
ls - list directory contents
ls -l - ls in long-list format

 */
