#makefile
all:	   ptracer.o
	   gcc ptracer.o -o ptracer
	   ptr_test.o
	   gcc ptr_test.o -o ptr_test
ptracer.o:	ptracer.c
	  	gcc -c ptracer.c 
ptr_test.o:	ptr_test.c
		gcc -c ptr_test.c
clean:
	    rm ptracer.o all
