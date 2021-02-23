all: priorityQueue randmst

randmst: randmst.cc
	g++ -O3 -o randmst randmst.cc

priorityQueue: priorityQueue.cc
	g++ -O3 -o priorityQueue priorityQueue.cc
