#include <iostream>
#include <vector>
#include <string>
#include "graph.h"
#include "network.h"
#include <sstream>

string convert_itos(size_t x);
size_t convert_stoi(string temp);
string trim(const string& str, const string& whitespace = " \t");


int main(){

	/*
		each interface of a router is a node in the graph
		if router has interfaces a, b, c; then the edges in the graph will be 
		directed 
		a -> dummy_node, b -> dummy_node, c -> dummy_node, 
		dummy_node -> a, dummy_node -> b, dummy_node -> c
		with edge weights zero
	
	*/
	graph<string, int> network;

	//the dummy nodes are named integers 1, 2, 3, 4...
	//take all router inputs and add edges to the network graph
	int dummy_nodes = 1;	//keeps the count of dummy nodes

	vector<string> router_interfaces;	//store all interfaces of a router
	router_interfaces.clear();

	//parse string routers in networks.h
	string router, interface;
	stringstream routers(Routers);
	vector<string> dummy;	//to store all the dummy nodes made for each router

	while(getline(routers, router, ';')){
		router_interfaces.clear();

		//add all the interfaces of a router to a vector
		stringstream interfaces(router);
		while(getline(interfaces, interface, ',')){
			interface = trim(interface);
			//all routers stored in the vector router_interfaces
			router_interfaces.push_back(interface);
		}
		
		//store all the dummy nodes in a vector
		//will be used later by print_shortest_path so that dummy nodes are not shown
		dummy.push_back(convert_itos(dummy_nodes));
		dummy_nodes += 1;

		//add the edges to the networks graph 
		for(auto iface: router_interfaces){
			network.insert_edge(iface, dummy.back());
		}
		for (auto iface : router_interfaces)
		{
			network.insert_edge(dummy.back(), iface);
		}
	}

	//add the interface edges
	stringstream more_edges(InterfaceDistance);	//from networks.h
	string interface_edge, source, destination, weight_string;
	int weight;

	//each edge starts with a '('
	while (getline(more_edges, interface_edge, '('))
	{
		if (interface_edge == "") {
			continue;
		}
		stringstream edge(interface_edge);
		getline(edge, source, ',');
		getline(edge, destination, ',');
		getline(edge, weight_string,')');	//and ends with a ')'

		//remove all starting and trailing commas, brackets and blank spaces
		source = trim(source, ", \t()");
		destination = trim(destination, " \t(),");
		weight_string = trim(weight_string, " \t(),");

		weight = convert_stoi(weight_string);
		//add undirected edges
		network.insert_edge(source, destination, weight, true);
	}

	//add host edges
	stringstream ip_addresses(IPaddress);	//from networks.h
	string ip = "";
	while (getline(ip_addresses, ip, ',')){
		ip = trim(ip);
		int third_dot = 0, countt = 0;
		unsigned int index = 0;
		//get index of the third '.' in each ip
		//eg: 1.1.1.1 will give 5 as the third '.' is at the fifth index
		for(index = 0; index < ip.length(); index++){
			if(ip[index] == '.'){
				countt += 1;
			}
			if(countt >= 3){
				break;
			}
		}
		//if the ip is not already in the network
		if(network.vertex_indices.find(ip) == network.vertex_indices.end()){
			//find the ip in the network with the same subnet
			string router_of_host = network.find_vertex_given_prefix(ip.substr(0, index+1), ip.substr(0, index+1) + "255");
			if (router_of_host == "") {
				cout << "no router of " << ip << " found" << endl;
			}
			else {
				router_of_host = trim(router_of_host);
				network.insert_edge(ip, router_of_host, 0, 1);
				//cout<<"host "<<ip<<" of router "<<router_of_host<<endl;
			}
		}
	}
	
	//network.display_all();

	cout<<"enter v for vertices and e edges"<<endl;

	string source_ip_address, source_ip_address_old="", destination_ip_address;
	cout << "give source and destination ip addresses:(press x or q to exit) ";
	while(cin>>source_ip_address){
		if (source_ip_address == "v") {
			network.display_vertices();
			cout << "give source and destination ip addresses (press x or q to exit): ";
			continue;
		}
		if (source_ip_address == "e")
		{
			network.display_edges();
			cout << "give source and destination ip addresses (press x or q to exit): ";
			continue;
		}
		if (source_ip_address == "x" || source_ip_address == "exit" || source_ip_address == "q" || source_ip_address == "quit")
		{
			return 0;
		}
		cin >> destination_ip_address;

		source_ip_address = trim(source_ip_address, " \t',;");
		destination_ip_address = trim(destination_ip_address, " \t',;");

		cout<<"looking for a path from "<<source_ip_address<<" to "<<destination_ip_address<<endl;
		if (source_ip_address_old == source_ip_address) {
			//no changes in the network during this loop
			//so if the source_ip is the same, then no need to reconpute shortest distances
			network.display_shortest_path(destination_ip_address, dummy);
		}
		else{
			network.dijkstra(source_ip_address, destination_ip_address, dummy);
		}
		source_ip_address_old = source_ip_address;
		cout << "give source and destination ip addresses (press x or q to exit): ";
	}
	return 0;
}

string convert_itos(size_t x)
{
	string ret = "";
	int rem = 0;
	while (x > 0)
	{
		rem = x % 10;
		ret += (char)(x + 48);
		x = x / 10;
	}
	return ret;
}

size_t convert_stoi(string temp)
{
	size_t ret = 0;
	ret = int(temp[0]) - 48;
	for (int iface = 1; iface < temp.size(); ++iface)
	{
		ret *= 10;
		ret += int(temp[iface]) - 48;
	}
	return ret;
}

string trim(const string& str, const string& whitespace)
{
	//trim leading and trailing characters of whitespace from string
	//eg: string = "abcdefa", whitespace = "abf"
	// it returns "cde"
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}