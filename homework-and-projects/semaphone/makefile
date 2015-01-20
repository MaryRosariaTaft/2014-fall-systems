all: control.c write.c
	gcc -o control control.c
	gcc -o write write.c

control.c: semaphone.h
	gcc semaphone.h

write.c: semaphone.h
	gcc semaphone.h

clean:
	rm *.gch
	rm *~
