all: randmst

randmst: randmst.cc
	gcc -O3 -o randmst randmst.cc
