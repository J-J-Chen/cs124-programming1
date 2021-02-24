randmst: randmst.cc
	g++ -O3 priorityQueue.cc randmst.cc -o randmst

priorityQueue: priorityQueue.cc
	g++ -O3 -o priorityQueue priorityQueue.cc
