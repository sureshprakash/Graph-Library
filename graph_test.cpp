#include <iostream>

#include "graph.h"

int main(int argc, char *argv[])
{
	Graph<int> g(false);

	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);
	
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.addEdge(4, 1);
	
	g.addEdge(1, 3);
	g.addEdge(2, 4);
	
	cout << g << endl;
	cout << g.minCut() << endl;
	
	
	return 0;
}
