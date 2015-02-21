#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"


int main() {

  typedef struct temp_name{
    char ch;
    int i;
  } note;

  int socket_id, socket_client; //socket descriptors
  note buffer; //for reading and writing
  int again; //for while loops
  int f; //for forking
  
  //create the socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;
  listener.sin_port = htons(24601);
  listener.sin_addr.s_addr = INADDR_ANY;
  bind(socket_id, (struct sockaddr *)(&listener), sizeof(listener));

  f = 1;
  while(f){
    //listen for and accept client connection (TCP)
    listen(socket_id, 1);
    socket_client = accept(socket_id, NULL, NULL); //socket_client is new the new socket descriptor
    printf("<main server> connected to new client: %d \n", socket_client-3);
    f = fork();
  }

  //subservers only
  if(!f){

    SDL_Surface *screen;
    Mix_Chunk *samples[150];
    int channel;   
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;
    int i;
    char name[1000];
    char *instruments[100] = {"Violin","Cello","Clarinet","Flute","Trumpet","Piano"};
    char *notes[100] = {"C4", "Db4", "D4", "Eb4", "E4", "F4", "Gb4", "G4", "Ab4", "A4", "Bb4", "B4", "C5", "Db5", "D5", "Eb5", "E5", "F5", "Gb5", "G5", "Ab5", "A5", "Bb5", "B5", "C6"};

    //mappings of keys to notes
    int noteval[26] = {0, 0, 0, 4, 3, 5, 7, 9, 0, 11, 12, 0, 0, 0, 0, 0, 0, 0, 2, 6, 10, 0, 1, 0, 8, 0};

    //Initialize BOTH SDL video and SDL audio
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
      printf("Unable to initialize SDL: %s\n", SDL_GetError());
      return 1;
    }

    //Initialize SDL_mixer with our chosen audio settings
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
      printf("Unable to initialize audio: %s\n", Mix_GetError());
      exit(1);
    }

    int j = 0;

    for (j = 0; j< 6; j++){
      for(i=0; i<25; i++){
        sprintf(name, "sounds/%s%s.ogg", instruments[j], notes[i]);
        samples[i+(25*j)] = Mix_LoadWAV(name);
        if(!samples[i+(25*j)]){
          printf("Mix_LoadWAV: %s\n", Mix_GetError());
        }
      }
    }

    while(buffer.ch != 'z'){
      read(socket_client, &buffer, sizeof(buffer));
      printf("<subserver> received from client %d: instrument(%d), note(%c) \n", socket_client-3, buffer.i, buffer.ch);

      if((buffer.ch - 'a') > 0 && (buffer.ch - 'z') < 0) { 
        channel = Mix_PlayChannel(-1, samples[(buffer.i*25)+noteval[buffer.ch - 'a']], 0);
      }
      
      else if(((buffer.ch - 'A') > 0 && (buffer.ch - 'Z') < 0)){
        channel = Mix_PlayChannel(-1, samples[(buffer.i*25)+noteval[buffer.ch - 'A']+12], 0);
      }
      
      else{
        channel = Mix_PlayChannel(-1, samples[buffer.i*25], 0);
      }
    }
    
    for(i=0; i<150; i++)
      Mix_FreeChunk(samples[i]);
      
    Mix_CloseAudio();
    SDL_Quit();

    close(socket_client);
    printf("<subserver> client %d exited\n", socket_client-3);
  }

  close(socket_id);
  
  return 0;

}
