#makefile
all:	   ptracer.o
	   gcc ptracer.o -o ptracer
ptracer.o:   ptracer.c
	   gcc -c ptracer.c 

clean:
	    rm ptracer.o all
