all: music.h music_library.h music.c music_library.c
	gcc -o test music_library.c music.c

music.c: music.h 
	gcc -c music.c

music_library.c: music.h music_library.h
	gcc -c music_library.c
clean:
	rm *.o
	rm *~	
