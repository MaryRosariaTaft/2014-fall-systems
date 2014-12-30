int main(){

  int from_server;
  int to_server;
  char line[100];

  sprintf(line, "%d",getpid());
  mkdfifo("line",0644); //will become from_server
  //don't open yet --> blocking will happen, have to send info to server first


  close(from_client);
  close(to_client);

}
