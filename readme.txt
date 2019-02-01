compile using 
g++ -std=c++11 ./routing_dijkstra.cpp -o routing.out

run without any arguments
./routing.out

graph.h contains the graph class with functions for inserting edges, vertices, running dijkstra and printing vertices, edges and the shortest paths
Heap.h has a Minheap class which is used in dijkstra for implementing priority queues
network.h is the file I tested my program on
routing_dijkstra.cpp is the file which contains main()
	the program can also print all the vvertices and the edges in the graph in the format shown below
	compiled using std=c++11 for using 'range based for loops' and 'auto'