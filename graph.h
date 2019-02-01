#ifndef GRAPH_H
#define GRAPH_H 1

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <map>

#include "Heap.h"


template <class dataStruct, class weight_type>
class edge;

template <class dataStruct, class weight_type>
class graph_node
{
public:
	dataStruct data;
	std::vector< edge<dataStruct, weight_type> > edges; 	//adjacency list of the nodes (contains pointers of all the neighbours)
	size_t prev;	//index of the previous node in the shortest path tree after running dijkstra
	weight_type dist;	//distance from the source after applying dijkstra
	graph_node(){
		data = 0;	//interpret zero based on the type
		edges.clear();
		prev = 0;
		dist = std::numeric_limits<weight_type>::max();
	}
	graph_node(dataStruct d)
	{
		data = d;
		edges.clear();
		prev = 0;
		dist = std::numeric_limits<weight_type>::max();
	}
	bool operator<(const graph_node<dataStruct, weight_type>& x) {
		return dist < x.dist;
	}
};

template <class dataStruct, class weight_type>
bool operator<(const graph_node<dataStruct, weight_type>& x, const graph_node<dataStruct, weight_type>& y) {
	//used for comparing nodes in priority queue in dijkstra
	return x.dist < y.dist;
}

template <class dataStruct, class weight_type>
class edge
{
public:
	size_t dest;
	weight_type weight;
	edge(size_t d, weight_type w = 0) {
		dest = d;
		weight = w;
	}
};


//only allowed weight_types are numerical types
template <class dataStruct, class weight_type>
class graph
{

public:
	const static weight_type INF = std::numeric_limits<weight_type>::max();	//stores the maximum balue weight_type can take
	
	//each node ( vertex ) has some data and the edge list
	std::vector<graph_node<dataStruct, weight_type>> vertices;

	std::map<dataStruct, int> vertex_indices;	//a map to store the vertex indices. access time logarithm in number of vertices; implemented as red black tres

	graph()
	{
		vertex_indices.clear();
		vertices.clear();
	}

	int insert_node(dataStruct n)
	{
		//returns index of the inserted node in graph vertices
		int index = vertices.size();
		vertex_indices[n] = index;
		graph_node<dataStruct, weight_type> *new_node = new graph_node<dataStruct, weight_type>(n);
		vertices.push_back(n);
		return index;
	}

	int insert_node(graph_node<dataStruct, weight_type>* node)
	{
		//returns index of the inserted node in graph vertices
		dataStruct n = node->data;
		int index = vertices.size();
		vertex_indices[n] = index;
		vertices.push_back(&node);
		return index;
	}


	int insert_node(graph_node<dataStruct, weight_type> node)
	{
		//returns index of the inserted node in graph vertices
		dataStruct n = node.data;
		int index = vertices.size();
		vertex_indices[n] = index;
		vertices.push_back(node);
		return index;
	}

	int insert_edge(dataStruct source, dataStruct dest, weight_type w = 0, bool undirected = 0)
	{
		//weight assumed to be zero if none provided
		//default is directed edge addition
		//adds the source and destination vertices to the graoh if they dont exist
		//returns the number of new vertices added to the graph

		int no = 0;
		int src_index = -1;
		int dest_index = -1;
		if (vertex_indices.find(source) == vertex_indices.end()) {
			// the source vertex doesnt exist
			graph_node<dataStruct, weight_type> source_node(source);
			src_index = insert_node(source_node);
			no += 1;
		}

		else {
			src_index = vertex_indices[source];
		}
		if (vertex_indices.find(dest) == vertex_indices.end()) {
			//the destination doesnt exist
			graph_node<dataStruct, weight_type> dest_node(dest);
			dest_index = insert_node(dest_node);
			no += 1;
		}
		else {
			dest_index = vertex_indices[dest];
		}

		//make edge and insert to the graph
		edge<dataStruct, weight_type>* e1 = new edge<dataStruct, weight_type>(dest_index, w);
		vertices[src_index].edges.push_back(*e1);
		if (undirected == 1) {
			edge<dataStruct, weight_type>* e2 = new edge<dataStruct, weight_type>(src_index, w);
			vertices[dest_index].edges.push_back(*e2);
		}

		return no;
	}

	void dijkstra_addr(graph_node<dataStruct ,weight_type>* source){
		//input is the address of a node

		//initialize the prev and dist maps

		for (auto& vertex : vertices) {
			vertex.dist = INF;
			vertex.prev = vertex_indices[vertex.data];//each vertex points to itself
		}
		source->dist = 0;
		//priority queue implemented using a min heap
		MinHeap< graph_node<dataStruct, weight_type>* > priority_queue;
		
		priority_queue.insert_at_end(source);
		graph_node<dataStruct, weight_type>* min = source;
		while (!priority_queue.is_empty()) {
			min = priority_queue.remove_min();
			for (auto& edge : min->edges) {
				if (vertices[edge.dest].dist > (min->dist + edge.weight)) {
					vertices[edge.dest].dist = min->dist + edge.weight;
					vertices[edge.dest].prev = vertex_indices[(*min).data];
					priority_queue.insert_at_end(&vertices[edge.dest]);
					priority_queue.bubble_up(priority_queue.size);
					//dont check if the element is in the heap or not, just add another copy to the  queue
					// each vertex is added the number of times it is updated.
					// TODO: calculate the complexity
				}
			}
		}

	}

	void dijkstra(dataStruct x){
		//input is a node
		//apply dijkstra on x
		// then use display_shortest_path(dataStruct x) to print the shortest path from x to any node x
		if (vertex_indices.find(x) == vertex_indices.end())
			std::cout << "no such vertex exists "<<std::endl;
		else
			dijkstra_addr(&vertices[vertex_indices[x]]);
	}

	void dijkstra(dataStruct x, dataStruct y, std::vector<dataStruct> &dont_print)
	{
		
		//apply dijksttra at x and print shortest path to y
		if (vertex_indices.find(x) == vertex_indices.end())
			std::cout << "no such vertex "<<x<<" exists" << std::endl;
		else{
			dijkstra_addr(&vertices[vertex_indices[x]]);
			if (vertex_indices.find(y) == vertex_indices.end())
				std::cout << "no such vertex " << y << " exists" << std::endl;
			else{
				display_shortest_path(y, dont_print);
			}
		}
	}

	void display_vertices() {
		for (auto vertex : vertices) {
			std::cout<<vertex.data<<" | ";
			if(vertex.dist != INF){
				std::cout << vertex.dist << " | ";
				if (vertex.prev != vertex_indices[vertex.data])
					std::cout << vertices[vertex.prev].data <<" ";
				else{
					std::cout << "(Source) ";
				}
			}
			else{
				std::cout << "INF ";
			}
			std::cout << std::endl;
		}
		return;
	}

	std::string find_vertex_given_prefix(std::string prefix, std::string upper_b){
		//  upper_b is the upper bound
		typename std::map<std::string, int>::iterator it = vertex_indices.lower_bound(prefix);
		if (it != vertex_indices.upper_bound(upper_b)){
			return it->first;
		}
		else{
			return "";
		}
	}

	void display_edges() {
		for (auto vertex : vertices) {
			std::cout << vertex.data << " ";
			std::cout << std::endl;
			for (auto edge : vertex.edges) {
				std::cout<<"\t"<< vertices[edge.dest].data<<" "<<edge.weight<<std::endl;
			}
		}
		std::cout << std::endl;
		return;
	}

	void display_all(){
		std::cout << "all vertices: " << std::endl;
		display_vertices();
		std::cout<<"all edges: "<<std::endl;
		display_edges();
		return;
	}

	void display_shortest_path(dataStruct x,const std::vector<dataStruct> &dont_print){
		size_t cursor = vertex_indices[x];
		if ( vertices[cursor].dist != INF ){
			std::cout<<"total path length: "<<vertices[cursor].dist<<std::endl;
			std::cout << "the shortest path is: " << std::endl;
			std::cout<<vertices[cursor].data;
			while(true){
				if(std::find(dont_print.begin(), dont_print.end(), vertices[vertices[cursor].prev].data) == dont_print.end()){
					//if the vertex is not dummy
					std::cout << std::endl << vertices[vertices[cursor].prev].data;
				}
				cursor = vertices[cursor].prev;
				if (vertices[cursor].prev == cursor) {
					break;
				}
			}
			std::cout << std::endl;
		}else{
			std::cout << "unreachable" << std::endl;
		}
	}

};

#endif