#include "graph.h"
#include <iostream>

int main()
{
	Graph<int> g(false);
	
	for(int i = 1; i <= 8; i++)
	{
		g.addVertex(i);
	}
	
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.addEdge(4, 8);
	g.addEdge(8, 7);
	g.addEdge(7, 6);
	g.addEdge(6, 5);
	g.addEdge(5, 1);
	
	g.addEdge(2, 6);
	g.addEdge(3, 7);
	
	cout << g << endl;
	
	cout << g.minCut() << endl;
/*	g.mergeVertices(8, 4, 8);
	g.removeSelfLoops();
	cout << g << endl;
	
	g.mergeVertices(3, 7, 3);
	g.removeSelfLoops();
	cout << g << endl;
	
	g.mergeVertices(8, 3, 8);
	g.removeSelfLoops();
	cout << g << endl;
*/	
	return 0;
}
