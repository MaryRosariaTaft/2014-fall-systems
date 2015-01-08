int main(){

  int from_client;
  int to_client;
  char line[100];

  //well-known pipe
  mkdfifo("mario",0644);
  from_client = opem("mario",O_RDONLY);
  read(from_client,line,sizeof(line));

  //process
  to_client = open(line,O_WRONLY); //assuming that the first data the client sends is the name of its receiving pipe

  //send something to the client for confirmation
  strncpy(line, "its-a me" sizeof(line));

  close(from_client);
  close(to_client);

}
