#include <iostream>

#include "graph.h"

int main(int argc, char *argv[])
{
	Graph<char> g(false);
	
	g.addVertex('A');
	g.addVertex('B');
	g.addVertex('C');
	
	g.addEdge('A', 'B');
	g.addEdge('B', 'C');
	g.addEdge('C', 'A');
/*	g.addVertex('D');
	g.addVertex('E');
	g.addVertex('F');
	g.addVertex('G');

	g.addEdge('A', 'B');
	g.addEdge('B', 'C');
	g.addEdge('C', 'D');
	g.addEdge('D', 'E');
	g.addEdge('D', 'F');
	g.addEdge('D', 'G');
	
	g.addEdge('E', 'F');
	g.addEdge('F', 'G');
	g.addEdge('G', 'A');
	g.addEdge('A', 'C');
	g.addEdge('B', 'D');
	g.addEdge('E', 'G');
	g.addEdge('F', 'C');
	g.addEdge('F', 'A');
	
	g.addEdge('F', 'F');
	g.addEdge('A', 'A');
	
	g.removeEdge('E', 'F');
	
	g.mergeVertices('F', 'D', 'H');
	
	g.removeVertex('C');
	
	g.removeSelfLoops();
	
	cout << g << endl;
	
	pair<char, char> p = g.pickRandomEdge();
	
	cout << p.first << ", " << p.second << endl;*/
	
	cout << g.findMinCut() << endl;
//	cout << g.edgeExists('B', 'H') << g.edgeExists('B', 'E') << endl;
	
	return 0;
}
