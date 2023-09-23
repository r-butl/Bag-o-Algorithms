// CSCI 311 - Spring 2023
// Graph Implementation
// Author: Lucas Butler

#include <iostream>
#include "Graph.h"
#include <queue>
#include <limits.h>
/*
    std::vector<std::shared_ptr<Node>> nodes;

    Graph();

    void printAdjList();
    bool isNeighbor(int, int);
    void DFS();
    int DFSVisit(int, int);
    void BFS(int);
    std::vector<int> distancesFrom(int);
.
    // NODE
    int id;
    int dist;
    int discovered;
    int finished;
    bool visited;
    std::shared_ptr<Node> predecessor;
    std::vector<std::shared_ptr<Node>> neighbors;
*/

Graph::Graph(){
  nodes = {};
}

// Prints the adjacency list
void Graph::printAdjList(){

	// protection against an empty vector
	if(nodes.size() == 0){
		return;
	}

	// Iterate through all of the nodes in the graph	
	for(int n = 0; n < nodes.size(); n++){
		// Print the node we are current at
		// protection against an empty vector of neighbors
		printf("%d: ", nodes[n]->id);
		if(nodes[n]->neighbors.size() == 0){
			// Do nothing
		}else{
			// Print all the neighbors in the current node
			for(int i = 0; i < nodes[n]->neighbors.size(); i++){
				printf("%d ", nodes[n]->neighbors[i]->id);
			}
		}
		// End of line character
		printf("\n");
	}
}

// Checks if the node is a neighbor
bool Graph::isNeighbor(int n, int v){

      // Check the nodes in u to see if v exists	
	if(nodes[n] == nullptr)	return false;	// searched node does not exist

	if(nodes[n]->neighbors.size() == 0) return false; // node has no neighbors

	for(int i = 0; i < nodes[n]->neighbors.size(); i++){
		
		if(v == nodes[n]->neighbors[i]->id) return true; // node exists
	}
	return false;

}

void Graph::DFS(){

	if(nodes.size() == 0) return;
	// Set all node values before the search begins
	for(int i = 0; i < nodes.size(); i++){
	
		// reset each of the nodes	
		nodes[i]->visited = false;
		nodes[i]->predecessor = nullptr;
		nodes[i]->discovered = -1;
		nodes[i]->finished = -1;	

	}		
	int time = 0;
	for(int u = 0; u < nodes.size(); u++){
		if(nodes[u]->visited == false){
			time = DFSVisit(u, time);
		}
	}
}

int Graph::DFSVisit(int s, int time){

	// start by incrementing the time	
	time = time + 1;
	nodes[s]->discovered = time;
	nodes[s]->visited = true;

	for(int i = 0; i < nodes[s]->neighbors.size(); i++){
			
		if(nodes[s]->neighbors[i]->visited == false){ // update the neighbors predecessor and visit it	
			nodes[s]->neighbors[i]->predecessor = nodes[s];
			time = DFSVisit(nodes[s]->neighbors[i]->id, time);
		}
	}	

	time = time + 1;
	nodes[s]->finished = time;
	//printf("node: %d, disc: %d, fin %d, visited: %d \n", nodes[s]->id, nodes[s]->discovered, nodes[s]->finished, nodes[s]->visited);
	return time;
}

void Graph::BFS(int s){

	if(nodes.size() == 0) return;

	// Set up the search
	for(int i = 0; i < nodes.size(); i++){

		nodes[i]->dist = INT_MAX;
		nodes[i]->visited = false;
		nodes[i]->predecessor = nullptr;
	}
	int distance = 0;
	nodes[s]->dist = distance;	// reset the roots distance to 0
	nodes[s]->visited = true; 	// make sure it is visited
	std::queue<int> q;		// create a new queue
	q.push(nodes[s]->id);

	while(q.size() > 0){
		int u = q.front();
		q.pop();
		//printf("\nCurrentNode: %d\t", nodes[u]->id);
		
		// update u's distance
		// Iterate through the neighbors and add them to the queue
		for(int i = 0; i < nodes[u]->neighbors.size(); i++){

			int id = nodes[u]->neighbors[i]->id;
			if(nodes[id]->visited == false){
				nodes[id]->dist = nodes[u]->dist + 1;
				nodes[id]->visited = true;
				nodes[id]->predecessor = nodes[u];
				q.push(id);
			       	//printf("\n\tnode %d, dist %d, visted %d, predecessor %d", id, nodes[id]->dist, nodes[id]->visited, nodes[id]->predecessor);

			}
		}
	}
}

// Add the distances from root to each node
std::vector<int> Graph::distancesFrom(int s){

	std::vector<int> r = {};	
	BFS(s);
	
	for(int i = 0; i < nodes.size(); i++){
		
		r.push_back(nodes[i]->dist);

	}
	
	return r;	

}
